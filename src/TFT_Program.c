/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 06 July 2021									   */
/*	Version: V03											   */
/***************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SYSTICK_interface.h"


#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"
extern u16 data[2];
u8 TFT_Control = 0;
volatile u8 Pages = 0;
void HTFT_voidInit(void)
{
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D2,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D3,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D4,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D5,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D6,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D7,OUTPUT_SPEED_2MHZ_PP);

	MGPIO_voidSetPinDirection(TFT_W,OUTPUT_SPEED_2MHZ_PP); //w
	MGPIO_voidSetPinDirection(TFT_REST,OUTPUT_SPEED_10MHZ_PP); //Rest
	MGPIO_voidSetPinDirection(TFT_R,INPUT_FLOATING); //read

	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);

	MGPIO_voidSetPinValue(TFT_W,GPIO_HIGH);
	//MGPIO_voidSetPinValue(TFT_R,GPIO_HIGH);
	/*Reset Pulse*/
	MGPIO_voidSetPinValue(TFT_REST,GPIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_REST,GPIO_LOW);
	MSTK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(TFT_REST,GPIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_REST,GPIO_LOW);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_REST,GPIO_HIGH);
	MSTK_voidSetBusyWait(120000);

	// Sleep OUT
	voidWriteCommand(0x11);
	MSTK_voidSetBusyWait(150000);

	//
	/*	voidWriteCommand(0x0C);
		voidWriteData(0x55);*/

	//CLMODE
	voidWriteCommand(0x3A);
	voidWriteData(0x65);

	// Power
	voidWriteCommand(0xBF);
	voidWriteData(0x04);

	voidWriteCommand(0x36);

	voidWriteData(0x08);

	//led
	//voidWriteCommand(0xB9);
	//voidWriteData(0xFF);

	// Display on 
	voidWriteCommand(0x29);

}

void HTFT_voidFillColor( u16 copy_u16Color)
{


	u32 Counter=0;


	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(239); // 126 , 159

	// Y
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(319>>8); //0x01
	voidWriteData(319);  //0x3F

	voidWriteCommand(0x2C);

	for(Counter = 0; Counter<76800; Counter++)
	{

		voidWriteData(copy_u16Color>>8);
		voidWriteData(copy_u16Color& 0x00FF);

	}

}

void HTFT_voidDisplayImage(const u16* copy_Image,u16 copy_u16Hight,u16 copy_u16With,u16 copy_u16Ystart,u16 copy_u16Yend,u16 copy_u16Xstart,u16 copy_u16Xend)
{
	u32 LOCAL_NO_OF_PIXELS = copy_u16Hight*copy_u16With;
	u32 Counter=0;


	//  R4 R3 R2 R1 R0 G5 G4 G3 G2 G1 G0 B4 B3 B2 B1 B0
	// X
	voidWriteCommand(0x2A);
	voidWriteData(copy_u16Xstart>>8);
	voidWriteData(copy_u16Xstart);
	voidWriteData(copy_u16Xend>>8);
	voidWriteData(copy_u16Xend); // 126 , 159

	// Y
	voidWriteCommand(0x2B);
	voidWriteData(copy_u16Ystart>>8);
	voidWriteData(copy_u16Ystart);
	voidWriteData(copy_u16Yend>>8);
	voidWriteData(copy_u16Yend);

	voidWriteCommand(0x2C);

	for(Counter = 0; Counter<LOCAL_NO_OF_PIXELS;Counter++)
	{

		voidWriteData(copy_Image[Counter]>>8);
		voidWriteData(copy_Image[Counter]& 0x00FF);

	}
}

void HTFT_voidDrawRect(u8 x1,u8 x2,u16 y1,u16 y2,u16 copy_u16Color)
{

	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);

	u32 Size = (x2-x1)*(y2-y1);
	u32 Counter=0;


	voidWriteCommand(CASET);
	voidWriteData(0);
	voidWriteData(x1);
	voidWriteData(0);
	voidWriteData((x2-1));

	// Y
	voidWriteCommand(RASET);
	voidWriteData(y1>>8);
	voidWriteData(y1);
	voidWriteData((y2-1)>>8);
	voidWriteData((y2-1));

	voidWriteCommand(RAMWR);

	for(Counter = 0; Counter<Size;Counter++)
	{

		voidWriteData(copy_u16Color>>8);
		voidWriteData(copy_u16Color& 0x00FF);

	}

}


