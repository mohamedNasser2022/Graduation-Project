/*
 * Main.c
 *
 *  Created on: 4 Dec 2020
 *      Author: Mohamed
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"RCC_Interface.h"
#include"DIO_interface.h"
#include"ADC_interface.h"
#include"UART_interface.h"
#include"ESP_interface.h"
#include"ADC_private.h"
#include"DMA_interface.h"
#include"TFT_interface.h"
#include"TIMER_interface.h"
#include"SYSTICK_interface.h"
#include"TIMER_private.h"
#include"TOUCH_interface.h"

#include"math.h"


#define Error_Low 250
#define Error_max -250

volatile u16 System_Data[8]={0};
/*
 * [0] = X value
 * [1] = Y Value
 * [2] = Voltage Feedback
 * [3] = Current Feedback
 * [4] = Temperture Feedback
 * [5] = System_Status_Change
 * [6] = Duty cycle %
 * [7] = System_Status
 *
 * */

/*         	System_Status
 * bit 0 For system running or stopping
 * bit 1 For Touch State
 * bit 2 For Fault
 * bit 3 for Current Control Mood
 * bit 4 for Voltage Control Mood
 * bit 5 for Steady State happend*/


u16 TimerDuty=0; // Init Duty of timer
volatile u16	R_NTC;

