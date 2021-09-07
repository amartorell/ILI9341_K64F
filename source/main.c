/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    lcd_test.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "test.h"
#include "ortega.h"
#include "carp.h"

/* TODO: insert other include files here. */
#include "GFX_Library.h"
#include "ILI9341.h"
/* TODO: insert other definitions and declarations here. */


#define DC_HIGH() GPIO_PortSet(BOARD_ILI9341_DC_GPIO, 1U << BOARD_ILI9341_DC_PIN)
/*
 * Test functions declarations
 */
typedef struct button_display_config{
	char * button_name;
	uint8_t text_size;
	uint8_t length_name;
	uint16_t background_color;
	uint16_t text_color;

}button_display_config_t;



// manejo playlist

void test_playlist2(char ** array, uint8_t size);
void test_playlist(void);
void disp_song_selected(char ** array, uint8_t size, int number);
void disp_song_unselected(char ** array, uint8_t size, int number);
//end manejo playlist


void testFillScreen(void);
void testText(void);
void testLines(uint16_t color);
void testFastLines(uint16_t color1, uint16_t color2);
void testRects(uint16_t color);
void testFilledRects(uint16_t color1, uint16_t color2);
void testFilledCircles(uint8_t radius, uint16_t color);
void testCircles(uint8_t radius, uint16_t color);
void testTriangles(void);
void testFilledTriangles(void);
void testRoundRects(void);
void testFilledRoundRects(void);

void test_rectangles(void);

void test_bubbles(void);
void test_button(uint16_t x, uint16_t y,button_display_config_t * button_config);
void test_print_image(void);

uint16_t i,j;
uint16_t bpm[160];
uint16_t oxy[160];
/*
 * @brief   Application entry point.
 */


char * word[]={"1 Future Nostalgia\n\r","2 Cool\n\r","3 Physical\n\r","4 Hola\n\r","5 Chau\n\r"};
#define PLAYLIST_ST_Y	49


int main(void) {

  	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");


    tft_begin();
    delay150Ms();
//    testFillScreen();
//
//
//    delay150Ms();
   button_display_config_t button_config = {
		   .background_color=ILI9341_RED,
		   .text_color=ILI9341_CYAN,
		   .text_size=2,
		   .button_name="tu vieja en tanga",
		   .length_name=14
   };

   button_display_config_t button_config_a = {
		   .background_color=ILI9341_RED,
		   .text_color=ILI9341_CYAN,
		   .text_size=2,
		   .button_name="no me la contes",
		   .length_name=12
   };

   button_display_config_t button_config_b = {
		   .background_color=ILI9341_GREEN,
		   .text_color=ILI9341_RED,
		   .text_size=2,
		   .button_name="test button",
		   .length_name=10
   };

//    test_rectangles();
//
    display_fillScreen(ILI9341_BLACK);
    //test_bubbles();
//    test_button(29,19,&button_config_b);
//   test_button(12, 100, &button_config);
//    test_button(12, 200, &button_config_a);
//    testText();
//    delay150Ms();
//
    //delay150Ms();
    //display_fillScreen(ILI9341_BLACK);
    //test_playlist();
    test_playlist2(word,5 );
   delay150Ms();
   disp_song_selected(word, 5, 0);
   disp_song_unselected(word, 5, 0);
   disp_song_selected(word, 5, 1);
   disp_song_unselected(word, 5, 1);
   disp_song_selected(word, 5, 2);
   disp_song_unselected(word, 5, 2);
   disp_song_selected(word, 5, 3);
   disp_song_unselected(word, 5, 3);

    //test_print_image();
//    testLines(ILI9341_CYAN);
//    delay150Ms();
//
//    testFastLines(ILI9341_RED, ILI9341_BLUE);
//    delay150Ms();
//
//    testRects(ILI9341_GREEN);
//    delay150Ms();
//
//    testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA);
//    delay150Ms();
//
//    testFilledCircles(10, ILI9341_MAGENTA);
//
//    testCircles(10, ILI9341_WHITE);
//    delay150Ms();
//
//    testTriangles();
//    delay150Ms();
//
//    testFilledTriangles();
//    delay150Ms();
//
//    testRoundRects();
//    delay150Ms();
//
//    testFilledRoundRects();
//    delay150Ms();

    return 0;
}

