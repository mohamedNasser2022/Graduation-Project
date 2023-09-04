/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"

void MAFIO_voidTIMER(void){

	CLR_BIT(AFIO -> EVCR,6);
	CLR_BIT(AFIO -> EVCR,7);
}

void MAFIO_voidSetEXTIConfig(u8 copy_u8Line,u8 copy_u8PortMap)
{
	u8 LOC_u8RegIndex = 0;
	if(copy_u8Line <= 3)
	{	
		LOC_u8RegIndex=0;
	}
	else if(copy_u8Line<=7)
	{
		LOC_u8RegIndex=1;
		copy_u8Line -= 4;
	}
	else if(copy_u8Line<=11)
	{
		LOC_u8RegIndex=2;
		copy_u8Line -= 8;
	}
	else if(copy_u8Line<=15)
	{
		LOC_u8RegIndex=3;
		copy_u8Line -= 12;
	}
	AFIO -> EXTICR[LOC_u8RegIndex] &= ~((0b1111)<<(copy_u8Line * 4));
	AFIO -> EXTICR[LOC_u8RegIndex] |= ((copy_u8PortMap)<<(copy_u8Line * 4));
}
