///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                              ILI9341.c                            ////
////                                                                   ////
////               ILI9341 display driver for CCS C compiler           ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////               This is a free software with NO WARRANTY.           ////
////                     https://simple-circuit.com/                   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
/*
* This library works with the Adafruit 2.8" Touch Shield V2 (SPI)
*    http://www.adafruit.com/products/1651
* Adafruit 2.4" TFT LCD with Touchscreen Breakout w/MicroSD Socket - ILI9341
*    https://www.adafruit.com/product/2478
* 2.8" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket - ILI9341
*    https://www.adafruit.com/product/1770
* 2.2" 18-bit color TFT LCD display with microSD card breakout - ILI9340
*    https://www.adafruit.com/product/1770
* TFT FeatherWing - 2.4" 320x240 Touchscreen For All Feathers
*    https://www.adafruit.com/product/3315
*
* These displays use SPI to communicate, 4 or 5 pins are required
* to interface (RST is optional).
*
* Adafruit invests time and resources providing this open source code,
* please support Adafruit and open-source hardware by purchasing
* products from Adafruit!
*
*
* This library depends on <a href="https://github.com/adafruit/Adafruit_GFX">
* Adafruit_GFX</a> being present on your system. Please make sure you have
* installed the latest version before using this library.
*
* Written by Limor "ladyada" Fried for Adafruit Industries.
*
* BSD license, all text here must be included in any redistribution.
*
*/
#include "ILI9341.h"
#include "peripherals.h"
#include "board.h"
#include "fsl_gpio.h"
#include "pin_mux.h"




#define RST_HIGH() GPIO_PortSet(BOARD_ILI9341_RST_GPIO, 1U << BOARD_ILI9341_RST_PIN)
#define RST_LOW() GPIO_PortClear(BOARD_ILI9341_RST_GPIO, 1U << BOARD_ILI9341_RST_PIN)
#define DC_HIGH() GPIO_PortSet(BOARD_ILI9341_DC_GPIO, 1U << BOARD_ILI9341_DC_PIN)
#define DC_LOW() GPIO_PortClear(BOARD_ILI9341_DC_GPIO, 1U << BOARD_ILI9341_DC_PIN)






uint16_t
  _width,    ///< Display width as modified by current rotation
  _height;   ///< Display height as modified by current rotation
uint8_t
  rotation;  ///< Display rotation (0 thru 3)

  uint8_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_PIXFMT  , 1, 0x55,
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_DISPON  , 0x80,                // Display on
  0x00                                   // End of list
};





  _Bool pitIsrFlag = false;
  dspi_transfer_t masterXfer;
  uint8_t masterBuffer[] = {0};
  uint8_t buffer[2*ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT];



void pit_callback(void){

	PIT_StopTimer(PIT_1_PERIPHERAL, kPIT_Chnl_0);
	pitIsrFlag = true;
}




void delay150Ms(void){

	PIT_StartTimer( PIT_1_PERIPHERAL, kPIT_Chnl_0);
	while(!pitIsrFlag);
	pitIsrFlag = false;
}






/**************************************************************************/
/*!
    @brief  Call before issuing command(s) or data to display. Performs
            chip-select (if required). Required
            for all display types; not an SPI-specific function.
*/
/**************************************************************************/
//void startWrite(void) {
//    output_low(TFT_CS);
//}

/**************************************************************************/
/*!
    @brief  Call after issuing command(s) or data to display. Performs
            chip-deselect (if required). Required
            for all display types; not an SPI-specific function.
*/
/**************************************************************************/
//void endWrite(void) {
//    output_high(TFT_CS);
//}

/**************************************************************************/
/*!
    @brief  Write a single command byte to the display. Chip-select and
            transaction must have been previously set -- this ONLY sets
            the device to COMMAND mode, issues the byte and then restores
            DATA mode. There is no corresponding explicit writeData()
            function -- just use ILI9341_SPI_XFER().
    @param  cmd  8-bit command to write.
*/
/**************************************************************************/
void writeCommand(uint8_t cmd) {
  DC_LOW();

  /* Start master transfer, send data to slave */
  masterBuffer[0] = cmd;
  masterXfer.txData = masterBuffer;
  masterXfer.rxData = NULL;
  masterXfer.dataSize = 1U;
  masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
  DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);
  /* Then release DC pin */

  DC_HIGH();
}


void writeData(uint8_t data){

	  masterBuffer[0] = data;
	  masterXfer.txData = masterBuffer;
	  masterXfer.rxData = NULL;
	  masterXfer.dataSize = 1U;
	  masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
	  DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);
}



