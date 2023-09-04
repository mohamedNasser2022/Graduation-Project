/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 28 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_config.h"

void MDMA_voidChannelInit(void)
{
	/*
	1- mem to mem
	2- very high 
	3- Sourc size, destination size 32 
	4-  MINC , PINK
	5- no circular
	6- direction
	7- Transfer interrupt
	
	*/
	#if CHANNEL_ID == 1
	CLR_BIT(DMA->Channel[0].CCR,14);
	
	/*Select mem size*/
	CLR_BIT(DMA->Channel[0].CCR,11);
	SET_BIT(DMA->Channel[0].CCR,10);

	/*Select per size*/
	CLR_BIT(DMA->Channel[0].CCR,9);
	SET_BIT(DMA->Channel[0].CCR,8);

	/*memory in crement*/
	SET_BIT(DMA->Channel[0].CCR,7);
	CLR_BIT(DMA->Channel[0].CCR,6);

	/*cicular*/
	SET_BIT(DMA->Channel[0].CCR,5);

	/*Read form per*/
	CLR_BIT(DMA->Channel[0].CCR,4);

	#endif
}


void MDMA_voidChannelStart(u32* copy_Pu32SourcAddress,u32* copy_Pu32DestinationAddress,u16 copy_u16BlockLength)
{
	/* make sure channel disabled*/
	CLR_BIT(DMA->Channel[0].CCR,0);
	/*Write address source*/
	DMA->Channel[0].CPAR = copy_Pu32SourcAddress;
	/*Write address destiantion*/
	DMA->Channel[0].CMAR = copy_Pu32DestinationAddress;
	/*Block length*/
	DMA->Channel[0].CNDTR = copy_u16BlockLength;
	/*Enable Channel*/
	SET_BIT(DMA->Channel[0].CCR,0);
	
}
