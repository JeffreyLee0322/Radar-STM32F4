#ifndef CMS_DEBUG_H
#define CMS_DEBUG_H
#include <stdio.h>
#include "stm32f4xx.h"
#include "cms_config.h"


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
 #ifdef CMS_DEBUG
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
 #else
  #define PUTCHAR_PROTOTYPE 
 #endif
#endif /* __GNUC__ */



#ifdef CMS_DEBUG
#define USARTx                           USART2
#define USARTx_CLK                       RCC_APB1Periph_USART2
#define USARTx_CLK_INIT                  RCC_APB1PeriphClockCmd
//#define USARTx_IRQn                      USART3_IRQn
//#define USARTx_IRQHandler                USART3_IRQHandler

#define USARTx_TX_PIN                    GPIO_Pin_2                
#define USARTx_TX_GPIO_PORT              GPIOA                       
#define USARTx_TX_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define USARTx_TX_SOURCE                 GPIO_PinSource2
#define USARTx_TX_AF                     GPIO_AF_USART2


void cms_debug_init(void);
#endif



#endif
