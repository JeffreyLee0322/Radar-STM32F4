#ifndef CMS_SPI_H
#define CMS_SPI_H
#include "stm32f4xx.h"
#include "stdint.h"
#include "cms_config.h"


#define SPIx                           SPI2
#define SPIx_CLK                       RCC_APB1Periph_SPI2
#define SPIx_CLK_INIT                  RCC_APB1PeriphClockCmd
//#define SPIx_IRQn                      SPI2_IRQn
//#define SPIx_IRQHANDLER                SPI2_IRQHandler

#define SPIx_SEL_PIN                   GPIO_Pin_12
#define SPIx_IRQ_PIN                   GPIO_Pin_10
#define SPIx_CE_PIN                    GPIO_Pin_11


#define SPIx_SCK_PIN                   GPIO_Pin_13
#define SPIx_SCK_GPIO_PORT             GPIOB
#define SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define SPIx_SCK_SOURCE                GPIO_PinSource13
#define SPIx_SCK_AF                    GPIO_AF_SPI2

#define SPIx_MISO_PIN                  GPIO_Pin_14
#define SPIx_MISO_GPIO_PORT            GPIOB
#define SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPIx_MISO_SOURCE               GPIO_PinSource14
#define SPIx_MISO_AF                   GPIO_AF_SPI2

#define SPIx_MOSI_PIN                  GPIO_Pin_15
#define SPIx_MOSI_GPIO_PORT            GPIOB
#define SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPIx_MOSI_SOURCE               GPIO_PinSource15
#define SPIx_MOSI_AF                   GPIO_AF_SPI2


//Config SPI_2
#define SPIx1                           SPI1
#define SPIx1_CLK                       RCC_APB2Periph_SPI1
#define SPIx1_CLK_INIT                  RCC_APB2PeriphClockCmd
//#define SPIx_IRQn                     SPI2_IRQn
//#define SPIx_IRQHANDLER               SPI2_IRQHandler

#define SPIx1_SEL_PIN                   GPIO_Pin_4//PA
#define SPIx1_IRQ_PIN                   GPIO_Pin_0//PB
#define SPIx1_CE_PIN                    GPIO_Pin_1//PB


#define SPIx1_SCK_PIN                   GPIO_Pin_5
#define SPIx1_SCK_GPIO_PORT             GPIOA
#define SPIx1_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOA
#define SPIx1_SCK_SOURCE                GPIO_PinSource5
#define SPIx1_SCK_AF                    GPIO_AF_SPI1

#define SPIx1_MISO_PIN                  GPIO_Pin_6
#define SPIx1_MISO_GPIO_PORT            GPIOA
#define SPIx1_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOA
#define SPIx1_MISO_SOURCE               GPIO_PinSource6
#define SPIx1_MISO_AF                   GPIO_AF_SPI1

#define SPIx1_MOSI_PIN                  GPIO_Pin_7
#define SPIx1_MOSI_GPIO_PORT            GPIOA
#define SPIx1_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOA
#define SPIx1_MOSI_SOURCE               GPIO_PinSource7
#define SPIx1_MOSI_AF                   GPIO_AF_SPI1


	
void cms_spi_init(uint8_t value);

uint8_t SPI_WriteRead(unsigned char SendData);
void SPI_CS_Enable_(void);
void SPI_CS_Disable_(void);
void SPI_CE_SetHigh(void);
void SPI_CE_SetLow(void);

uint8_t SPI_WriteRead_2(unsigned char SendData);
void SPI_CS_Enable_2(void);
void SPI_CS_Disable_2(void);
void SPI_CE_SetHigh_2(void);
void SPI_CE_SetLow_2(void);

void SPI_Delay(int time);

#endif