static void voidWriteCommand(u8 copy_u8Command)
{


	MGPIO_voidSetPinValue(TFT_RS,GPIO_LOW);
	/*Send Comand*/

	WriteDIO(copy_u8Command);


	MGPIO_voidSetPinValue(TFT_W,GPIO_LOW);

	MGPIO_voidSetPinValue(TFT_W,GPIO_HIGH);
	while(MGPIO_u8GetPinValue(TFT_R)==0);
}
static void WriteDIO(u8 copy_u8Command)
{
	MGPIO_voidSetPinValue(TFT_D0,GET_BIT(copy_u8Command,0));
	MGPIO_voidSetPinValue(TFT_D1,GET_BIT(copy_u8Command,1));
	MGPIO_voidSetPinValue(TFT_D2,GET_BIT(copy_u8Command,2));
	MGPIO_voidSetPinValue(TFT_D3,GET_BIT(copy_u8Command,3));
	MGPIO_voidSetPinValue(TFT_D4,GET_BIT(copy_u8Command,4));
	MGPIO_voidSetPinValue(TFT_D5,GET_BIT(copy_u8Command,5));
	MGPIO_voidSetPinValue(TFT_D6,GET_BIT(copy_u8Command,6));
	MGPIO_voidSetPinValue(TFT_D7,GET_BIT(copy_u8Command,7));

}
static void voidWriteData(u8 copy_u8Data)
{


	MGPIO_voidSetPinValue(TFT_RS,GPIO_HIGH);//send data
	WriteDIO(copy_u8Data); // write DIO
	MGPIO_voidSetPinValue(TFT_W,GPIO_LOW); // start read
	MGPIO_voidSetPinValue(TFT_W,GPIO_HIGH);
	while(MGPIO_u8GetPinValue(TFT_R)==0); // wait until reading finish

}


static void TFT_voidWriteChar( u8 * Cop_u8Char , u8 Xaxis , u16 Yaxis , u16 Copy_u16Color,u16 copy_u16BackGround )
{
	u8  LOC_u8Mask = 0x01 ;
	u8  LOC_u8DataMasked  ;
	u16 LOC_u8Pixel       ;
	for( u8 LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 5 ; LOC_u8Iterator1++ ){
		for( u8 LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < 8 ; LOC_u8Iterator2++ ){
			/* Set The Position Of 5x7 Character */
			voidWriteCommand( CASET ); // set column range (x0,x1)
			voidWriteData( (Xaxis +  LOC_u8Iterator1)>>8 );
			voidWriteData(  Xaxis +  LOC_u8Iterator1 );
			voidWriteData(240>>8);
			voidWriteData(240);
			voidWriteCommand( RASET ); // set row range (y0,y1)
			voidWriteData( (Yaxis +  LOC_u8Iterator2)>>8 );
			voidWriteData( Yaxis +  LOC_u8Iterator2 );
			voidWriteData(319>>8);
			voidWriteData(319);
			voidWriteCommand( RAMWR ); // memory write
			LOC_u8DataMasked = Cop_u8Char[ LOC_u8Iterator1 ] & LOC_u8Mask ;
			if( LOC_u8DataMasked == 0  ) { LOC_u8Pixel = copy_u16BackGround   ; }
			else                         { LOC_u8Pixel = Copy_u16Color ; }
			voidWriteData ( LOC_u8Pixel >> 8   ); // write hi byte
			voidWriteData ( LOC_u8Pixel & 0xFF ); // write lo byte
			LOC_u8Mask <<= 1 ;
		}

		LOC_u8Mask = 0x01 ;
	}
}

