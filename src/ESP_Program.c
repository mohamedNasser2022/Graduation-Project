/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 24 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

#include"UART_interface.h"
#include"SYSTICK_interface.h"


u8 WIFI_Status=0; //bit 0 wifi state, bit 1 Server Connection
u8 r=0;
u16 ESP_data[3];
u8 Local_u8Response[100] = {0};
void HESP_voidESPInit(void)
{



	MUSART_voidTransmit("AT\r\n");
	r= HESP_u8ESPCheckCommand(5,0,0);
	MUSART_voidTransmit("ATE0\r\n");
	r= HESP_u8ESPCheckCommand(5,0,0);

	MUSART_voidTransmit("AT+CWMODE=1\r\n");
	r= HESP_u8ESPCheckCommand(5,0,0);



}
// http://supercharger.freevar.com/current.txt
u8 HESP_u8ESPConnectToServer(u8 copy_Server[])
{
	MUSART_voidTransmit("AT+CIPSTART=");
	MUSART_voidTransmit("\"TCP\",\"");
	MUSART_voidTransmit(copy_Server);
	MUSART_voidTransmit("\",80\r\n");
	r= HESP_u8ESPCheckCommand(1000,1,"OK");
	return r;
}
u8 HESP_u8ReadData(u8 copy_dataSize[],u8 copy_http[],u8 copy_DataType)
{
	u8 Local_u8Return = 0;
	MUSART_voidTransmit("AT+CIPSEND=");
	MUSART_voidTransmit(copy_dataSize);
	MUSART_voidTransmit("\r\n");
	r= HESP_u8ESPCheckCommand(1,0,0);

	MUSART_voidTransmit("GET ");
	MUSART_voidTransmit(copy_http);
	MUSART_voidTransmit("\r\n");
	HESP_u8ESPCheckCommand(1000,0,0);
	for(u8 local_search = 0 ; local_search<99;local_search++)
			{
				if ((Local_u8Response[local_search] ==':'))
				{	u8 Local_Digit=0;
					u8 Local_Number=0;
					local_search++;
					while(Local_u8Response[local_search] != 'C')
					{
						Local_Number =Local_u8Response[local_search]-0x30;
						ESP_data[0] = (ESP_data[0])*10*Local_Digit+Local_Number;
						Local_Digit++;
						local_search++;
						if(local_search == 95)
						{
							break;
						}

					}
					Local_u8Return = 1;
					break;
				}
				else{
					Local_u8Return=0;
				}

			}
	return r;

}
u8 HESP_u8ESPWifiConnect(u8 copy_u8ID[],u8 copy_u8Pass[])
{

	MUSART_voidTransmit("AT+CWJAP_CUR=");
	MUSART_voidTransmit("\"");
	MUSART_voidTransmit(copy_u8ID);
	MUSART_voidTransmit("\",\"");
	MUSART_voidTransmit(copy_u8Pass);
	MUSART_voidTransmit("\"\r\n");
	r = HESP_u8ESPCheckCommand(5000,0,0);

	return r;


}



u8 HESP_u8ESPCheckCommand(u32 copy_WaitTime_ms,u8 copy_u8EnableCheck,u8 copy_veryfied[])
{
	u8 Local_u8Return = 0;
	for(u8 zero = 0;zero<100;zero++)
	{
		Local_u8Response[zero] = 0;
	}


	u8 k=0;
	u8 i=0;
	while(i != 255)
	{
		/*Recive from ESP*/
		i = MUSART_u8ReciveESP(copy_WaitTime_ms*1000);
		Local_u8Response[k] = i;
		k++;
	}

	/*Analysis what recived?*/
	if(copy_u8EnableCheck == 1){
	for(u8 local_search = 0 ; local_search<99;local_search++)
	{
		if ((Local_u8Response[local_search] == copy_veryfied[0])&&(Local_u8Response[local_search+1] == copy_veryfied[1]))
		{
			Local_u8Return = 1;
			break;
		}
		else{
			Local_u8Return=0;
		}

	}
	}
	else {
		Local_u8Return=1;
	}
	return Local_u8Return;

}

