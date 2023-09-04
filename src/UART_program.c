/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
#include"SYSTICK_interface.h"
volatile u8 breakLoop=0;

void MUSART_voidInit(void)
{
	/*Set Baud rate at 115200*/
	MUSART1->BRR = 0x116;
	/*Enable Tx	3
	  Enable RX 2
	  Enable UART*/
	SET_BIT(MUSART1->CR1,2);
	SET_BIT(MUSART1->CR1,3);
	SET_BIT(MUSART1->CR1,13);

}

void MUSART_voidTransmit(u8 arr[])
{
	u8 i=0;
	u32 l=0;
	while(arr[i] != '\0')
	{
		MUSART1->DR = arr[i];
		while(((MUSART1->SR)& 1<<6) == 0);
		i++;
		//MSTK_voidSetBusyWait(20);

	}
}

void MUSART_voidTransmitNumbers(u8 copy_u8SendNumber)
{
	u8 i=0;
	u32 l=0;

	MUSART1->DR = copy_u8SendNumber;
	while(((MUSART1->SR)& 1<<6) == 0);




}

u8 MUSART_u8Recive(void)
{

	u8  Recive = 0;
	while(((MUSART1->SR)& 1<<5) == 0)
	{

	}

	Recive = MUSART1->DR;

	return Recive;
}


u8 MUSART_u8ReciveESP(u32 copy_waitingTime)
{
	u16 TimeOut = 0;
	u8  Recive  = 0;
	MSTK_voidSetIntervalSingle(copy_waitingTime,func);
	while(((MUSART1->SR)& 1<<5) == 0)
	{
		if(breakLoop == 1)
		{
			Recive = 255;
			breakLoop=0;
			break;
		}
	}
	if(Recive == 0)
	{
		Recive = MUSART1->DR;
	}
	return Recive;
}
void func(void){

	breakLoop = 1;
}