void PIT0_IRQHandler(void)
{
    /* Clear interrupt flag.*/
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	pit_callback();
}

void PIT1_IRQHandler(void)
{
//	GPIO_PortSet(BOARD_TEST_PIN_GPIO, 1U << BOARD_TEST_PIN_PIN);
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);
//	i++;
//	j++;
//	lcdGFX_updateGFX(bpm[i%160], oxy[i%160]);
//	if(!(j%40))
//	{
//		PIT_StopTimer(PIT_1_PERIPHERAL, kPIT_Chnl_1);
// 		lcdGFX_updateDATA(i%99, 82.34, 36.8);
// 		PIT_StartTimer(PIT_1_PERIPHERAL, kPIT_Chnl_1);
//	}
//	GPIO_PortClear(BOARD_TEST_PIN_GPIO, 1U << BOARD_TEST_PIN_PIN);
}
/*
 * Test functions
 */

void testFillScreen(void)
{
	display_fillScreen(ILI9341_GREEN);
//	display_fillScreen(ILI9341_RED);
//	display_fillScreen(ILI9341_GREEN);
//	display_fillScreen(ILI9341_BLUE);
//	display_fillScreen(ILI9341_BLACK);
}

void testText(void)
{
	display_fillScreen(ILI9341_BLACK);
	display_setCursor(0, 0);
	display_setTextColor(ILI9341_WHITE);
	display_setTextSize(1);
	display_printString("Hello World!\r\n");
	display_setTextColor(ILI9341_YELLOW);
	display_setTextSize(2);
	display_printString("1234.56\r\n");
	display_setTextColor(ILI9341_RED);
	display_setTextSize(3);
	display_printString("0xDEADBEEF\r\n");
	display_printString("\r\n");    // start a new line
	display_setTextColor(ILI9341_GREEN);
	display_setTextSize(5);
	display_printString("Groop\r\n");
	display_setTextSize(2);
	display_printString("I implore thee,\r\n");
	display_setTextSize(1);
	display_printString("my foonting turlingdromes.\r\n");
	display_printString("And hooptiously drangle me\r\n");
	display_printString("with crinkly bindlewurdles,\r\n");
	display_printString("Or I will rend thee\r\n");
	display_printString("in the gobberwarts\r\n");
	display_printString("with my blurglecruncheon,\r\n");
	display_printString("see if I don't!\r\n");
}

void testLines(uint16_t color) {
	int16_t x1, y1, x2, y2,
	w = get_display_width(),
	h = get_display_height();

	display_fillScreen(ILI9341_BLACK);

	x1 = 0; y1 = 0;
	y2 = h - 1;

	for(x2=0; x2<w; x2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}

	x2 = w - 1;
	for(y2=0; y2<h; y2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}

	display_fillScreen(ILI9341_BLACK);

	x1 = w - 1;
	y1 = 0;
	y2 = h - 1;

	for(x2=0; x2<w; x2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}

	x2    = 0;
	for(y2=0; y2<h; y2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}

	display_fillScreen(ILI9341_BLACK);

	x1 = 0;
	y1 = h - 1;
	y2 = 0;

	for(x2=0; x2<w; x2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}

	x2    = w - 1;
	for(y2=0; y2<h; y2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}

	display_fillScreen(ILI9341_BLACK);

	x1 = w - 1;
	y1 = h - 1;
	y2 = 0;

	for(x2=0; x2<w; x2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}

	x2 = 0;
	for(y2=0; y2<h; y2+=6)
	{
		display_drawLine(x1, y1, x2, y2, color);
	}
}

