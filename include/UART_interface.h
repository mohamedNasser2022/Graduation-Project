/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  UART_INTERFACE_H
#define  UART_INTERFACE_H

void MUSART_voidInit(void);
void MUSART_voidTransmit(u8 arr[]);
u8 MUSART_u8Recive(void);
u8 MUSART_u8ReciveESP(u32 copy_waitingTime);
void func(void);
#endif
