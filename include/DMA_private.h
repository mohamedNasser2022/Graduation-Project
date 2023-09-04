/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 01 JAN 2021									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  DMA_PRIVATE_H
#define  DMA_PRIVATE_H

typedef struct {

	volatile u32 CCR;
	volatile u32 CNDTR;
	volatile u32 CPAR;
	volatile u32 CMAR;
	volatile u32 Reserved;

}DMA_Channel;

typedef struct{
	
	volatile u32 ISR;
	volatile u32 IFCR;
	DMA_Channel Channel[7];
	
	
}DMA_t;

#define DMA ((DMA_t*)0x40020000)




#endif
