#include "cms_rf.h"
#include "cms_spi.h"
#include "stdint.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"


enum BLE_ADV_CHANNEL_
{
		BLE_ADV_CHANNEL_37,
		BLE_ADV_CHANNEL_38,
		BLE_ADV_CHANNEL_39,
};
const uint8_t TX_ADDRESS_DEF[4] = {0x71, 0x91, 0x7D, 0x6B};
typedef union 
{
    uint8_t ucPayload[PAYLOAD_WIDTH];

}RF_PAYLOAD;

RF_PAYLOAD  RF_Payload;
uint32_t rx_times = 0;
uint8_t readStatus = 0;


static void RF_WriteReg( uint8_t reg,  uint8_t wdata);
static uint8_t RF_ReadReg( uint8_t reg);
static void RF_ReadBuf( uint8_t reg, unsigned char *pBuf,  uint8_t length);
static void RF_WriteBuf( uint8_t reg, uint8_t *pBuf, uint8_t length);
static void rf_clear_status(void);
static void rf_clear_fifo(void);
static uint8_t rf_dump_rx_data( uint8_t *ucPayload,  uint8_t length);
static void RF_RxMode(void);
static void RF_TxMode(void);
//void work_status_init(void);
static uint8_t ucRF_GetStatus(void);

/******************************************************************************/
//            RF_WriteReg
//                Write Data(1 Byte Address ,1 byte data)
/******************************************************************************/
static void RF_WriteReg( uint8_t reg,  uint8_t wdata)
{
	SPI_CS_Enable_();
	SPI_WriteRead(reg);
	SPI_WriteRead(wdata);
	SPI_CS_Disable_();
}

static uint8_t RF_ReadReg( uint8_t reg)
{
	uint8_t readData = 0;
	SPI_CS_Enable_();
	readData = SPI_WriteRead(reg);
	readData = SPI_WriteRead(0);
	SPI_CS_Disable_();
	return readData;
}

/******************************************************************************/
//            RF_ReadBuf
//                Read Data(1 Byte Address ,length byte data read)
/******************************************************************************/
static void RF_ReadBuf( uint8_t reg, unsigned char *pBuf,  uint8_t length)
{
    uint8_t byte_ctr;

		SPI_CS_Enable_();	
    SPI_WriteRead(reg);       		                                                		
    for(byte_ctr=0;byte_ctr<length;byte_ctr++)
    {
		pBuf[byte_ctr] = SPI_WriteRead(0);
	}
    	//pBuf[byte_ctr] = SPI_Read();                         
	SPI_CS_Disable_();
}

/******************************************************************************/
//            RF_WriteBuf
//                Write Buffer
/******************************************************************************/
static void RF_WriteBuf( uint8_t reg, uint8_t *pBuf, uint8_t length)
{
    uint8_t j = 0;
	
		SPI_CS_Enable_();	
    SPI_WriteRead(reg);
    for(j = 0;j < length; j++)
    {
        //SPI_Write(pBuf[j]);
		//SPI_Read();
			SPI_WriteRead(pBuf[j]);
    }
	j = 0;
    SPI_CS_Disable_();
}


/******************************************************************************/
//            RF_GetStatus
//            read RF IRQ status,3bits return
/******************************************************************************/
static uint8_t ucRF_GetStatus(void)
{			//??RF??? 
    return RF_ReadReg(STATUS)&0x70;	
}

/******************************************************************************/
//            RF_TxMode
//                Set RF into TX mode
/******************************************************************************/
static void RF_TxMode(void)
{
    RF_WriteReg(W_REGISTER + CONFIG,  0X8E);// 将RF设置成TX模式
    //SPI_Delay(2000);
    SPI_CE_SetHigh();
    //SPI_Delay(2000);
}

/******************************************************************************/
//            RF_RxMode
//            ?RF???RX??,??????
/******************************************************************************/
static void RF_RxMode(void)
{
    RF_WriteReg(W_REGISTER + CONFIG, 0X87 );		// ?RF???RX??   
    //RF_WriteReg(W_REGISTER + CONFIG,  0xB7 );		// ?RF???RX??   	
    //SPI_Delay(200);
    SPI_CE_SetHigh();
    //SPI_Delay(200);
}

void work_rx_status(void)
{
    RF_RxMode();
    //Work_State = FUNCTION_RX;
    //ucRFAPI_STATE = RFAPI_RX;               
}

void work_tx_status(void)
{
    RF_TxMode();
    //Work_State = FUNCTION_RX;
    //ucRFAPI_STATE = RFAPI_RX;               
}

