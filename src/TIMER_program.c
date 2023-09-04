/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

void TIMER_voidInitPWM(u8 copy_u8Timerx,u16 copy_u16ARR,u16 copy_u16Prescaler)
{
	switch(copy_u8Timerx)
	{
	case TIMER1:

		TIMER_1 -> CR1    &= ~((0b1111)<<4);  /*Set Auto reload, countup,Edge aline */
		TIMER_1 -> CR1    |=  ((0b1000)<<4);
		TIMER_1 -> PSC     = copy_u16Prescaler;  /*pre scaler = 0 +1 = 1 */
		TIMER_1 -> ARR     = copy_u16ARR; /*frequance of PMW*/
		TIMER_1 -> CCR1   = 0; /*duty cycle of PWM channel 1*/
		TIMER_1 -> CCMR1 &= ~(0xFF); /* CLEAR BITs [0,1] */
		TIMER_1 -> CCMR1 |=  (0b01101000); /* CLEAR BITs [0,1] */
		CLR_BIT(TIMER_1 -> CCER,3);
		SET_BIT(TIMER_1 -> EGR,0);
		SET_BIT(TIMER_1 -> CCER,0);
		SET_BIT(TIMER_1 -> BDTR,15);
		SET_BIT(TIMER_1 -> CR1,0);


		break;
	case TIMER2:
		TIMER_2 -> CR1    &= ~((0b1111)<<4);  /*Set Auto reload, countup,Edge aline */
		TIMER_2 -> CR1    |=  ((0b1000)<<4);
		TIMER_2 -> PSC    = copy_u16Prescaler;  /*pre scaler = 0 +1 = 1 */
		TIMER_2 -> ARR    = copy_u16ARR; /*frequance of PMW*/
		TIMER_2 -> CCR2   = 250; /*duty cycle of PWM channel 1*/
		TIMER_2 -> CCMR1  = 0; /* CLEAR BITs [0,1] */
		TIMER_2 -> CCMR1 |=  0b01101000; /* CLEAR BITs [0,1] */
		CLR_BIT(TIMER_2 -> CCER,3);
		SET_BIT(TIMER_2 -> EGR,0);
		SET_BIT(TIMER_2 -> CCER,0);
		SET_BIT(TIMER_2 -> BDTR,15);
		SET_BIT(TIMER_2 -> CR1,0);

		break;
	case TIMER3:
		TIMER_3 -> CR1    &= ~((0b1111)<<4);  /*Set Auto reload, countup,Edge aline */
		TIMER_3 -> CR1    |=  ((0b1000)<<4);
		TIMER_3 -> PSC    = copy_u16Prescaler;  /*pre scaler = 0 +1 = 1 */
		TIMER_3 -> ARR    = copy_u16ARR; /*frequance of PMW*/
		TIMER_3 -> CCR1   = 250; /*duty cycle of PWM channel 1*/
		TIMER_3 -> CCMR1 &= ~(0xFF); /* CLEAR BITs [0,1] */
		TIMER_3 -> CCMR1 |=  (0b01101000); /* CLEAR BITs [0,1] */
		CLR_BIT(TIMER_3 -> CCER,3);
		SET_BIT(TIMER_3 -> EGR,0);
		SET_BIT(TIMER_3 -> CCER,0);
		SET_BIT(TIMER_3 -> BDTR,15);
		SET_BIT(TIMER_3 -> CR1,0);
		break;
	case TIMER4:
		TIMER_4 -> CR1    &= ~((0b1111)<<4);  /*Set Auto reload, countup,Edge aline */
		TIMER_4 -> CR1    |=  ((0b1000)<<4);
		TIMER_4 -> PSC    = copy_u16Prescaler;  /*pre scaler = 0 +1 = 1 */
		TIMER_4 -> ARR    = copy_u16ARR; /*frequance of PMW*/
		TIMER_4 -> CCR1   = 0; /*duty cycle of PWM channel 1*/
		TIMER_4 -> CCMR1 &= ~(0xFF); /* CLEAR BITs [0,1] */
		TIMER_4 -> CCMR1 |=  (0b01101000); /* CLEAR BITs [0,1] */
		CLR_BIT(TIMER_4 -> CCER,3);
		SET_BIT(TIMER_4 -> EGR,0);
		SET_BIT(TIMER_4 -> CCER,0);
		SET_BIT(TIMER_4 -> BDTR,15);
		SET_BIT(TIMER_4 -> CR1,0);
		break;
	default:
		// ERROR
		break;
	}
}

void TIMER_voidTimerShifting(void)
{
	TIMER_1 -> CNT = 0;
	TIMER_4 -> CNT = TIMER_1 -> CNT + 310;


}

u8 TIMER_u8TimerVerifyShiting(void)
{

	volatile	s16 x = (TIMER_1 -> CNT) - (TIMER_4 -> CNT);
	if(x<0)
	{
		x = x*-1; // get x positive
	}
	if(x<311 && x>309)
	{
		return 1;
	}
	else
	{
		TIMER_1 -> CNT = 0;
		TIMER_4 -> CNT = TIMER_1 -> CNT + 311;
	}


}


void TIMER1_voidPWMSetDuty(u16 copy_u16DutyValue)
{
	if(copy_u16DutyValue >285)
	{
		TIMER_1 -> CCR1 =0;
	}
	else{
		TIMER_1 -> CCR1   = copy_u16DutyValue;
	}
}

void TIMER4_voidPWMSetDuty(u16 copy_u16DutyValue)
{
	if(copy_u16DutyValue >285)
	{
		TIMER_4 -> CCR1   =0;
	}
	else{
		TIMER_4 -> CCR1   = copy_u16DutyValue;
	}
}

