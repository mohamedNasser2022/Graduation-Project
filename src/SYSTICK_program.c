/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"
#include "SYSTICK_config.h"

static u8 MSTK_u8ModeOfInterval;

void (*callback)(void);

void MSTK_voidInit(void)
{
#if   SYSTICK_CLOCK == SYSTICK_DIV_1
	SET_BIT(STK->CTRL,2);

#elif SYSTICK_CLOCK == SYSTICK_DIV_8
	CLR_BIT(STK->CTRL,2);
#endif


}

void MSTK_voidSetBusyWait(u32 copy_time)
{
	STK -> LOAD = copy_time*4;
	STK -> VAL  = 0 ;
	SET_BIT(STK->CTRL,0); /*Start Timer*/
	while(GET_BIT(STK->CTRL,16) == 0);

}

void MSTK_voidSetIntervalSingle(u32 copy_time,void (*ptr)(void) )
{
	STK -> LOAD = copy_time*4;

	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
	callback = ptr;
	SET_BIT(STK->CTRL,0); /*Start Timer*/
	SET_BIT(STK->CTRL,1); /*Enable Interrupt*/


}

void MSTK_voidSetIntervalPeriodic(u32 copy_time,void (*ptr)(void))
{
	/* Load ticks to load register */
	STK -> LOAD = copy_time*4;

	/* Start Timer */
	SET_BIT(STK->CTRL, 0);

	/* Save CallBack */
	callback = ptr;

	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;

	/* Enable STK Interrupt */
	SET_BIT(STK->CTRL, 1);

}

void MSTK_voidStopTimer(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(STK->CTRL, 1);

	/* Stop Timer */
	SET_BIT(STK->CTRL, 0);
	STK -> LOAD = 0;
	STK -> VAL  = 0;



}

u32 MSTK_u32GetElapsedTime(void)
{

}
u32 MSTK_u32GetRemaningTime(void)
{

}

void SysTick_Handler(void)
{
	u8 Local_u8Temporary;

	if (MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		/* Disable STK Interrupt */
		CLR_BIT(STK->CTRL, 1);

		/* Stop Timer */
		SET_BIT(STK->CTRL, 0);
		STK -> LOAD = 0;
		STK -> VAL  = 0;
	}

	/* Callback notification */
	callback();

	/* Clear interrupt flag */
	Local_u8Temporary = GET_BIT(STK->CTRL,16);
}

