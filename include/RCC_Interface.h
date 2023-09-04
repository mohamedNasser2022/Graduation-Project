/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 24 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/


#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#define RCC_AHP  0
#define RCC_APB1 1
#define RCC_APB2 2

void RCC_voidInitSystemClock(void);
void RCC_voidEnableClock(u8 BusID, u8 PerID);
void RCC_voidDisableClock(u8 BusID, u8 PerID);




#endif
