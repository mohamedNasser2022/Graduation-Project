/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  TIMER_PRIVATE_H
#define  TIMER_PRIVATE_H

typedef struct {

		u32 volatile CR1   ;
		u32 volatile CR2   ;
		u32 volatile SMCR  ;
		u32 volatile DIER  ;
		u32 volatile SR    ;
		u32 volatile EGR   ;
		u32 volatile CCMR1 ;
		u32 volatile CCMR2 ;
		u32 volatile CCER  ;
		u32 volatile CNT   ;
		u32 volatile PSC   ;
		u32 volatile ARR   ;
		u32 volatile RCR   ;
		u32 volatile CCR1  ;
		u32 volatile CCR2  ;
		u32 volatile CCR3  ;
		u32 volatile CCR4  ;
		u32 volatile BDTR  ;
		u32 volatile DCR   ;
		u32 volatile DMAR  ;

}TIMER_t ; 

#define TIMER_1 ((volatile TIMER_t *) 0x40012C00)
#define TIMER_2 ((volatile TIMER_t *) 0x40000000)
#define TIMER_3 ((volatile TIMER_t *) 0x40000400)
#define TIMER_4 ((volatile TIMER_t *) 0x40000800)



#endif
