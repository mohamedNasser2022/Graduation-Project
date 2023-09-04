/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 28 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  DMA_INTERFACE_H
#define  DMA_INTERFACE_H


void MDMA_voidChannelInit(void);

void MDMA_voidChannelStart(u32* copy_Pu32SourcAddress,u32* copy_Pu32DestinationAddress,u16 copy_u16BlockLenth);




#endif
