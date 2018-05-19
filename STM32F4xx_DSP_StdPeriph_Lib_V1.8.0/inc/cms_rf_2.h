#ifndef CMS_RF2_H
#define CMS_RF2_H
#include "stm32f4xx.h"
#include "stdint.h"
#include "cms_rf_config.h"

void cms_rf_init_2(void);
void work_rx_status_2(void);
void work_tx_status_2(void);
void ucRF_TxData_2( uint8_t *ucPayload,  uint8_t length);
void ble_to_24g_irq_handle_2(void);
void 		rf_receive_handle_2(void); 


#endif

