/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  ADC_INTERFACE_H
#define  ADC_INTERFACE_H

void ADC_voidInitADC(void);
void ADC_voidSelectChannalRegular(u8 copy_Channal,u8 copy_Group,u8 copy_Sample);
void ADC_voidRegularLength(u8 copy_NoConversions);
u16 ADC_u16Conversion(u8 copy_ChannelNumber);

void ADC2_voidInitADC(void);
void ADC2_voidSelectChannalRegular(u8 copy_Channal,u8 copy_Group,u8 copy_Sample);
void ADC2_voidRegularLength(u8 copy_NoofGroups);
u16 ADC2_u16Conversion(u8 copy_ChannelNumber);
#endif