void HTFT_VoidWriteNumber( u16* Cop_u16Char , u8 Xaxis , u16 Yaxis , u16 Copy_u8Color,u16 copy_u16BackGround )
{


	u16  LOC_u16Mask = 0x01 ;
	u16  LOC_u16DataMasked  ;
	u16  LOC_u16Pixel       ;

	for( u8 LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 9 ; LOC_u8Iterator1++ ){

		for( u8 LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < 16 ; LOC_u8Iterator2++ ){

			/* Set The Position Of 5x7 Character */
			voidWriteCommand( CASET ); // set column range (x0,x1)

			voidWriteData( (Xaxis +  LOC_u8Iterator1)>>8 );
			voidWriteData(  Xaxis +  LOC_u8Iterator1 );
			voidWriteData(240>>8);
			voidWriteData(240);

			voidWriteCommand( RASET ); // set row range (y0,y1)

			voidWriteData( (Yaxis +  LOC_u8Iterator2)>>8 );
			voidWriteData( Yaxis +  LOC_u8Iterator2 );
			voidWriteData(319>>8);
			voidWriteData(319);

			voidWriteCommand( RAMWR ); // memory write

			LOC_u16DataMasked = Cop_u16Char[ LOC_u8Iterator1 ] & LOC_u16Mask ;

			if( LOC_u16DataMasked == 0  ) { LOC_u16Pixel = copy_u16BackGround    ; }
			else                         { LOC_u16Pixel = Copy_u8Color ; }

			voidWriteData ( LOC_u16Pixel >> 8   ); // write hi byte
			voidWriteData ( LOC_u16Pixel & 0xFF ); // write lo byte

			LOC_u16Mask <<= 1 ;

		}

		LOC_u16Mask = 0x01 ;

	}

}
void HTFT_voidTouched(u16* ptr)
{
	u16 Local_X = ptr[0];
	u16 Loacl_Y = ptr[1];
	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);

	voidWriteCommand( CASET ); // set column range (x0,x1)

	voidWriteData( Local_X>>8 );
	voidWriteData(  Local_X );
	voidWriteData(240>>8);
	voidWriteData(240);

	voidWriteCommand( RASET ); // set row range (y0,y1)

	voidWriteData( Loacl_Y>>8 );
	voidWriteData( Loacl_Y );
	voidWriteData(319>>8);
	voidWriteData(319);

	voidWriteCommand( RAMWR ); // memory write

	voidWriteData ( RED >> 8   );
	voidWriteData ( RED & 0xFF );


}

void HTFT_voidWriteString(u8 *copy_u8ptr,u8 Xaxis,u16 Yaxis, u16 Copy_u16Color,u16 copy_u16BackGround)
{
	u8 Local_counter = 0;
	while(copy_u8ptr[Local_counter] != '\0')
	{
		for(u8 i=0; i<17;i++)
		{
			if(copy_u8ptr[Local_counter] == Char[i][5])
			{
				TFT_voidWriteChar(Char[i],Xaxis+6*Local_counter,Yaxis,Copy_u16Color,copy_u16BackGround);
			}
		}
		Local_counter++;
	}
}


u16 voltage = 0;
u16 Current = 0;

void HTFT_voidKeyPad(u16 *copy_u16ptr)
{
	static u16 Curs_V[2] = {92,281};
	static u16 Curs_C[2] = {92,231};
	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);
	u16 Local_X =copy_u16ptr[0]; // x
	u16 Local_Y =copy_u16ptr[1]; //Y


	if((Local_X>=90)&&(Local_X<=139)&&(Local_Y>=30)&&(Local_Y<=109))
	{
		for(u8 i = 0 ; i<12 ;i++)
		{
			if((Local_X>=Numbers[i][10])&&(Local_X<=Numbers[i][10]+8)&&(Local_Y>=Numbers[i][11])&&(Local_Y<=Numbers[i][11]+15))
			{
				if(Numbers[i][9] != 'C')
				{
					if(TFT_Control == 1)
					{	/*Volt*/
						voltage = (Numbers[i][9]-0x30) + voltage*10;
						HTFT_voidWriteValue(voltage,Curs_V[0],Curs_V[1],BLUE,WHITE);
					}
					else if(TFT_Control == 0)
					{ /*Current*/
						if(Current<7500){
							Current = (Numbers[i][9]-0x30) + Current*10;
							HTFT_voidWriteValue(Current,Curs_C[0],Curs_C[1],RED,WHITE);
						}
						else
						{
							//error
						}
					}
				}
				else
				{
					voltage = 0;
					Current = 0;
					HTFT_voidDrawRect(82,180,280,300,WHITE);
					HTFT_voidDrawRect(82,180,230,250,WHITE);
					//HTFT_voidDrawRect(130,180,155,201,BLACK);
					if(GET_BIT(copy_u16ptr[7],2))
					{
						CLR_BIT(copy_u16ptr[5],2);
						CLR_BIT(copy_u16ptr[7],2);
						HTFT_voidDrawRect(200,220,70,80,BLACK);
					}

				}
			}
		}
	}

}