void SamplingAndControl(void);
void Send_WIFI(void);
void FeedBack(u16 *System,u16 *Duty);
void Protection(u16* System);
u16 data[2] = {0,0};
u16 ADC1_Data[3];
void main()
{


	volatile u16 x,y,Volt,Cur,T;



	RCC_voidEnableClock(RCC_APB2,2); //Enable GPIOA
	RCC_voidEnableClock(RCC_APB2,3); //Enable GPIOB
	HTFT_voidInit();
	HTFT_voidShow();

	RCC_voidInitSystemClock();

	RCC_voidEnableClock(RCC_AHP,0);   //Enable DMA
	RCC_voidEnableClock(RCC_APB2,9);  //Enable ADC1
	RCC_voidEnableClock(RCC_APB2,10); // ADC2
	RCC_voidEnableClock(RCC_APB2,14); //Enable UART1

	RCC_voidEnableClock(RCC_APB2,11); // Timer 1
	RCC_voidEnableClock(RCC_APB1,2);  // Timer 4

	MSTK_voidInit();





	ADC2_voidInitADC();
	ADC2_voidSelectChannalRegular(0,1,0);
	ADC2_voidRegularLength(0);


	MGPIO_voidSetPinDirection(GPIOA,PIN2,INPUT_ANALOG); /*Volt*/
	MGPIO_voidSetPinDirection(GPIOA,PIN4,INPUT_ANALOG); /*Current 2.5A to 7.5 A*/
	MGPIO_voidSetPinDirection(GPIOA,PIN7,INPUT_ANALOG); /*Current Scale 2 0.5A up to 2.5 A*/
	MGPIO_voidSetPinDirection(GPIOA,PIN5,INPUT_ANALOG); /*Temp*/

	ADC_voidInitADC();
	ADC_voidSelectChannalRegular(0,1,0);
	ADC_voidRegularLength(0);

	//UART
	MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_50MHZ_AFPP);//TX
	MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);//RX
	MUSART_voidInit();



	//................................

	/*
	MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_50MHZ_AFPP);//TX
	MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);//RX
	MUSART_voidInit();
	HESP_voidESPInit();
	HESP_u8ESPWifiConnect("Thorn","abdalaze0m1WMA19");
	HESP_u8ESPConnectToServer("162.253.155.226");
	HESP_u8ReadData("49","http://supercharger.freevar.com/current.txt",CURRENT);
	HESP_u8ESPConnectToServer("162.253.155.226");
	HESP_u8ReadData("49","http://supercharger.freevar.com/voltage.txt",VOLTAGE);
	*/




	/* F system should be 4*8MHZ = 32 Mhz using PLL
	 * so timer ARR = 620 which has frequencey 25Khz
	 * at prescaler 2 of timer*/

	MGPIO_voidSetPinDirection(GPIOB,PIN7,OUTPUT_SPEED_2MHZ_PP); /*Relay*/
	MGPIO_voidSetPinValue(GPIOB,7,0);

	MGPIO_voidSetPinDirection(GPIOB,PIN6,OUTPUT_SPEED_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA,PIN8,OUTPUT_SPEED_10MHZ_PP);

	//Should be 0 for debugging
	/*MGPIO_voidSetPinValue(GPIOB,6,1);
	MGPIO_voidSetPinValue(GPIOA,8,1);*/

	MGPIO_voidSetPinValue(GPIOB,6,0);
	MGPIO_voidSetPinValue(GPIOA,8,0);

	MGPIO_voidSetPinDirection(GPIOB,PIN6,OUTPUT_SPEED_10MHZ_AFPP);//T4 C1
	TIMER_voidInitPWM(TIMER4,620,2);
	MGPIO_voidSetPinDirection(GPIOA,PIN8,OUTPUT_SPEED_10MHZ_AFPP);//T3 C1
	TIMER_voidInitPWM(TIMER1,620,2);
	TIMER_voidTimerShifting();

	while(!TIMER_u8TimerVerifyShiting());


	// For Debugging
	MGPIO_voidSetPinValue(GPIOB,7,0);
	TIMER1_voidPWMSetDuty(0);
	TIMER4_voidPWMSetDuty(0);

	MGPIO_voidSetPinValue(GPIOB,7,1);
	MSTK_voidSetBusyWait(100000*4);
	MGPIO_voidSetPinValue(GPIOB,7,0);




	volatile u16  R_Battery=0;

	const s16 B_NTC = -3950;
	MSTK_voidSetIntervalPeriodic(1000000*4,Send_WIFI);  //periodic calling

	while(1)
	{
		x=0;y=0;


		SamplingAndControl();

		R_NTC = (R_NTC*10*1000)/(5000-R_NTC); // Voltage 5 v applied on two resistor..
		volatile float x_TEST =log(((float)R_NTC/(10*1000)));
		T = ((-298/(((float)298/B_NTC*x_TEST)-1)) -273)*1000;
		R_Battery = Volt*1000/Cur;
		System_Data[4] = T;
		System_Data[6] = (TimerDuty*100)/310;

		if(System_Data[5]!=0)
		{
			if(GET_BIT(System_Data[7],2) == 1)
			{
				HTFT_voidShowChange(System_Data[7]);

				CLR_BIT(System_Data[5],2);
			}
			if((GET_BIT(System_Data[5],0) == 1)&&(GET_BIT(System_Data[7],0)==0&&GET_BIT(System_Data[7],2)==0))
			{
				SET_BIT(System_Data[7],0); // Runing system
				CLR_BIT(System_Data[5],0);
				MGPIO_voidSetPinValue(GPIOB,7,1);
				TIMER1_voidPWMSetDuty(TimerDuty);
				TIMER4_voidPWMSetDuty(TimerDuty);
				HTFT_voidShowChange(System_Data[7]);
			}
			else if((GET_BIT(System_Data[5],0) == 1)&&(GET_BIT(System_Data[7],0)==1))
			{
				CLR_BIT(System_Data[7],0); //Stopping system
				CLR_BIT(System_Data[7],5);
				CLR_BIT(System_Data[5],0);
				TimerDuty=0;
				TIMER1_voidPWMSetDuty(TimerDuty);
				TIMER4_voidPWMSetDuty(TimerDuty);
				MGPIO_voidSetPinValue(GPIOB,7,0);
				HTFT_voidShowChange(System_Data[7]&0x01);

			}
		}
	}
}

extern u16 voltage;
extern u16 Current;