void testFastLines(uint16_t color1, uint16_t color2) {
	int16_t x, y, w = get_display_width(), h = get_display_height();

	display_fillScreen(ILI9341_BLACK);

	for(y=0; y<h; y+=5)
	{
		display_drawHLine(0, y, w, color1);
	}
	for(x=0; x<w; x+=5)
	{
		display_drawVLine(x, 0, h, color2);
	}
}

void testRects(uint16_t color)
{
	int16_t n, i, i2,
		  cx = get_display_width()  / 2,
		  cy = get_display_height() / 2;

	display_fillScreen(ILI9341_BLACK);
	n = min(get_display_width(), get_display_height());

	for(i=2; i<n; i+=6)
	{
		i2 = i / 2;
		display_drawRect(cx-i2, cy-i2, i, i, color);
	}
}

void test_rectangles(void){

	int cy= get_display_height()/4;

	display_fillScreen(ILI9341_BLACK);
	display_drawRect(1, get_display_height()-cy, get_display_width()-1, 20,ILI9341_RED );
	display_setCursor(2, get_display_height()-cy+2);
	display_setTextSize(2);
	display_setTextColor(ILI9341_DARKGREEN);
	display_printString("hola don jose\r\n");
	delay150Ms();
	delay150Ms();
	display_setCursor(2, get_display_height()-cy+2);
	display_printString("no me la conteiner");

}



void testFilledRects(uint16_t color1, uint16_t color2)
{
  int16_t n, i, i2,
          cx = get_display_width()  / 2 - 1,
          cy = get_display_height() / 2 - 1;

  display_fillScreen(ILI9341_BLACK);
  n = min(get_display_width(), get_display_height());
  for(i=n; i>0; i-=6)
  {
	  i2 = i / 2 - 1;
      display_fillRect(cx-i2, cy-i2, i, i, color1);

      // Outlines are not included in timing results
      display_drawRect(cx-i2, cy-i2, i, i, color2);
  }
}

void testFilledCircles(uint8_t radius, uint16_t color)
{
	int16_t x, y, w = get_display_width(), h = get_display_height(), r2 = radius * 2;

	display_fillScreen(ILI9341_BLACK);

	for(x=radius; x<w; x+=r2)
	{
		for(y=radius; y<h; y+=r2)
		{
			display_fillCircle(x, y, radius, color);
	    }
	}
}

void testCircles(uint8_t radius, uint16_t color)
{
	int16_t x, y, r2 = radius * 2,
		  w = get_display_width()  + radius,
		  h = get_display_height() + radius;

	for(x=0; x<w; x+=r2)
	{
		for(y=0; y<h; y+=r2)
		{
			display_drawCircle(x, y, radius, color);
		}
	}
}

void testTriangles(void)
{
  int16_t n, i, cx = get_display_width()  / 2 - 1,
          cy = get_display_height() / 2 - 1;
  uint16_t color = 0xF600;
  display_fillScreen(ILI9341_BLACK);
  n = min(cx, cy);

  for(i=0; i<n; i+=5)
  {
    display_drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      color);
    color += 100;
  }
}

void testFilledTriangles(void)
{
	int16_t i, cx = get_display_width()  / 2 - 1,
			 cy = get_display_height() / 2 - 1;

	display_fillScreen(ILI9341_BLACK);

	for(i=min(cx,cy); i>10; i-=5) {

	display_fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
	  display_color565(0, i*2, i*2));

	display_drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
	  display_color565(i*2, i*2, 0));

	}
}

void testRoundRects(void)
{
	int16_t w, i, i2,
		  cx = get_display_width()  / 2 - 1,
		  cy = get_display_height() / 2 - 1;

	display_fillScreen(ILI9341_BLACK);
	w = min(get_display_width(), get_display_height());

	for(i=0; i<w; i+=6) {
	i2 = i / 2;
	display_drawRoundRect(cx-i2, cy-i2, i, i, i/8, display_color565(i, 0, 0));
	}
}