void HTFT_voidWriteValue(u16 copy_u16Number,u8 GetX,u16 GetY,u16 Copy_u16Color,u16 copy_u16BackGround)
{
	volatile u16 Loca_Number = copy_u16Number;
	volatile u16 Local_Fraction = 0;
	volatile u16 Local_Fraction1 = 0;
	volatile u16 Local_Fraction_Constant = 0;
	volatile u16 Loca_Number1 = 0;
	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);
	u8 digit = 0;
	u8 Zero_I=0;
	u8 Zeros_F_Right = 0; // 100 = 1
	u8 Zeros_F_Value = 0; // 100 = 1
	u8 Zero_F=0;
	u8 Local_Enable_Fraction=0;
	if(Loca_Number>=1000)
	{
		Local_Fraction = Loca_Number;
		Local_Enable_Fraction=1;
		while(Local_Fraction >1000)
		{
			Local_Fraction = Local_Fraction-1000;

		}
		Loca_Number/=1000;
	}
	else
	{
		Local_Fraction = Loca_Number;
	}
	Local_Fraction_Constant = Local_Fraction;

	while(Loca_Number !=0 ||Local_Fraction!=0 )
	{

		if(Zero_F ==0&&Local_Fraction>=100)
		{
			Zeros_F_Right = 1;  //500
		}


		Local_Fraction1 = Local_Fraction%10 + Local_Fraction1*10;
		Local_Fraction/=10;
		if(Local_Fraction1 == 0 )
		{
			Zero_F++;

		}
		if(Local_Enable_Fraction == 1 &&Loca_Number!=0){
			Loca_Number1 = Loca_Number%10 + Loca_Number1*10;
			Loca_Number /= 10;
			if(Loca_Number1 ==0 && Zero_I ==0)
			{
				Zero_I=1;
			}

		}
		else if(Local_Enable_Fraction==0)
		{
			Loca_Number = Local_Fraction;
		}
	}
	if(Local_Fraction_Constant <100)
	{
		if(Local_Fraction_Constant<10)
		{
			Local_Fraction1 = Local_Fraction1*100;
		}
		else{
			Local_Fraction1 = Local_Fraction1*10;
		}
	}

	do
	{
		for(u8 i=0 ; i<N;i++)
		{
			if(Loca_Number1%10 == (Numbers[i][9]-0x30))
			{
				HTFT_VoidWriteNumber(Numbers[i],GetX + digit*10,GetY,Copy_u16Color,copy_u16BackGround);
				Loca_Number1 /=10;
				digit++;
				if(Zero_I == 1 && digit == 1)
				{//printe zero
					HTFT_VoidWriteNumber(Numbers[10],GetX + digit*10,GetY,Copy_u16Color,copy_u16BackGround);
					digit++;
				}
				if(Loca_Number1 == 0&&Local_Fraction1 != 0)
				{
					HTFT_VoidWriteNumber(Numbers[11],GetX + digit*10,GetY,Copy_u16Color,copy_u16BackGround);
					digit++;
					Zero_I=0;
					Loca_Number1 = Local_Fraction1;
					Local_Fraction1=0;
					if(Zeros_F_Right ==0)
					{
						while(Zero_F){
							HTFT_VoidWriteNumber(Numbers[10],GetX + digit*10,GetY,Copy_u16Color,copy_u16BackGround);
							digit++;
							Zero_F--;}

					}
					else
					{

					}


				}


				break;
			}

		}
		if(Loca_Number1==0)
		{
			break;
		}
	}
	while(Loca_Number1 != 0 );

}

