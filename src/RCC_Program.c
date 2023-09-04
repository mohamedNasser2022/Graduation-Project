/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 24 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidInitSystemClock(void){

#if   RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
	RCC_CR  = 0x00010000; /*HSE Enable With no bypass*/
	RCC_CFGR= 0x00000001;


#elif RCC_CLOCK_TYPE == RCC_HSE_RC
	RCC_CR  = 0x00050000; /*HSE Enable With bypass*/
	RCC_CFGR= 0x00000001;

#elif RCC_CLOCK_TYPE == RCC_HSI
	RCC_CR  = 0x00000081; /*HSI Enable + Trimming 0 */
	RCC_CFGR= 0x00000000;


#elif RCC_CLOCK_TYPE == RCC_PLL
	RCC_CR  = 0x00010000; /*HSE Enable With no bypass*/
	RCC_CFGR= 0x00000001;
	CLR_BIT(RCC_CR,24);


#if    RCC_PLL_INPUT ==  RCC_PLL_IN_HSI_DIV_2
	CLR_BIT(RCC_CFGR,16);

#elif  RCC_PLL_INPUT ==  RCC_PLL_IN_HSE
	SET_BIT(RCC_CFGR,16);

#elif  RCC_PLL_INPUT ==  RCC_PLL_IN_HSE_DIV_2
	SET_BIT(RCC_CFGR,17);

#else
#error("You chosed Wrong Clock type")

#endif


	RCC_CFGR &= ~(0b1111<<18);
	RCC_CFGR |=  (RCC_PLL_MUL_VAL<<18);
	SET_BIT(RCC_CR,24);

	RCC_CFGR &= ~(0b11);
	RCC_CFGR |= (0b10);

#else

#endif
}

void RCC_voidEnableClock(u8 BusID, u8 PerID){

	if (PerID <= 31)
	{
		switch (BusID)
		{
		case RCC_AHP  : SET_BIT(RCC_AHBENR  ,PerID);   break;
		case RCC_APB1 : SET_BIT(RCC_APB1ENR ,PerID);   break;
		case RCC_APB2 : SET_BIT(RCC_APB2ENR ,PerID);   break;
		}
	}

	else
	{
		/* Return Error */
	}


}

void RCC_voidDisableClock(u8 BusID, u8 PerID){

	if (PerID <= 31)
	{
		switch (BusID)
		{
		case RCC_AHP  : CLR_BIT(RCC_AHBENR  ,PerID);   break;
		case RCC_APB1 : CLR_BIT(RCC_APB1ENR ,PerID);   break;
		case RCC_APB2 : CLR_BIT(RCC_APB2ENR ,PerID);   break;
		}
	}

	else
	{
		/* Return Error */
	}

}

