/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 24 Nov 2020									   */
/*	Version: V01  											   */
/***************************************************************/

#ifndef TOUCH_CONFIG_H
#define TOUCH_CONFIG_H
/*
To get Y coordinate :
XM_AN Set HIGH && Ym_D1 LOW and third input floating

To get X coordinate :
YM_AN 1 && Xm_D0 LOW and third floating
*/

#define Xm_D0 GPIOB,PIN12
#define Ym_D1 GPIOA,PIN3

#define XM_AN GPIOA,1 //CS ref to X
#define YM_AN GPIOA,0 //RS ref to Y

#define X 1
#define Y 0
#endif