void HTFT_voidShow(void)
{
	HTFT_voidFillColor(BLACK);
	Page_1(1);

}
static void Page_1(u8 operations)
{
	if(operations==1){
		SET_BIT(Pages,0); //which page is current used
		HTFT_voidWriteString("SET VOLT",10,285,BLUE,BLACK);
		HTFT_voidWriteString("SET CURRENT",10,235,RED,BLACK);
		HTFT_voidWriteString("MOE",10,125,GREEN,BLACK);
		HTFT_voidDrawRect(82,180,280,300,WHITE); //Volt
		HTFT_voidDrawRect(82,180,230,250,WHITE); //Current
		//.....
		HTFT_voidDrawRect(200,220,265,275,BLUE);
		HTFT_voidWriteString("SET",201,265,GREEN,BLUE);
		//......
		HTFT_voidDrawRect(200,220,50,60,BLUE);
		HTFT_voidWriteString("RUN",201,50,GREEN,BLUE);
		HTFT_voidDrawRect(230,235,50,55,RED);
		//.........
		TFT_Control = 0;

		HTFT_VoidWriteNumber(Number_Cli,200,170,RED,BLACK);

		for(u8 i=0; i<11; i++)
		{
			/*printing Keypad*/
			HTFT_VoidWriteNumber( Numbers[i], Numbers[i][10], Numbers[i][11] , GREEN,BLACK);

		}
	}
	else if(operations==0)
	{
		CLR_BIT(Pages,0);
		HTFT_voidWriteString("SET VOLT",10,285,BLACK,BLACK);
		HTFT_voidWriteString("SET CURRENT",10,235,BLACK,BLACK);
		//HTFT_voidWriteString("MOE",10,125,BLACK,BLACK);
		HTFT_voidDrawRect(82,180,280,300,BLACK); //Volt
		HTFT_voidDrawRect(82,180,230,250,BLACK); //Current
		//.....
		HTFT_voidDrawRect(200,220,265,275,BLACK);
		HTFT_voidWriteString("SET",201,265,BLACK,BLACK);
		//......
		HTFT_voidDrawRect(200,220,50,60,BLACK);
		HTFT_voidWriteString("RUN",201,50,BLACK,BLACK);
		HTFT_voidDrawRect(230,235,50,55,BLACK);
		//.........
		TFT_Control = 0;

		HTFT_VoidWriteNumber(Number_Cli,200,170,BLACK,BLACK);

		for(u8 i=0; i<11; i++)
		{
			/*printing Keypad*/
			HTFT_VoidWriteNumber( Numbers[i], Numbers[i][10], Numbers[i][11] , BLACK,BLACK);

		}

	}
}

static void Page2_Dynamic(u8 operations,u16* Position)
{
	if(operations==1){
		SET_BIT(Pages,1);
		HTFT_voidWriteString("VOLT    ",10,280,GREEN,BLACK); // Voltage Reading
		HTFT_voidWriteString("CURRENT ",10,260,GREEN,BLACK); // Current Reading
		HTFT_voidWriteString("TEMP    ",10,240,GREEN,BLACK); // Temp Reading
		HTFT_voidWriteString("UT      ",10,220,GREEN,BLACK); // Duty Reading
		HTFT_voidWriteString("VOLT    V VALUE",10,185,GREEN,BLACK);
		HTFT_voidWriteString("CURRENT I VALUE",10,155,GREEN,BLACK);
		HTFT_voidWriteValue(data[0],130,185,GREEN,BLACK);
		HTFT_voidWriteValue(data[1],130,155,GREEN,BLACK);
	}
	else if(operations==3)
	{
		//measurement
		HTFT_voidShowMeasurement(1,Position);
	}
	else if(operations == 0)
	{
		CLR_BIT(Pages,1);
		HTFT_voidWriteString("VOLT    ",10,280,BLACK,BLACK); // Voltage Reading
		HTFT_voidWriteString("CURRENT ",10,260,BLACK,BLACK); // Current Reading
		HTFT_voidWriteString("TEMP    ",10,240,BLACK,BLACK); // Temp Reading
		HTFT_voidWriteString("UT      ",10,220,BLACK,BLACK); // Duty Reading
		HTFT_voidWriteString("VOLT    V VALUE",10,185,BLACK,BLACK);
		HTFT_voidWriteString("CURRENT I VALUE",10,155,BLACK,BLACK);
		HTFT_voidWriteValue(data[0],130,185,BLACK,BLACK);
		HTFT_voidWriteValue(data[1],130,155,BLACK,BLACK);
		HTFT_voidShowMeasurement(0,Position);
	}
}

