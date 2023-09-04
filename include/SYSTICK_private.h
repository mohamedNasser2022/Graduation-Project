/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  SYSTICK_PRIVATE_H
#define  SYSTICK_PRIVATE_H

typedef struct{
	
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
	
	
}Systick_t;

#define STK ((volatile Systick_t *) 0xE000E010)

#define SYSTICK_DIV_1 1 
#define SYSTICK_DIV_8 8

#define     MSTK_SINGLE_INTERVAL    0
#define     MSTK_PERIOD_INTERVAL    1


#endif
