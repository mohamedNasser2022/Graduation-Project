/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 04 DCE 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  ADC_PRIVATE_H
#define  ADC_PRIVATE_H

#define ADC1_BASE_ADDRESS  0x40012400
#define ADC2_BASE_ADDRESS  0x40012800
#define ADC3_BASE_ADDRESS  0x40013C00

#define ADC2_DISCONT_MODE 0
#define ADC2_CONT_MODE    1
#define ADC2_RIGHT 1
#define ADC2_LEFT 0

#define ADC_REGULA		 0
#define ADC_INJECTED	 1
#define ADC_DISCONT_MODE 0
#define ADC_CONT_MODE    1
#define ADC_RIGHT		 1
#define ADC_LEFT 		 0


	
      /*Registers FOR ADC 1*/

#define ADC_SR    *((u32*) (ADC1_BASE_ADDRESS + 0x00 ))
#define ADC_CR1   *((u32*) (ADC1_BASE_ADDRESS + 0x04 ))
#define ADC_CR2   *((u32*) (ADC1_BASE_ADDRESS + 0x08 ))
#define ADC_SMPR1 *((u32*) (ADC1_BASE_ADDRESS + 0x0C ))
#define ADC_SMPR2 *((u32*) (ADC1_BASE_ADDRESS + 0x10 ))
#define ADC_JOFR1 *((u32*) (ADC1_BASE_ADDRESS + 0x14 ))
#define ADC_JOFR2 *((u32*) (ADC1_BASE_ADDRESS + 0x18 ))
#define ADC_JOFR3 *((u32*) (ADC1_BASE_ADDRESS + 0x1C ))
#define ADC_JOFR4 *((u32*) (ADC1_BASE_ADDRESS + 0x20 ))
#define ADC_HTR   *((u32*) (ADC1_BASE_ADDRESS + 0x24 ))
#define ADC_LTR   *((u32*) (ADC1_BASE_ADDRESS + 0x28 ))
#define ADC_SQR1  *((u32*) (ADC1_BASE_ADDRESS + 0x2C ))
#define ADC_SQR2  *((u32*) (ADC1_BASE_ADDRESS + 0x30 ))
#define ADC_SQR3  *((u32*) (ADC1_BASE_ADDRESS + 0x34 ))
#define ADC_JSQR  *((u32*) (ADC1_BASE_ADDRESS + 0x38 ))
#define ADC_JDR1  *((u32*) (ADC1_BASE_ADDRESS + 0x3C ))
#define ADC_JDR2  *((u32*) (ADC1_BASE_ADDRESS + 0x40 ))
#define ADC_JDR3  *((u32*) (ADC1_BASE_ADDRESS + 0x44 ))
#define ADC_JDR4  *((u32*) (ADC1_BASE_ADDRESS + 0x48 ))
#define ADC_DR    *((u32*) (ADC1_BASE_ADDRESS + 0x4C ))

       /*Registers FOR ADC 2*/
#define ADC2_SR    *((u32*) (ADC2_BASE_ADDRESS + 0x00 ))
#define ADC2_CR1   *((u32*) (ADC2_BASE_ADDRESS + 0x04 ))
#define ADC2_CR2   *((u32*) (ADC2_BASE_ADDRESS + 0x08 ))
#define ADC2_SMPR1 *((u32*) (ADC2_BASE_ADDRESS + 0x0C ))
#define ADC2_SMPR2 *((u32*) (ADC2_BASE_ADDRESS + 0x10 ))
#define ADC2_JOFR1 *((u32*) (ADC2_BASE_ADDRESS + 0x14 ))
#define ADC2_JOFR2 *((u32*) (ADC2_BASE_ADDRESS + 0x18 ))
#define ADC2_JOFR3 *((u32*) (ADC2_BASE_ADDRESS + 0x1C ))
#define ADC2_JOFR4 *((u32*) (ADC2_BASE_ADDRESS + 0x20 ))
#define ADC2_HTR   *((u32*) (ADC2_BASE_ADDRESS + 0x24 ))
#define ADC2_LTR   *((u32*) (ADC2_BASE_ADDRESS + 0x28 ))
#define ADC2_SQR1  *((u32*) (ADC2_BASE_ADDRESS + 0x2C ))
#define ADC2_SQR2  *((u32*) (ADC2_BASE_ADDRESS + 0x30 ))
#define ADC2_SQR3  *((u32*) (ADC2_BASE_ADDRESS + 0x34 ))
#define ADC2_JSQR  *((u32*) (ADC2_BASE_ADDRESS + 0x38 ))
#define ADC2_JDR1  *((u32*) (ADC2_BASE_ADDRESS + 0x3C ))
#define ADC2_JDR2  *((u32*) (ADC2_BASE_ADDRESS + 0x40 ))
#define ADC2_JDR3  *((u32*) (ADC2_BASE_ADDRESS + 0x44 ))
#define ADC2_JDR4  *((u32*) (ADC2_BASE_ADDRESS + 0x48 ))
#define ADC2_DR    *((u32*) (ADC2_BASE_ADDRESS + 0x4C ))

      /*Registers FOR ADC 3*/
#define ADC3_SR    *((u32*) (ADC3_BASE_ADDRESS + 0x00 ))
#define ADC3_CR1   *((u32*) (ADC3_BASE_ADDRESS + 0x04 ))
#define ADC3_CR2   *((u32*) (ADC3_BASE_ADDRESS + 0x08 ))
#define ADC3_SMPR1 *((u32*) (ADC3_BASE_ADDRESS + 0x0C ))
#define ADC3_SMPR2 *((u32*) (ADC3_BASE_ADDRESS + 0x10 ))
#define ADC3_JOFR1 *((u32*) (ADC3_BASE_ADDRESS + 0x14 ))
#define ADC3_JOFR2 *((u32*) (ADC3_BASE_ADDRESS + 0x18 ))
#define ADC3_JOFR3 *((u32*) (ADC3_BASE_ADDRESS + 0x1C ))
#define ADC3_JOFR4 *((u32*) (ADC3_BASE_ADDRESS + 0x20 ))
#define ADC3_HTR   *((u32*) (ADC3_BASE_ADDRESS + 0x24 ))
#define ADC3_LTR   *((u32*) (ADC3_BASE_ADDRESS + 0x28 ))
#define ADC3_SQR1  *((u32*) (ADC3_BASE_ADDRESS + 0x2C ))
#define ADC3_SQR2  *((u32*) (ADC3_BASE_ADDRESS + 0x30 ))
#define ADC3_SQR3  *((u32*) (ADC3_BASE_ADDRESS + 0x34 ))
#define ADC3_JSQR  *((u32*) (ADC3_BASE_ADDRESS + 0x38 ))
#define ADC3_JDR1  *((u32*) (ADC3_BASE_ADDRESS + 0x3C ))
#define ADC3_JDR2  *((u32*) (ADC3_BASE_ADDRESS + 0x40 ))
#define ADC3_JDR3  *((u32*) (ADC3_BASE_ADDRESS + 0x44 ))
#define ADC3_JDR4  *((u32*) (ADC3_BASE_ADDRESS + 0x48 ))
#define ADC3_DR    *((u32*) (ADC3_BASE_ADDRESS + 0x4C ))
		   

#endif