void HTFT_voidScreenPressed(u16* Position)
{

	if((Position[0]!=0)&&(Position[1]!=0))
	{
		Page_Change(Position);
		if(GET_BIT(Pages,0)==1)
		{
			if((Position[0]<240 && Position[1]<320))
			{
				HTFT_voidKeyPad(Position);
				HTFT_voidSelection(Position);
				HTFT_voidSystemState(Position);
			}
		}
	}
	if(GET_BIT(Pages,1)==1)
	{
		Page2_Dynamic(3,Position);
	}
}
static void Page_Change(u16* Position)
{
	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);
	u16 Local_X =Position[0]; // x
	u16 Local_Y =Position[1]; //Y
	if((Local_X>=0)&&(Local_X<=20)&&(Local_Y>=0)&&(Local_Y<=320))
	{ //you are in page 2 and want to return to page 1
		Page2_Dynamic(0,Position); //Delete page 2
		Page_1(1); // Create page 1
	}
	else if((Local_X>=220)&&(Local_X<=240)&&(Local_Y>=0)&&(Local_Y<=320))
	{ //you are in page 1 and want to return to page 2
		Page_1(0); // Delete page 1
		Page2_Dynamic(1,Position); //Create page 2

	}


}

void HTFT_voidShowChange(u8 copy_u8State)
{
	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);
	if(GET_BIT(copy_u8State,0)==1&&GET_BIT(copy_u8State,2)==0)
	{
		//System Running
		HTFT_voidDrawRect(200,226,50,60,BLACK);
		HTFT_voidDrawRect(200,226,50,60,BLUE);
		HTFT_voidWriteString("STOP",201,50,GREEN,BLUE);
		HTFT_voidDrawRect(230,235,50,55,GREEN); //LAMP

	}
	else if(GET_BIT(copy_u8State,0)==0&&GET_BIT(copy_u8State,2)==0)
	{
		HTFT_voidDrawRect(200,226,50,60,BLACK);
		HTFT_voidDrawRect(200,220,50,60,BLUE);
		HTFT_voidWriteString("RUN",201,50,GREEN,BLUE);
		HTFT_voidDrawRect(230,235,50,55,RED); // LAMP
	}
	else if(GET_BIT(copy_u8State,2)==1)
	{
		HTFT_voidWriteString("RRR",201,70,RED,BLACK);
	}



}

