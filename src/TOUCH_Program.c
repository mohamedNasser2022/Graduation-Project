/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 24 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SYSTICK_interface.h"
#include "ADC_private.h"


#include "TOUCH_interface.h"
#include "TOUCH_private.h"
#include "TOUCH_config.h"


//volatile u16 Position[2];
void HTOUCH_voidGetPoint(u16 *ptr)
{
	volatile u32 LOCAL_X =0;
	volatile u32 LOCAL_Y =0;

	if(HTOUCH_u8GetTouched()){
		if(GET_BIT(ptr[5],1)==0){
			ConfigtoX();
			SET_BIT(ptr[5],1);
			for(u8 i=0 ; i<40; i++)
			{
				LOCAL_X = ((u32)(ADC2_u16Conversion(X)*3300))/4096 + LOCAL_X;
			}
			LOCAL_X /= 40;
			ConfigtoY();

			for(u8 i=0 ; i<40; i++)
			{
				LOCAL_Y = ((u32)(ADC2_u16Conversion(Y)*3300))/4096 + LOCAL_Y;
			}
			LOCAL_Y /=40;
			ptr[0] = (((u32)LOCAL_X * 86.91)  - 22786)/1000 ; //0.194
			ptr[1] = (((s32)LOCAL_Y * -119.6) + 359799.8)/1000 ; //0.2374

		}
		else{
			ptr[0] = 0;
			ptr[1] = 0;
		}

	}
	else
	{
		ptr[0] = 0;
		ptr[1] = 0;
		CLR_BIT(ptr[5],1);

	}


}

static u8 HTOUCH_u8GetTouched(void)
{
	volatile u16 LOCAL_X =0;
	volatile u16 LOCAL_Y =0;

	MGPIO_voidSetPinDirection(YM_AN,INPUT_ANALOG);
	MGPIO_voidSetPinDirection(XM_AN,INPUT_ANALOG);
	MGPIO_voidSetPinDirection(Xm_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(Ym_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(Xm_D0,1);
	MGPIO_voidSetPinValue(Ym_D1,0);
	for(u8 i=0; i<10 ;i++)
	{
		LOCAL_X = ((u32)(ADC2_u16Conversion(0)*3300))/4096;
		LOCAL_Y = ((u32)(ADC2_u16Conversion(1)*3300))/4096;
		if (LOCAL_X == 0 || LOCAL_Y ==0)
		{
			break;
		}

	}
	if (LOCAL_X == 0 || LOCAL_Y ==0)
	{
		return 0 ;
	}
	else
	{
		return 1 ;
	}
}

static void ConfigtoX(void)
{
	MGPIO_voidSetPinDirection(YM_AN,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(XM_AN,INPUT_ANALOG);

	MGPIO_voidSetPinDirection(Xm_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(Ym_D1,INPUT_FLOATING);

	MGPIO_voidSetPinValue(YM_AN,1);
	MGPIO_voidSetPinValue(Xm_D0,0);


}


static void ConfigtoY(void)
{
	MGPIO_voidSetPinDirection(YM_AN,INPUT_ANALOG);
	MGPIO_voidSetPinDirection(XM_AN,OUTPUT_SPEED_2MHZ_PP);

	MGPIO_voidSetPinDirection(Xm_D0,INPUT_FLOATING);
	MGPIO_voidSetPinDirection(Ym_D1,OUTPUT_SPEED_2MHZ_PP);

	MGPIO_voidSetPinValue(XM_AN,1);
	MGPIO_voidSetPinValue(Ym_D1,0);


}
