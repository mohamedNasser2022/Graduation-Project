/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  SYSTICK_INTERFACE_H
#define  SYSTICK_INTERFACE_H




void MSTK_voidInit(void);
void MSTK_voidSetBusyWait(u32 copy_time);      		//Synchronous Functions
void MSTK_voidSetIntervalSingle(u32 copy_time,void (*ptr)(void));	//Asynchronous Fucntions
void MSTK_voidSetIntervalPeriodic(u32 copy_time,void (*ptr)(void));	//Asynchronous Fucntions
void MSTK_voidStopTimer(void);
void MSTK_voidContinTimer(void);
u32 MSTK_u32GetElapsedTime(void);
u32 MSTK_u32GetRemaningTime(void);


#endif
