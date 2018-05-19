#include "cms_spi.h"
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_it.h"

static void SPI_Config(void);
static void SPI_Config_2(void);
static void SPI_Master_Init(void);
static void SPI_Master_Init_2(void);


SPI_InitTypeDef  SPI_InitStructure;

static void SPI_Master_Init(void)
{
/* Master board configuration */    
  /* Initializes the SPI communication */
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPIx, &SPI_InitStructure);
  
  /* The Data transfer is performed in the SPI interrupt routine */
  /* Configure the Tamper Button */
  //STM_EVAL_PBInit(BUTTON_TAMPER,BUTTON_MODE_GPIO);
  
  /* Wait until Tamper Button is pressed */
  //while (STM_EVAL_PBGetState(BUTTON_TAMPER));
  
  /* Enable the SPI peripheral */
  SPI_Cmd(SPIx, ENABLE);
  
  /* Initialize Buffer counters */
  //ubTxIndex = 0;
  //ubRxIndex = 0;
  
  /* Enable the Rx buffer not empty interrupt */
  //SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);
  
  /* Enable the Tx buffer empty interrupt */
  //SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_TXE, ENABLE);
}

static void SPI_Master_Init_2(void)
{
  /* Master board configuration */    
  /* Initializes the SPI communication */
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPIx1, &SPI_InitStructure);
  
  /* The Data transfer is performed in the SPI interrupt routine */
  /* Configure the Tamper Button */
  //STM_EVAL_PBInit(BUTTON_TAMPER,BUTTON_MODE_GPIO);
  
  /* Wait until Tamper Button is pressed */
  //while (STM_EVAL_PBGetState(BUTTON_TAMPER));
  
  /* Enable the SPI peripheral */
  SPI_Cmd(SPIx1, ENABLE);
  
  /* Initialize Buffer counters */
  //ubTxIndex = 0;
  //ubRxIndex = 0;
  
  /* Enable the Rx buffer not empty interrupt */
  //SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);
  
  /* Enable the Tx buffer empty interrupt */
  //SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_TXE, ENABLE);
}

/**
  * @brief  Configures the SPI Peripheral.
  * @param  None
  * @retval None
  */
static void SPI_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable the SPI clock */
  SPIx_CLK_INIT(SPIx_CLK, ENABLE);
  
  /* Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(SPIx_SCK_GPIO_CLK | SPIx_MISO_GPIO_CLK | SPIx_MOSI_GPIO_CLK, ENABLE);
  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* SPI GPIO Configuration --------------------------------------------------*/
  /* GPIO Deinitialisation */
  GPIO_DeInit(SPIx_SCK_GPIO_PORT);
  //GPIO_DeInit(SPIx_MISO_GPIO_PORT);
  //GPIO_DeInit(SPIx_MOSI_GPIO_PORT);
  //GPIO_DeInit(GPIOA);
  
  /* Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(SPIx_SCK_GPIO_PORT, SPIx_SCK_SOURCE, SPIx_SCK_AF);
  GPIO_PinAFConfig(SPIx_MISO_GPIO_PORT, SPIx_MISO_SOURCE, SPIx_MISO_AF);    
  GPIO_PinAFConfig(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_SOURCE, SPIx_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = SPIx_SCK_PIN;
  GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);
  
  /* SPI  MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPIx_MISO_PIN;
  GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPIx_MOSI_PIN;
  GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);
 
  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPIx);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  
  /* Configure the Priority Group to 1 bit */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Configure the SPI interrupt priority */
  //NVIC_InitStructure.NVIC_IRQChannel = SPIx_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);

  //SPI_SEL SETUP Send-->
  /* Configure PB12 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = SPIx_SEL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure PA10 in output pushpull mode (IRQ)*/
  GPIO_InitStructure.GPIO_Pin = SPIx_IRQ_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_OType = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure PA11 in output pushpull mode (CE)*/
  GPIO_InitStructure.GPIO_Pin = SPIx_CE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

