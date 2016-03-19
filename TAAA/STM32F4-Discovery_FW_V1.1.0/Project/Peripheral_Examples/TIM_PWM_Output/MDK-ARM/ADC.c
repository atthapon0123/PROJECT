#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "ADC.h"

	/* ----------------------------------------------*/
	/*                ADC Pin Table                  */
	/* ----------------------------------------------*/
	/*| Channel    |   ADC1   |   ADC2   |   ADC3   |*/
	/* ----------------------------------------------*/
	/*| Channel 0  |   PA0    |   PA0    |   PA0    |*/
	/*| Channel 1  |   PA1    |   PA1    |   PA1    |*/
	/*| Channel 2  |   PA2    |   PA2    |   PA2    |*/
	/*| Channel 3  |   PA3    |   PA3    |   PA3    |*/
	/*| Channel 4  |   PA4    |   PA4    |   PF6    |*/
	/*| Channel 5  |   PA5    |   PA5    |   PF7    |*/
	/*| Channel 6  |   PA6    |   PA6    |   PF8    |*/
	/*| Channel 7  |   PA7    |   PA7    |   PF9    |*/
	/*| Channel 8  |   PB0    |   PB0    |   PF10   |*/
	/*| Channel 9  |   PB1    |   PB1    |   PF3    |*/
	/*| Channel 10 |   PC0    |   PC0    |   PC0    |*/
	/*| Channel 11 |   PC1    |   PC1    |   PC1    |*/
	/*| Channel 12 |   PC2    |   PC2    |   PC2    |*/
	/*| Channel 13 |   PC3    |   PC3    |   PC3    |*/
	/*| Channel 14 |   PC4    |   PC4    |   PF4    |*/
	/*| Channel 15 |   PC5    |   PC5    |   PC5    |*/
	/* ----------------------------------------------*/
	/*                 Table End                     */
	/* ----------------------------------------------*/

#define COUNT 16384
float TAAA1 = 0;
int i = 0;
float check =0;

void RCC_Configuration(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA | 
  RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | 
  RCC_APB2Periph_ADC3, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
 
/****************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
 
/*****************************************************************************/
void ADC_Configuration(void)
{
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef ADC_InitStructure;
 
  /* ADC Common Init */
  ADC_CommonInitStructure.ADC_Mode = ADC_TripleMode_RegSimult;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1; 
  // 3 half-words one by one, 1 then 2 then 3
  ADC_CommonInitStructure.ADC_TwoSamplingDelay =  ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
 
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE; // 2 Channels
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Conversions Triggered
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 2;
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_Init(ADC2, &ADC_InitStructure); // Mirror on ADC2
  ADC_Init(ADC3, &ADC_InitStructure); // Mirror on ADC3
 
  /* ADC1 regular channel 0 & 10 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0,  1, ADC_SampleTime_3Cycles);  
  // PA0
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 2, ADC_SampleTime_3Cycles);// PC0
 
  /* ADC2 regular channel 1 & 11 configuration */
  ADC_RegularChannelConfig(ADC2, ADC_Channel_1,  1, ADC_SampleTime_3Cycles); 
  // PA1
  ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 2,  ADC_SampleTime_3Cycles);// PC1
 
  /* ADC3 regular channel 2 & 12 configuration */
  ADC_RegularChannelConfig(ADC3, ADC_Channel_2,  1, ADC_SampleTime_3Cycles);  
  // PA2
  ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2,  ADC_SampleTime_3Cycles);// PC2
 
  /* Enable DMA request after last transfer (Multi-ADC mode)  */
  ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
 
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
 
  /* Enable ADC2 */
  ADC_Cmd(ADC2, ENABLE);
 
  /* Enable ADC3 */
  ADC_Cmd(ADC3, ENABLE);
}
 
 
#define BUFFERSIZE  (6)  
__IO uint16_t ADCTripleConvertedValues[BUFFERSIZE]; 
__IO int analog[6] = { 0, 0, 0, 0, 0, 0 };
 
static void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;
 
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADCTripleConvertedValues[0];
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)0x40012308; // CDR_ADDRESS; Packed ADC1, ADC2
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = BUFFERSIZE; // Count of 16-bit words
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
 
  /* Enable DMA Stream Half / Transfer Complete interrupt */
  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC | DMA_IT_HT, ENABLE);
 
  /* DMA2_Stream0 enable */
  DMA_Cmd(DMA2_Stream0, ENABLE);
}
 
/******************************************************************************/ 
void TIM2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = ((SystemCoreClock / 2) / 40000) - 1; 
  // 40 KHz, from 84 MHz TIM2CLK (ie APB1 = HCLK/4, TIM2CLK = HCLK/2)
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 
  /* TIM2 TRGO selection */
  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update); 
   //   ADC_ExternalTrigConv_T2_TRGO
 
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}
 
/********************************************************************************/
void NVIC_Configuration(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

/* Enable the DMA Stream IRQ Channel */
NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************/ 
void DMA2_Stream0_IRQHandler(void) 
// Called at 1 KHz for 40 KHz sample rate, LED Toggles at 500 Hz
{
/* Test on DMA Stream Half Transfer interrupt */
if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_HTIF0))
{
/* Clear DMA Stream Half Transfer interrupt pending bit */
DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_HTIF0);

// Add code here to process first half of buffer (ping)
}

/* Test on DMA Stream Transfer Complete interrupt */
if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
{
/* Clear DMA Stream Transfer Complete interrupt pending bit */
DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);


// Add code here to process second half of buffer (pong)
}
}

void ADC_init(ADCvalue *p)
{ 
RCC_Configuration();
	
GPIO_Configuration();

NVIC_Configuration();

TIM2_Configuration();
	
DMA_Configuration();

ADC_Configuration();
//	adcdim.init(&adcdim);

/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConv(ADC1);
	

} 


void ADC_update(ADCvalue *p)
{
		analog[0] = (int) ADCTripleConvertedValues[0]  ; 	//PA0
		analog[1] = (int) ADCTripleConvertedValues[1]  ; 	//PA1
		analog[2] = (int) ADCTripleConvertedValues[2]  ; 	//PC0
		analog[3] = (int) ADCTripleConvertedValues[3]  ; 	//PC1
		analog[4] = (int) ADCTripleConvertedValues[4]  ; 	//PC1
		analog[5] = (int) ADCTripleConvertedValues[5]  ; 	//PC1


	if ((i<=COUNT))
	{

		if ((i<=COUNT))
		{
			p->err0 += (int) ADCTripleConvertedValues[0];
			p->err1 += (int) ADCTripleConvertedValues[1];
			p->err2 += analog[3];
			p->err3 += analog[4];
			i++;
		}
		p->error0=((int)p->err0/(i-1))-0x0800;
		p->error1=((int)p->err1/(i-1))-0x0800;
		p->error2=((int)p->err2/(i-1))-0x0800;
		p->error3=((int)p->err3/(i-1))-0x0800;
	}
	else
	{

	p->volt_grid_ab = ((int) ADCTripleConvertedValues[0] - p->error0)  ; 	//PA0
	p->volt_grid_bc = ((int) ADCTripleConvertedValues[1] - p->error1)   ; 	//PA1
	
	p->volt_grid_ab_set0 = ((float)p->volt_grid_ab*3/4095) - 1.5 ; //set0 unit3V 
	p->volt_grid_bc_set0 = ((float)p->volt_grid_bc*3/4095) - 1.5 ; //set0 unit3V

	p->volt_grid_ab_pu = p->volt_grid_ab_set0/2.06944 ;
	p->volt_grid_bc_pu = p->volt_grid_bc_set0/2.06944 ;
	}

}