void HTFT_voidSystemState(u16* copy_u16ptr)
{
	MGPIO_voidSetPinDirection(TFT_RS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_CS,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D0,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(TFT_D1,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(TFT_CS,0);
	u16 Local_X =copy_u16ptr[0]; // x
	u16 Local_Y =copy_u16ptr[1]; //Y
	u16 Local_Data = copy_u16ptr[5];
	if((Local_X>=200)&&(Local_X<=220)&&(Local_Y>=50)&&(Local_Y<=60))
	{
		if(GET_BIT(copy_u16ptr[5],0)==0){
			SET_BIT(copy_u16ptr[5],0);
		}

	}
}

extern SamplingAndControl;
void HTFT_voidShowMeasurement(u8 operation,u16* Measurement)
{	static u8 Volt = 0;
static u8 Current =0 ;
if(operation==1)
{
	if((Volt==Measurement[2])&&(Current==Measurement[3]))
	{

	}
	else
	{

		//Write volt
		HTFT_voidDrawRect(75,140,280,300,BLACK); //Clear 20*20 Black
		HTFT_voidWriteValue(Measurement[2],75,280,GREEN,BLACK); //Write

		//write Current
		HTFT_voidDrawRect(75,140,260,280,BLACK); // Clear
		HTFT_voidWriteValue(Measurement[3],75,260,GREEN,BLACK);

		//Temp
		HTFT_voidDrawRect(75,95,240,260,BLACK);//Clear
		HTFT_voidWriteValue(Measurement[4],75,240,GREEN,BLACK);

		//.. Duty
		HTFT_voidDrawRect(75,95,220,240,BLACK);
		HTFT_voidWriteValue(Measurement[6],75,220,GREEN,BLACK);



		Volt    = Measurement[2];
		Current = Measurement[3];

	}
}
else if(operation==0)
{
	//Write volt
	HTFT_voidDrawRect(75,140,280,300,BLACK); //Clear 20*20 Black
	//write Current
	HTFT_voidDrawRect(75,140,260,280,BLACK); // Clear
	//Temp
	HTFT_voidDrawRect(75,140,240,260,BLACK);//Clear
	//.. Duty
	HTFT_voidDrawRect(75,140,220,240,BLACK);


}
}

void HTFT_voidSelection(u16* Position)
{
	u16 Local_X =Position[0]; // x
	u16 Local_Y =Position[1]; //Y

	if((Local_X>=200&&Local_X<=209)&&((Local_Y>=170)&&(Local_Y<186)))
	{
		if(TFT_Control ==0)
		{
			TFT_Control = 1;
			HTFT_VoidWriteNumber(Number_Cli,200,170,BLUE,BLACK);

		}
		else
		{
			TFT_Control = 0;
			HTFT_VoidWriteNumber(Number_Cli,200,170,RED,BLACK);
		}

	}
	else if(((Local_X>=200)&&(Local_X<=220))&&((Local_Y>=265)&&(Local_Y<=280)))
	{
		//SET is Pressed
		data[0] = voltage;
		data[1] = Current;
	}
	else if(((Local_X>=10)&&(Local_X<=30))&&((Local_Y>=125)&&(Local_Y<=145)))
	{	//Mode Is Pressed
		if((GET_BIT(Position[7],3)==0)&&(GET_BIT(Position[7],4)==0))
		{	//Current MODE
			SET_BIT(Position[7],3); //Activate Current
			HTFT_voidWriteString("CURRENT",50,125,GREEN,BLACK);
		}
		else if((GET_BIT(Position[7],3)==1)&&(GET_BIT(Position[7],4)==0))
		{
			//Voltage MODE
			SET_BIT(Position[7],4); //Activate Volt
			CLR_BIT(Position[7],3); //Deactivate Current
			HTFT_voidDrawRect(50,125,125,135,BLACK);
			HTFT_voidWriteString("VOLT",50,125,GREEN,BLACK);

		}
		else if((GET_BIT(Position[7],3)==0)&&(GET_BIT(Position[7],4)==1))
		{
			//Voltage MODE
			SET_BIT(Position[7],4); //Activate Volt
			SET_BIT(Position[7],3); //Activate Current
			HTFT_voidDrawRect(50,125,125,135,BLACK);
			HTFT_voidWriteString("VOLT CURRENT",50,125,GREEN,BLACK);

		}
		else if((GET_BIT(Position[7],3)==1)&&(GET_BIT(Position[7],4)==1))
		{
			//Voltage MODE
			CLR_BIT(Position[7],4); //deactivate Volt
			CLR_BIT(Position[7],3); //Activate Current
			HTFT_voidDrawRect(50,125,125,135,BLACK);
			//HTFT_voidWriteString("CURRENT",50,125,GREEN,BLACK);

		}
	}


}

