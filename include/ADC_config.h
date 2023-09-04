/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 29 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef  ADC_CONFIG_H
#define  ADC_CONFIG_H
/*Option: ADC_CONT_MODE
		  ADC_DISCONT_MODE
*/

#define ADC2_MODE ADC2_DISCONT_MODE

/*Option: ADC_LEFT
		  ADC_RIGHT
		  */

#define ADC2_DATA_ALIGNMENT  ADC2_RIGHT

/*Option : ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   
		   */
#define ADC2_SAMPLE

// ADC1

/*
 ADC_REGULA
 ADC_INJECTED
 */


#define ADC_MODE ADC_DISCONT_MODE

/*Option: ADC_LEFT
		  ADC_RIGHT
		  */

#define ADC_DATA_ALIGNMENT  ADC_RIGHT

/*Option : ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5
		   ADC_S_1_5

		   */
#define ADC_SAMPLE 001

#define ADC_EVENT 0b111 //for software trigger


//..

#endif