void cms_rf_init(void)
{
  uint8_t BB_cal_data[]	  = {0x12,0xED,0x67,0x9C,0x46};
  uint8_t RF_cal_data[]	  = {0xF6,0x3F,0x5D};
  uint8_t RF_cal2_data[]  = {0x45,0x21,0xEF,0x2C,0x5A,0x40};
  uint8_t Dem_cal_data[]  = {0x00};
  //uint8_t Dem_cal2_data[] = {0x0B,0x0F,0x02};//16:13 = 0000 2bytes ---> 16bit
  uint8_t Dem_cal2_data[] = {0x0B,0x0F,0x03};//16:13 = 1000 3bytes --->  24bit
  //uint8_t Dem_cal2_data[] = {0x0B,0xCF,0x02};//16:13 = 0110 3bytes  ----> 22bit

    uint8_t feature = 0x00;

    RF_WriteReg(RST_FSPI, 0x5A);								//Software Reset    			
    RF_WriteReg(RST_FSPI, 0XA5);
    
    RF_WriteReg(FLUSH_TX, 0);									// CLEAR TXFIFO		    			 
    RF_WriteReg(FLUSH_RX, 0);									// CLEAR  RXFIFO
    RF_WriteReg(W_REGISTER + STATUS, 0x70);							// CLEAR  STATUS	
    RF_WriteReg(W_REGISTER + EN_RXADDR, 0x01);							// Enable Pipe0
    RF_WriteReg(W_REGISTER + SETUP_AW,  0x02);							// address witdth is 5 bytes
    RF_WriteReg(W_REGISTER + RF_CH,     DEFAULT_CHANNEL);                                       // 2478M HZ
    RF_WriteReg(W_REGISTER + RX_PW_P0,  PAYLOAD_WIDTH);						// 8 bytes
    RF_WriteBuf(W_REGISTER + TX_ADDR,   ( uint8_t*)TX_ADDRESS_DEF, sizeof(TX_ADDRESS_DEF));	// Writes TX_Address to PN006
    RF_WriteBuf(W_REGISTER + RX_ADDR_P0,( uint8_t*)TX_ADDRESS_DEF, sizeof(TX_ADDRESS_DEF));	// RX_Addr0 same as TX_Adr for Auto.Ack   
    RF_WriteBuf(W_REGISTER + BB_CAL,    BB_cal_data,  sizeof(BB_cal_data));
    RF_WriteBuf(W_REGISTER + RF_CAL2,   RF_cal2_data, sizeof(RF_cal2_data));
    RF_WriteBuf(W_REGISTER + DEM_CAL,   Dem_cal_data, sizeof(Dem_cal_data));
    RF_WriteBuf(W_REGISTER + RF_CAL,    RF_cal_data,  sizeof(RF_cal_data));
    RF_WriteBuf(W_REGISTER + DEM_CAL2,  Dem_cal2_data,sizeof(Dem_cal2_data));
    RF_WriteReg(W_REGISTER + DYNPD, 0x00);					                            
    RF_WriteReg(W_REGISTER + RF_SETUP,  RF_POWER);						// 13DBM  		
    RF_WriteReg(ACTIVATE, 0x73);
    
#if(TRANSMIT_TYPE == TRANS_ENHANCE_MODE)      
    RF_WriteReg(W_REGISTER + SETUP_RETR,0x01);							//  1 retrans... 	
    RF_WriteReg(W_REGISTER + EN_AA,     0x01);							// Enable Auto.Ack:Pipe0  	
#elif(TRANSMIT_TYPE == TRANS_BURST_MODE)                                                                
    RF_WriteReg(W_REGISTER + SETUP_RETR,0x00);							// Disable retrans... 	
    RF_WriteReg(W_REGISTER + EN_AA,     0x00);							// Disable AutoAck 
#endif

#if(EN_DYNPLOAD == 1)
    feature |= 0x04;
    RF_WriteReg(W_REGISTER + DYNPD, 0x01);
#endif

#if(EN_ACK_PAYLOAD == 1)
    feature |= 0x02;
#endif

if(PAYLOAD_WIDTH >32)
    feature |= 0x18;

RF_WriteReg(W_REGISTER + FEATURE, feature);
}