/**************************************************************************/
/*!
    @brief   Initialize ILI9341 chip
    Connects to the ILI9341 over SPI and sends initialization procedure commands
    @param    freq  Desired SPI clock frequency
*/
/**************************************************************************/
void tft_begin(void) {

//    #ifdef TFT_RST

      RST_HIGH();
      delay150Ms();
      RST_LOW();
      delay150Ms();
      RST_HIGH();
      delay150Ms();
//    #else                           // If no hardware reset pin...
//      writeCommand(ILI9341_SWRESET);  // Engage software reset
//      delay_ms(150);
//    #endif




    uint8_t cmd, x, numArgs;
    uint8_t *addr = initcmd;
    cmd = *addr++;
    while( cmd > 0 ) {

        writeCommand(cmd);

        x = *addr++;

        numArgs = x & 0x7F;

        while(numArgs--)
        	{
        		uint8_t aux_data;
        		aux_data= *addr++;
        		writeData(aux_data);
        	}
        if(x & 0x80){

        	delay150Ms();
        }
        cmd = *addr++;
    }


    _width  = ILI9341_TFTWIDTH;
    _height = ILI9341_TFTHEIGHT;
    rotation = 0;
}

/**************************************************************************/
/*!
    @brief   Set the "address window" - the rectangle we will write to RAM with the next chunk of SPI data writes. The ILI9341 will automatically wrap the data as each row is filled
    @param   x1  TFT memory 'x' origin
    @param   y1  TFT memory 'y' origin
    @param   w   Width of rectangle
    @param   h   Height of rectangle
*/
/**************************************************************************/
void setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h) {
    uint16_t x2 = (x1 + w - 1),
             y2 = (y1 + h - 1);
    writeCommand(ILI9341_CASET); // Column address set
    buffer[0]=x1 >> 8;
    buffer[1]=x1;
    buffer[2]=x2 >> 8;
    buffer[3]=x2;
	masterXfer.txData = buffer;
	masterXfer.rxData = NULL;
	masterXfer.dataSize = 4;
	masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
	DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);


    writeCommand(ILI9341_PASET); // Row address set
    buffer[0]=y1 >> 8;
    buffer[1]=y1;
    buffer[2]=y2 >> 8;
    buffer[3]=y2;
	masterXfer.txData = buffer;
	masterXfer.rxData = NULL;
	masterXfer.dataSize = 4;
	masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
	DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);

    writeCommand(ILI9341_RAMWR); // Write to RAM
}

/**************************************************************************/
/*!
    @brief  Set origin of (0,0) and orientation of TFT display
    @param  m  The index for rotation, from 0-3 inclusive
*/
/**************************************************************************/
void setRotation(uint8_t m)
{
  rotation = m % 4; // can't be higher than 3
    switch (rotation) {
        case 0:
            m = (MADCTL_MX | MADCTL_BGR);
            _width  = ILI9341_TFTWIDTH;
            _height = ILI9341_TFTHEIGHT;
            break;
        case 1:
            m = (MADCTL_MV | MADCTL_BGR);
            _width  = ILI9341_TFTHEIGHT;
            _height = ILI9341_TFTWIDTH;
            break;
        case 2:
            m = (MADCTL_MY | MADCTL_BGR);
            _width  = ILI9341_TFTWIDTH;
            _height = ILI9341_TFTHEIGHT;
            break;
        case 3:
            m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
            _width  = ILI9341_TFTHEIGHT;
            _height = ILI9341_TFTWIDTH;
            break;
    }

    writeCommand(ILI9341_MADCTL);
    writeData(m);
}
void drawPixel(uint16_t x, uint16_t y, uint16_t color) {
  if((x < _width) && (y < _height)) {

		setAddrWindow(x, y, 1, 1);
		buffer[0] = color >> 8;
		buffer[1] = color & 0xFF;
		masterXfer.txData = buffer;
		masterXfer.rxData = NULL;
		masterXfer.dataSize = 2;
		masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
		DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);
  }
}