void FeedBack(u16 *System,u16 *Duty)
{

	s16 Local_feedBack_Voltage = voltage - System[2] ;
	s16 Local_feedBack_Current = Current - System[3] ;
	if(GET_BIT(System[7],2) == 0)
	{
		if(GET_BIT(System[7],4)==1 && GET_BIT(System[7],3)==0){
			// Voltage Control
			if(((Local_feedBack_Voltage > Error_Low)) && (*Duty < 284))
			{
				*Duty = *Duty +1;
			}
			else if((Local_feedBack_Voltage < Error_max)&&(*Duty !=0))
			{
				*Duty = *Duty-1;
			}
			else{
				SET_BIT(System[7],5);
			}
			TIMER1_voidPWMSetDuty(*Duty);
			TIMER4_voidPWMSetDuty(*Duty);
			volatile u8 T1_T4 = TIMER_u8TimerVerifyShiting();
		}
		else if((GET_BIT(System[7],3)==1) && (GET_BIT(System[7],4)==0))
		{ // Current Control
			if(((Local_feedBack_Current > Error_Low)) && (*Duty < 284))
			{
				*Duty = *Duty +1;
			}
			else if((Local_feedBack_Current < Error_max)&&(*Duty !=0))
			{
				*Duty = *Duty-1;
			}
			else{
				SET_BIT(System[7],5);
			}
			TIMER1_voidPWMSetDuty(*Duty);
			TIMER4_voidPWMSetDuty(*Duty);
			volatile u8 T1_T4 = TIMER_u8TimerVerifyShiting();

		}
		else
		{

		}
	}


}

void Protection(u16* System)
{	// Calculate R
	volatile u16 LOCAL_R = (System[2]*1000)/System[3];
	if((LOCAL_R <= 200)&&(GET_BIT(System[5],2)==0)&&(GET_BIT(System[7],2)==0)&&(System[6]>2))
	{	//Fault detected
		SET_BIT(System[5],2);
	}
	else if((LOCAL_R <= 200)&&(GET_BIT(System[5],2)==1))
	{ 	//Fault actions premant fault
		TIMER1_voidPWMSetDuty(0);
		TIMER4_voidPWMSetDuty(0);
		SET_BIT(System[7],2);
		SET_BIT(System[5],0);
	}
	else if((LOCAL_R > 200)&&(GET_BIT(System[5],2)==1)&&GET_BIT(System[7],2)==0)
	{	//Fault Cleared
		CLR_BIT(System[5],2);
	}
	else
	{

	}

}

void SamplingAndControl(void)
{
	volatile u16 Volt,Cur,Cur1,Cur2;
	Volt =  ((ADC2_u16Conversion(2)*3300)/4096);
	Volt = Volt*9.84-2732;
	Cur1  =  (ADC2_u16Conversion(7)*3300)/4096; //Gain 99 0,2.5A
	Cur2  =  (ADC2_u16Conversion(4)*3300)/4096; //Gain 31 2.5,7A
	if(Cur1 <=2600)
	{
		Cur   = ((u32)Cur1*1000/990); //310
	}
	else
	{
		Cur   = ((u32)Cur2*1000/310); //310
	}

	R_NTC = (ADC2_u16Conversion(5)*3300)/4096;
	System_Data[2] = Volt; // Used in protection
	System_Data[3] = Cur;
	//Cur = Cur*2.801-576.92;
	HTOUCH_voidGetPoint(System_Data); //get X , Y from touch
	HTFT_voidScreenPressed(System_Data); // send data to tft to be proccess
	if(GET_BIT(System_Data[7],0))
	{
		if(TimerDuty > 10){
			Protection(System_Data);
		}
		FeedBack(System_Data,&TimerDuty);
	}
}
void Send_WIFI(void)
{
	MUSART_voidTransmitNumbers(0x80|(System_Data[2]/1000)); //Send Voltage
	MUSART_voidTransmitNumbers(System_Data[3]/1000);

}
