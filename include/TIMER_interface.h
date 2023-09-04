/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  TIMER_INTERFACE_H
#define  TIMER_INTERFACE_H

void TIMER_voidInitPWM(u8 copy_u8Timerx,u16 copy_u16ARR,u16 copy_u16Prescaler);
void TIMER_voidTimerShifting(void);
void TIMER1_voidPWMSetDuty(u16 copy_u16DutyValue);
void TIMER4_voidPWMSetDuty(u16 copy_u16DutyValue);
u8 TIMER_u8TimerVerifyShiting(void);

#define TIMER1	1
#define TIMER2	2
#define TIMER3	3
#define TIMER4	4
#endif
