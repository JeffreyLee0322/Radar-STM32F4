#include "cms_debug.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"


#ifdef CMS_DEBUG
void cms_debug_init(void)
{
		  USART_InitTypeDef USART_InitStructure;
		  //NVIC_InitTypeDef NVIC_InitStructure;
		  GPIO_InitTypeDef GPIO_InitStructure;
		  
		  /* Enable GPIO clock */
		  RCC_AHB1PeriphClockCmd(USARTx_TX_GPIO_CLK, ENABLE);
		  
		  /* Enable USART clock */
		  USARTx_CLK_INIT(USARTx_CLK, ENABLE);
		  
		  /* Connect USART pins to AF7 */
		  GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);
		  //GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);
		  
		  /* Configure USART Tx and Rx as alternate function push-pull */
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		  GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
		  GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);
		  
		  //GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
		  //GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);
		
		  /* Enable the USART OverSampling by 8 */
		  //USART_OverSampling8Cmd(USARTx, ENABLE);  
		
		  /* USARTx configuration ----------------------------------------------------*/
		  /* USARTx configured as follows:
				- BaudRate = 5250000 baud
				   - Maximum BaudRate that can be achieved when using the Oversampling by 8
					 is: (USART APB Clock / 8) 
					 Example: 
						- (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
						- (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
				   - Maximum BaudRate that can be achieved when using the Oversampling by 16
					 is: (USART APB Clock / 16) 
					 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
					 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
				- Word Length = 8 Bits
				- one Stop Bit
				- No parity
				- Hardware flow control disabled (RTS and CTS signals)
				- Receive and transmit enabled
		  */ 
		  USART_InitStructure.USART_BaudRate = 115200;
		  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		  USART_InitStructure.USART_StopBits = USART_StopBits_1;
		  USART_InitStructure.USART_Parity = USART_Parity_No;
		  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		  USART_InitStructure.USART_Mode = USART_Mode_Tx;
		  USART_Init(USARTx, &USART_InitStructure);
		  
		  /* NVIC configuration */
		  /* Configure the Priority Group to 2 bits */
		  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		  
		  /* Enable the USARTx Interrupt */
		  //NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
		  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		  //NVIC_Init(&NVIC_InitStructure);
		  
		  /* Enable USART */
		  USART_Cmd(USARTx, ENABLE);
}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USARTx, (uint8_t) ch);
	
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

#endif