static void SPI_Config_2(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable the SPI clock */
  SPIx1_CLK_INIT(SPIx1_CLK, ENABLE);
  
  /* Enable GPIO clocks */
  //RCC_AHB1PeriphClockCmd(SPIx1_SCK_GPIO_CLK | SPIx1_MISO_GPIO_CLK | SPIx1_MOSI_GPIO_CLK, ENABLE);
  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* SPI GPIO Configuration --------------------------------------------------*/
  /* GPIO Deinitialisation */
  //GPIO_DeInit(SPIx_SCK_GPIO_PORT);
  //GPIO_DeInit(SPIx_MISO_GPIO_PORT);
  //GPIO_DeInit(SPIx_MOSI_GPIO_PORT);
  //GPIO_DeInit(GPIOA);
  
  /* Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(SPIx1_SCK_GPIO_PORT, SPIx1_SCK_SOURCE, SPIx1_SCK_AF);
  GPIO_PinAFConfig(SPIx1_MISO_GPIO_PORT, SPIx1_MISO_SOURCE, SPIx1_MISO_AF);    
  GPIO_PinAFConfig(SPIx1_MOSI_GPIO_PORT, SPIx1_MOSI_SOURCE, SPIx1_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = SPIx1_SCK_PIN;
  GPIO_Init(SPIx1_SCK_GPIO_PORT, &GPIO_InitStructure);
  
  /* SPI  MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPIx1_MISO_PIN;
  GPIO_Init(SPIx1_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPIx1_MOSI_PIN;
  GPIO_Init(SPIx1_MOSI_GPIO_PORT, &GPIO_InitStructure);
 
  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPIx1);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  
  /* Configure the Priority Group to 1 bit */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Configure the SPI interrupt priority */
  //NVIC_InitStructure.NVIC_IRQChannel = SPIx_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);

  //SPI_SEL SETUP Receive <--
  /* Configure PA4 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = SPIx1_SEL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure PB0 in output pushpull mode (IRQ)*/
  GPIO_InitStructure.GPIO_Pin = SPIx1_IRQ_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_OType = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  //Configure EXTI Line0 (connected to PB0(IRQ) pin) in interrupt mode
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  /* Configure PA0 pin as input floating */
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  //GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set EXTI Line0 Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Configure PB1 in output pushpull mode (CE)*/
  GPIO_InitStructure.GPIO_Pin = SPIx1_CE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SPI_CS_Enable_(void)
{
    /* Reset PB12 */
    GPIO_ResetBits(GPIOB, SPIx_SEL_PIN);
    //GPIO_ResetBits(GPIOA, SPIx1_SEL_PIN);
}

void SPI_CS_Enable_2(void)
{
    /* Reset PB12 */
    //GPIO_ResetBits(GPIOB, SPIx_SEL_PIN);
    GPIO_ResetBits(GPIOA, SPIx1_SEL_PIN);
}


void SPI_CS_Disable_(void)
{
   /* Set PB12 */
   GPIO_SetBits(GPIOB, SPIx_SEL_PIN);
   //GPIO_SetBits(GPIOA, SPIx1_SEL_PIN);
}

void SPI_CS_Disable_2(void)
{
   /* Set PB12 */
   //GPIO_SetBits(GPIOB, SPIx_SEL_PIN);
   GPIO_SetBits(GPIOA, SPIx1_SEL_PIN);
}

uint8_t SPI_WriteRead(unsigned char SendData)
{
	while(!((SPIx->SR)&0x2));//Tx buffer not empty
	SPI_I2S_SendData(SPIx, SendData);
	while(!((SPIx->SR)&0x1));//Rx buffer empty
	return SPI_I2S_ReceiveData(SPIx);

	/*while(!((SPIx1->SR)&0x2));//Tx buffer not empty
	SPI_I2S_SendData(SPIx1, SendData);
	while(!((SPIx1->SR)&0x1));//Rx buffer empty
	return SPI_I2S_ReceiveData(SPIx1);*/
}

uint8_t SPI_WriteRead_2(unsigned char SendData)
{
	/*while(!((SPIx->SR)&0x2));//Tx buffer not empty
	SPI_I2S_SendData(SPIx, SendData);
	while(!((SPIx->SR)&0x1));//Rx buffer empty
	return SPI_I2S_ReceiveData(SPIx);*/

	while(!((SPIx1->SR)&0x2));//Tx buffer not empty
	SPI_I2S_SendData(SPIx1, SendData);
	while(!((SPIx1->SR)&0x1));//Rx buffer empty
	return SPI_I2S_ReceiveData(SPIx1);
}


void cms_spi_init(uint8_t value)
{
  /* SPI configuration */
  if(0 == value)
  {
	SPI_Config();
	SPI_Master_Init();
  }else if(1 == value)
  {
	SPI_Config_2();
  	SPI_Master_Init_2();
  }else if(2 == value)
  {
	SPI_Config();
	SPI_Master_Init();
        SPI_Config_2();
	SPI_Master_Init_2();
  }else
  {
	 //SPI NO USED!!!
  }
}

void SPI_CE_SetHigh(void)
{
	GPIO_SetBits(GPIOA, SPIx_CE_PIN);
	//GPIO_SetBits(GPIOB, SPIx1_CE_PIN);
}

void SPI_CE_SetHigh_2(void)
{
	//GPIO_SetBits(GPIOA, SPIx_CE_PIN);
	GPIO_SetBits(GPIOB, SPIx1_CE_PIN);
}

void SPI_CE_SetLow(void)
{
	GPIO_ResetBits(GPIOA, SPIx_CE_PIN);
	//GPIO_ResetBits(GPIOB, SPIx1_CE_PIN);
}

void SPI_CE_SetLow_2(void)
{
	//GPIO_ResetBits(GPIOA, SPIx_CE_PIN);
	GPIO_ResetBits(GPIOB, SPIx1_CE_PIN);
}


void SPI_Delay(int time)
{
  if (time != 0x00)
  {
    time--;
  }
}