/**************************************************************************/
/*!
   @brief    Draw a perfectly horizontal line (this is often optimized in a subclass!)
    @param    x   Left-most x coordinate
    @param    y   Left-most y coordinate
    @param    w   Width in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void drawHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color) {

	if( (x < _width) && (y < _height) && w)
	{
		uint8_t hi = color >> 8, lo = color;
		if((x + w - 1) >= _width)
			w = _width  - x;
		setAddrWindow(x, y, w, 1);

		for(uint32_t i=0;i<((2*w)-1);i++)
		{
			if(!(i%2))
			{
				buffer[i] = hi;
			}
			else
			{
				buffer[i] = lo;
			}
		}
		masterXfer.txData = buffer;
		masterXfer.rxData = NULL;
		masterXfer.dataSize = 2*w;
		masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
		DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);

//		while (w--)
//		{
//		  writeData(hi);
//		  writeData(lo);
//		}

	}
}

/**************************************************************************/
/*!
   @brief    Draw a perfectly vertical line (this is often optimized in a subclass!)
    @param    x   Top-most x coordinate
    @param    y   Top-most y coordinate
    @param    h   Height in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void drawVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color)
{
	if( (x < _width) && (y < _height) && h)
	{
		uint8_t hi = color >> 8, lo = color;
		if((y + h - 1) >= _height)
			h = _height - y;
		setAddrWindow(x, y, 1, h);

		for(uint32_t i=0;i<((2*h)-1);i++)
		{
			if(!(i%2))
			{
				buffer[i] = hi;
			}
			else
			{
				buffer[i] = lo;
			}
		}
		masterXfer.txData = buffer;
		masterXfer.rxData = NULL;
		masterXfer.dataSize = 2*h;
		masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
		DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);

//		while (h--)
//		{
//			writeData(hi);
//			writeData(lo);
//		}
	}
}
/**************************************************************************/
/*!
   @brief    Fill a rectangle completely with one color. Update in subclasses if desired!
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
	if(w && h) {                            // Nonzero width and height?
		uint8_t hi = color >> 8, lo = color;
		if((x >= _width) || (y >= _height))
		  return;
		if((x + w - 1) >= _width)
		  w = _width  - x;
		if((y + h - 1) >= _height)
		  h = _height - y;
		setAddrWindow(x, y, w, h);
		uint32_t px = (uint32_t)w * h;

		for(uint32_t i=0;i<((2*px)-1);i++)
		{
			if(!(i%2))
			{
				buffer[i] = hi;
			}
			else
			{
				buffer[i] = lo;
			}
		}
		masterXfer.txData = buffer;
		masterXfer.rxData = NULL;
		masterXfer.dataSize = (2*px);
		masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
		DSPI_MasterTransferBlocking(SPI_0_PERIPHERAL, &masterXfer);

//		while (px--) {
//		  writeData(hi);
//		  writeData(lo);
//		}
	}
}

/**************************************************************************/
/*!
   @brief    Fill the screen completely with one color. Update in subclasses if desired!
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void fillScreen(uint16_t color) {
    fillRect(0, 0, _width, _height, color);
}


uint16_t get_display_width(void)
{
	return _width;
}

uint16_t get_display_height(void)
{
	return _height;
}







/**************************************************************************/
/*!
    @brief  Invert the colors of the display (if supported by hardware).
            Self-contained, no transaction setup required.
    @param  i  true = inverted display, false = normal display.
*/
/**************************************************************************/
//void invertDisplay(bool i) {
//    startWrite();
//    writeCommand(i ? ILI9341_INVON : ILI9341_INVOFF);
//    endWrite();
//}

/**************************************************************************/
/*!
    @brief   Scroll display memory
    @param   y How many pixels to scroll display by
*/
///**************************************************************************/
//void tft_scrollTo(uint16_t y) {
//    startWrite();
//    writeCommand(ILI9341_VSCRSADD);
//    ILI9341_SPI_XFER(y >> 8);
//    ILI9341_SPI_XFER(y);
//    endWrite();
//}

/**************************************************************************/
/*!
   @brief  Read 8 bits of data from ILI9341 configuration memory. NOT from RAM!
           This is highly undocumented/supported, it's really a hack but kinda works?
    @param    command  The command register to read data from
    @param    index  The byte index into the command to read from
    @return   Unsigned 8-bit data read from ILI9341 register
*/
/**************************************************************************/
//uint8_t tft_readcommand8(uint8_t command, uint8_t index) {
//    startWrite();
//    writeCommand(0xD9);  // woo sekret command?
//    ILI9341_SPI_XFER(0x10 + index);
//    writeCommand(command);
//    uint8_t r = ILI9341_SPI_XFER(0xFF);
//    endWrite();
//    return r;
//}

/*!
    @brief  Essentially writePixel() with a transaction around it. I don't
            think this is in use by any of our code anymore (believe it was
            for some older BMP-reading examples), but is kept here in case
            any user code relies on it. Consider it DEPRECATED.
    @param  color  16-bit pixel color in '565' RGB format.
*/
//void pushColor(uint16_t color) {
//    uint8_t hi = color >> 8, lo = color;
//    startWrite();
//    ILI9341_SPI_XFER(hi);
//    ILI9341_SPI_XFER(lo);
//    endWrite();
//}

// end of code.