/******************************************************************************/
//            ucRF_DumpRxData
//            ????????:
//            ??:
//              1. ucPayload:?????????Buffer
//              2. length:    ???????
//              Return:
//              1. 0: ???????
//              2. 1: ??????????
//              note: Only use in Rx Mode
//              length ???? PAYLOAD_WIDTH
/******************************************************************************/
static uint8_t rf_dump_rx_data( uint8_t *ucPayload,  uint8_t length)
{ 
    //if(!(ucRF_GetStatus() & RX_DR_FLAG))
    //if(GPIO0->DI & (1<<7))
    //if(!((ucRF_GetStatus() >> 6)&0x01))
    //if(0 == irq_flag)
  readStatus = ucRF_GetStatus();
    if(!(readStatus & RX_DR_FLAG))
    //if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == 1)
    {
      return 0;                                                                 		
    }

    //irq_flag = 0;
    rx_times++;
    if(rx_times > 0xfffff0)
    {
        rx_times = 0;
    }
    
    RF_ReadBuf(R_RX_PAYLOAD, ucPayload, length);
 
     return 1;
}

void ble_to_24g_irq_handle(void)
{
	//irq_flag = 1;
}


/******************************************************************************/
//            RF_ClearStatus
//                clear RF IRQ
/******************************************************************************/
static void rf_clear_status(void)
{
    RF_WriteReg(W_REGISTER + STATUS,0x70);							//??RF?IRQ?? 
    //RF_WriteReg(W_REGISTER + STATUS,0x40);							//??RF?IRQ?? 
}

/******************************************************************************/
//            RF_ClearFIFO
//                clear RF TX/RX FIFO
/******************************************************************************/
static void rf_clear_fifo(void)
{ 
    RF_WriteReg(FLUSH_TX, 0);			                                		//??RF ? TX FIFO		
    RF_WriteReg(FLUSH_RX, 0);                                         //??RF ? RX FIFO	
}

/******************************************************************************/
//            BB_RX_State
//                In RX status ,Judge data has been received and read them
/******************************************************************************/
void rf_receive_handle(void)
{
	//uint8_t i = 0;
		if(rf_dump_rx_data(RF_Payload.ucPayload,PAYLOAD_WIDTH))//16Bytes
		{
			rf_clear_fifo();
			rf_clear_status();
			
#if 0
			//whitening_init(39);//BLE_CHANNEL_INDEX
			whitening_decode(RF_Payload.ucPayload, PAYLOAD_WIDTH);
			
			if (RF_Payload.ucPayload[8] == 0x04 &&
				RF_Payload.ucPayload[9] == 0xFF &&
				RF_Payload.ucPayload[10] == 0xF0 &&
				RF_Payload.ucPayload[11] == 0xFF)
			{
			  RX_READY = 1;
			  
			  Have_Data++;
			  if(Have_Data > 0xfffff0)
			  {
				  Have_Data = 0;
			  }
			  
			  //for(i = 0; i < 16; i++)
			  {
				  //Payload_Data_Pre_Crc[i] = RF_Payload.ucPayload[i];
			  }
			  
			  crc_init();
			  check_crc(RF_Payload.ucPayload, PAYLOAD_WIDTH - 3);
			  uint32_t calc_crc = arr_to_crc();
			  
			  uint32_t rf_crc = RF_Payload.ucPayload[PAYLOAD_WIDTH - 3] + (RF_Payload.ucPayload[PAYLOAD_WIDTH - 2] << 8) + (RF_Payload.ucPayload[PAYLOAD_WIDTH - 1] << 16);
			  
			  if (calc_crc == rf_crc)
			  {
				RX_CRC_CORRECT = 1;
				Correct_Data++;
				if(Correct_Data > 0xfffff0)
				{
					Correct_Data = 0;
				}
				rf_data = RF_Payload.ucPayload[PAYLOAD_WIDTH - 4];
			  }
			  else
			  {
				RX_CRC_CORRECT = 0;
				Wrong_Data++;
				if(Wrong_Data > 0xfffff0)
				{
					Wrong_Data = 0;
				}
			  }
			}
#endif
		}
}

/******************************************************************************/
//            发送数据：
//            参数：
//              1. ucPayload：需要发送的数据首地址
//              2. length:  需要发送的数据长度
//              Return:
//              1. MAX_RT: TX Failure  (Enhance mode)
//              2. TX_DS:  TX Successful (Enhance mode)
//              note: Only use in Tx Mode
//              length 通常等于 PAYLOAD_WIDTH
/******************************************************************************/
void ucRF_TxData( uint8_t *ucPayload,  uint8_t length)
{
    RF_WriteBuf(W_TX_PAYLOAD, ucPayload, length);                               		//write data to txfifo                                                                      		//rf entery tx mode start send data                                                                       		//rf entery stb3
    //delay_ms(2);
    
    if(ucRF_GetStatus()==TX_DS_FLAG)                //Check  the register sent successfully
    {
        rf_clear_fifo();
	rf_clear_status();
    }
}





