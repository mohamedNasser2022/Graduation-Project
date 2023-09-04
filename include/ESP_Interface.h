/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 24 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/


#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

void HESP_voidESPInit(void);

#define CURRENT 0
#define VOLTAGE 1

u8 HESP_u8ESPWifiConnect(u8 copy_u8ID[],u8 copy_u8Pass[]);
u8 HESP_u8ESPConnectToServer(u8 copy_Server[]);
u8 HESP_u8ReadData(u8 copy_dataSize[],u8 copy_http[],u8 copy_DataType);
u8 HESP_u8ESPCheckCommand(u32 copy_WaitTime_ms,u8 copy_u8EnableCheck,u8 copy_veryfied[]);
void HESP_voidWifiSetState(u8 copy_u8BIT,u8 Copy_u8Value);

#endif