void testFilledRoundRects(void)
{
	int16_t i, i2,
		  cx = get_display_width()  / 2 - 1,
		  cy = get_display_height() / 2 - 1;

	display_fillScreen(ILI9341_BLACK);

	for(i=min(get_display_width(), get_display_height()); i>20; i-=6) {
	i2 = i / 2;
	display_fillRoundRect(cx-i2, cy-i2, i, i, i/8, display_color565(0, i, 0));
	}
}

void test_bubbles(void){

	display_drawRoundRect(29, 19,150 ,18, 8, ILI9341_WHITE);
	display_fillRoundRect(30, 20, 150, 17, 8, ILI9341_GREEN);

	display_setCursor(38, 20);
	display_setTextSize(2);
	display_setTextColor(ILI9341_RED);
	display_printString("test button\r\n");


}
void test_button(uint16_t x, uint16_t y,button_display_config_t * button_config){

	display_drawRoundRect(x, y,((button_config->length_name))*(button_config->text_size)*8 ,(button_config->text_size)*8+2, 10, button_config->background_color);
	display_fillRoundRect(x+1, y+1,((button_config->length_name))*(button_config->text_size)*8 ,(button_config->text_size)*8+2, 10, button_config->background_color);


	display_setCursor(x+(button_config->text_size)*4, y+(button_config->text_size));
	display_setTextSize(button_config->text_size);
	display_setTextColor(button_config->text_color);
	display_printString(button_config->button_name);

}

void test_playlist(void){

	display_setCursor(2, 2);
	display_setTextSize(4);
	display_setTextColor(ILI9341_WHITE);
	display_printString("Playlist");

	display_setCursor(2, 49);
	display_setTextSize(2);
	display_setTextColor(ILI9341_RED);
	display_printString("1 Future Nostalgia\n\r");
	display_printString("2 Cool\n\r");
	display_printString("3 Physical\n\r");
	display_printString("4 Levitating\n\r");
	display_printString("5 Pretty Please\n\r");
	display_printString("6 Hallucinate\n\r");
	display_printString("7 Love Again\n\r");
	display_printString("8 Break My Heart\n\r");
	display_printString("9 Good in Bed\n\r");
	display_printString("10 Boys Will Be Boys\n");
	display_printString("11 Fever\n\r");
}


void test_playlist2(char ** array, uint8_t size){

	int i;

	display_setCursor(2, 2);
	display_setTextSize(4);
	display_setTextColor(ILI9341_WHITE);
	display_printString("Playlist");

	display_setCursor(0, PLAYLIST_ST_Y);
	display_setTextSize(2);
	display_setTextColor(ILI9341_RED);

	for(i=0;i < size; i++)
	{
		display_printString(array[i]);
	}

}
void disp_song_selected(char ** array, uint8_t size, int number){

	if(number <= size)
	{
		display_setCursor(0, PLAYLIST_ST_Y+number*8*2+1);
		display_setTextSize(2);
		display_setTextColor(ILI9341_GREEN);
		display_printString(array[number]);
	}
}
void disp_song_unselected(char ** array, uint8_t size, int number){

	if(number <= size)
	{
		display_setCursor(0, PLAYLIST_ST_Y+number*8*2+1);
		display_setTextSize(2);
		display_setTextColor(ILI9341_RED);
		display_printString(array[number]);
	}
}


void test_print_image(void){
	int i,j;

	for(i=0; i< 240; i++)
	{
		for(j=0; j< 320;j++){
			display_drawPixel(i,j,ortega[j][i]);
		}
	}
//	for(i=0; i< 240;i++)
//	{
//		for(j=0; j < 320; j++)
//		{
//			display_drawPixel(i,j,test[i][j]);
//		}
//	}
}


