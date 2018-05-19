#ifndef _CMS_GPIO_H
#define _CMS_GPIO_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#define TIMER3_TEST_PIN                   GPIO_Pin_3
#define TIMER3_TEST_GPIO_PORT             GPIOA

void timer3_gpio_test_init(void);
void timer3_set_gpio(void);
void timer3_clear_gpio(void);

#endif

