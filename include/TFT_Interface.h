/***************************************************************/
/*	Author : Mohamed Nasser					                   */
/*	Date   : 18 Feb 2021									   */
/*	Version: V02											   */
/***************************************************************/


#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

void HTFT_voidInit(void);
void HTFT_voidDisplayImage(const u16* copy_Image,u16 copy_u16Hight,u16 copy_u16With,u16 copy_u16Ystart,u16 copy_u16Yend,u16 copy_u16Xstart,u16 copy_u16Xend);
void HTFT_voidFillColor( u16 copy_u16Color);
void HTFT_voidDrawRect(u8 x1,u8 x2,u16 y1,u16 y2,u16 copy_u16Color);
void HTFT_VoidWriteNumber( u16* Cop_u16Char , u8 Xaxis , u16 Yaxis , u16 Copy_u8Color,u16 copy_u16BackGround );
void HTFT_voidTouched(u16* ptr);
void TFT_VidWriteChar( u8 * Cop_u8Char , u8 Xaxis , u16 Yaxis , u16 Copy_u8Color );
void HTFT_voidWriteString(u8 *copy_u8ptr,u8 Xaxis,u16 Yaxis, u16 Copy_u16Color,u16 copy_u16BackGround);
void HTFT_voidShow(void);
void HTFT_voidScreenPressed(u16* Position);
void HTFT_voidShowMeasurement(u8 operation,u16* Measurement);
void HTFT_voidShowChange(u8 copy_u8State);
static void Page_1(u8 operations);
static void Page2_Dynamic(u8 operations,u16* Position);
static void Page_Change(u16* Position);
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


#endif
