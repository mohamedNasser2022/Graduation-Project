/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 18 Feb 2021									   */
/*	Version: V02											   */
/***************************************************************/

#ifndef ESP_CONFIG_H
#define ESP_CONFIG_H

#define TFT_RS   GPIOA,PIN0	//Command 0 data 1
#define TFT_CS   GPIOA,PIN1

#define TFT_REST GPIOB,PIN1


#define TFT_W   GPIOB,PIN0
#define TFT_R   GPIOB,PIN10

#define TFT_D0 GPIOB,PIN12 //Effected on Touch
#define TFT_D1 GPIOA,PIN3  //Effected on Touch
#define TFT_D2 GPIOA,PIN12
#define TFT_D3 GPIOA,PIN11
#define TFT_D4 GPIOB,PIN5
#define TFT_D5 GPIOB,PIN13
#define TFT_D6 GPIOB,PIN14
#define TFT_D7 GPIOB,PIN15



/*#define TFT_RS   GPIOA,PIN0	//Command 0 data 1
#define TFT_CS   GPIOA,PIN1

#define TFT_REST GPIOB,PIN1


#define TFT_W   GPIOB,PIN0
#define TFT_R   GPIOA,PIN7  //read

#define TFT_D0 GPIOB,PIN12
#define TFT_D1 GPIOB,PIN3
#define TFT_D2 GPIOA,PIN12
#define TFT_D3 GPIOA,PIN11
#define TFT_D4 GPIOA,PIN8
#define TFT_D5 GPIOB,PIN15
#define TFT_D6 GPIOB,PIN14
#define TFT_D7 GPIOB,PIN13
*/
#define DISPOFF 0x28 // display off
#define DISPON 0x29 // display on
#define CASET 0x2A // column address set
#define RASET 0x2B // row address set
#define RAMWR 0x2C // RAM write
#define MADCTL 0x36 // axis control

#endif
