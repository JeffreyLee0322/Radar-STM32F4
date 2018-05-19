#include "cms_gpio.h"

void timer3_gpio_test_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin =   TIMER3_TEST_PIN;
  GPIO_Init(TIMER3_TEST_GPIO_PORT, &GPIO_InitStructure);
}

void timer3_set_gpio(void)
{
  GPIO_SetBits(TIMER3_TEST_GPIO_PORT, TIMER3_TEST_PIN);
}

void timer3_clear_gpio(void)
{
  GPIO_ResetBits(TIMER3_TEST_GPIO_PORT, TIMER3_TEST_PIN);
}

