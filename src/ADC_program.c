/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

// note config can user edit in it only, 
//config and private mustn't be included in any other drivers
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"



void ADC2_voidInitADC(void)
{
#if   ADC2_MODE == ADC2_DISCONT_MODE
	CLR_BIT(ADC2_CR2,1);
	SET_BIT(ADC2_CR1,11);
#if   ADC2_DATA_ALIGNMENT == ADC2_RIGHT
	CLR_BIT(ADC2_CR2,11);
#elif ADC2_DATA_ALIGNMENT == ADC2_LEFT
	SET_BIT(ADC2_CR2,11);
#else  /*Error*/
#endif
#elif ADC2_MODE == ADC2_CONT_MODE
	SET_BIT(ADC2_CR2,1);
#if   ADC2_DATA_ALIGNMENT == ADC2_RIGHT
	CLR_BIT(ADC2_CR2,11);
#elif ADC2_DATA_ALIGNMENT == ADC2_LEFT
	SET_BIT(ADC2_CR2,11);
#else  /*Error*/
#endif
#else /*Error*/
#endif
	SET_BIT(ADC2_CR2,20); /*Enable external trigger*/
	ADC2_CR2  &= ~((0b111)<<17);
	ADC2_CR2  |=  (0b111<<17);  // SW selected to be trigger
	SET_BIT(ADC2_CR2,0);
}

void ADC2_voidSelectChannalRegular(u8 copy_Channal,u8 copy_Group,u8 copy_Sample)
{
	if(copy_Group<=6)
	{
		ADC2_SQR3 &= ~((0b11111)<<(copy_Channal-1)*5);
		ADC2_SQR3 |= ((copy_Channal)<<(copy_Channal-1)*5);
	}
	else if(copy_Group<=12)
	{	copy_Group = copy_Group - 6;
	ADC2_SQR2 &= ~((0b11111)<<(copy_Channal-1)*5);
	ADC2_SQR2 |= ((copy_Channal)<<(copy_Channal-1)*5);
	}
	else if(copy_Group<=16)
	{	copy_Group = copy_Group - 12;
	ADC2_SQR1 &= ~((0b11111)<<(copy_Channal-1)*5);
	ADC2_SQR1 |= ((copy_Channal)<<(copy_Channal-1)*5);
	}
	ADC2_SMPR2 = 0x3F;
}

void ADC2_voidRegularLength(u8 copy_NoofGroups)
{
	ADC2_SQR1 &= ~((0b1111)<<20);
	ADC2_SQR1 |=   (copy_NoofGroups<<20);


}

extern SamplingAndControl;

u16 ADC2_u16Conversion(u8 copy_ChannelNumber)
{
	ADC2_SQR3 = copy_ChannelNumber;
	u16 lOC_Data = 0;

	SET_BIT(ADC2_CR2,22);
	while(GET_BIT(ADC2_SR,1) == 0);
	lOC_Data = ADC2_DR;

	return lOC_Data;
}


void ADC_voidInitADC(void)
{
#if   ADC_MODE == ADC_DISCONT_MODE
	CLR_BIT(ADC_CR2,1);
	SET_BIT(ADC_CR1,11);
#if   ADC_DATA_ALIGNMENT == ADC_RIGHT
	CLR_BIT(ADC_CR2,11);
#elif ADC_DATA_ALIGNMENT == ADC_LEFT
	SET_BIT(ADC_CR2,11);
#else  /*Error*/
#endif
#elif ADC_MODE == ADC_CONT_MODE
	SET_BIT(ADC_CR2,1);
#if   ADC_DATA_ALIGNMENT == ADC_RIGHT
	CLR_BIT(ADC_CR2,11);
#elif ADC_DATA_ALIGNMENT == ADC_LEFT
	SET_BIT(ADC_CR2,11);
#else  /*Error*/
#endif
#else /*Error*/
#endif
	SET_BIT(ADC2_CR2,20); /*Enable external trigger*/
	ADC_CR2  &= ~((0b111)<<17);
	ADC_CR2  |=  (0b111<<17);  // SW selected to be trigger
	SET_BIT(ADC_CR2,0);

}

void ADC_voidSelectChannalRegular(u8 copy_Channal,u8 copy_Group,u8 copy_Sample)
{
	if(copy_Group<=6)
	{
		ADC_SQR3 &= ~((0b11111)<<(copy_Channal-1)*5);
		ADC_SQR3 |= ((copy_Channal)<<(copy_Channal-1)*5);
	}
	else if(copy_Group<=12)
	{	copy_Group = copy_Group - 6;
	ADC_SQR2 &= ~((0b11111)<<(copy_Channal-1)*5);
	ADC_SQR2 |= ((copy_Channal)<<(copy_Channal-1)*5);
	}
	else if(copy_Group<=16)
	{	copy_Group = copy_Group - 12;
	ADC_SQR1 &= ~((0b11111)<<(copy_Channal-1)*5);
	ADC_SQR1 |= ((copy_Channal)<<(copy_Channal-1)*5);
	}
	ADC_SMPR2 = 0x3F;
}

void ADC_voidRegularLength(u8 copy_NoConversions)
{
	ADC_SQR1 &= ~((0b1111)<<20);
	ADC_SQR1 |=   (copy_NoConversions<<20);


}
u16 ADC_u16Conversion(u8 copy_ChannelNumber)
{

	ADC_SQR3 = copy_ChannelNumber;
	u16 lOC_Data = 0;
	SET_BIT(ADC_CR2,22);
	while(GET_BIT(ADC_SR,1) == 0);
	lOC_Data = ADC_DR;
	return lOC_Data;


}
