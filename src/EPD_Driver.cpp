/*
	EPD_Driver.cpp
	
	--COPYRIGHT--
  * Brief The drivers and functions of development board
  * Copyright (c) 2012-2021 Pervasive Displays Inc. All rights reserved.
  *  Authors: Pervasive Displays Inc.
  *  Redistribution and use in source and binary forms, with or without
  *  modification, are permitted provided that the following conditions
  *  are met:
  *  1. Redistributions of source code must retain the above copyright
  *     notice, this list of conditions and the following disclaimer.
  *  2. Redistributions in binary form must reproduce the above copyright
  *     notice, this list of conditions and the following disclaimer in
  *     the documentation and/or other materials provided with the
  *     distribution.
  *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if defined(ENERGIA)
#include "Energia.h"
#else
#include "Arduino.h"
#endif

#include "EPD_Driver.h"

// ---------- PUBLIC FUNCTIONS -----------

EPD_Driver::EPD_Driver(eScreen_EPD_t eScreen_EPD, pins_t board)
{
	spi_basic = board;
	
	// Type
	pdi_cp = (uint16_t) eScreen_EPD;
	pdi_size = (uint16_t) (eScreen_EPD >> 8);

	uint16_t _screenSizeV = 0;
	uint16_t _screenSizeH = 0;
	uint16_t _screenDiagonal = 0;
	uint16_t _refreshTime = 0;
	
    switch (pdi_size)
    {
        case 0x15: // 1.54"

            _screenSizeV = 152; // vertical = wide size
            _screenSizeH = 152; // horizontal = small size
            _screenDiagonal = 154;
            _refreshTime = 16;
            break;
			
		case 0x20: // 2.06"

            _screenSizeV = 248; // vertical = wide size
            _screenSizeH = 128; // horizontal = small size
            _screenDiagonal = 206;
            _refreshTime = 15;
            break;

        case 0x21: // 2.13"

            _screenSizeV = 212; // vertical = wide size
            _screenSizeH = 104; // horizontal = small size
            _screenDiagonal = 213;
            _refreshTime = 15;
            break;

        case 0x26: // 2.66"

            _screenSizeV = 296; // vertical = wide size
            _screenSizeH = 152; // horizontal = small size
            _screenDiagonal = 266;
            _refreshTime = 15;
            break;

        case 0x27: // 2.71"

            _screenSizeV = 264; // vertical = wide size
            _screenSizeH = 176; // horizontal = small size
            _screenDiagonal = 271;
            _refreshTime = 19;
            break;

        case 0x28: // 2.87"

            _screenSizeV = 296; // vertical = wide size
            _screenSizeH = 128; // horizontal = small size
            _screenDiagonal = 287;
            _refreshTime = 14;
            break;
			
		case 0x29: // 2.9"

            _screenSizeV = 384; // vertical = wide size
            _screenSizeH = 168; // horizontal = small size
            _screenDiagonal = 290;
            _refreshTime = 14;
            break;

        case 0x37: // 3.70"

            _screenSizeV = 416; // vertical = wide size
            _screenSizeH = 240; // horizontal = small size
            _screenDiagonal = 370;
            _refreshTime = 15; // ?
            break;

        case 0x41: // 4.17"

            _screenSizeV = 300; // vertical = wide size
            _screenSizeH = 400; // horizontal = small size
            _screenDiagonal = 417;
            _refreshTime = 19;
            break;

        case 0x43: // 4.37"

            _screenSizeV = 480; // vertical = wide size
            _screenSizeH = 176; // horizontal = small size
            _screenDiagonal = 437;
            _refreshTime = 21;
            break;

        default:

            break;
    }

    // Force conversion for two unit16_t multiplication into uint32_t.
    // Actually for 1 colour; BWR requires 2 pages.
    image_data_size = (uint32_t) _screenSizeV * (uint32_t) (_screenSizeH / 8);

	// Config registers according to screen size
	memcpy(register_data, register_data_sm, sizeof(register_data_sm));
}

// CoG initialization function
//		Implements Tcon (COG) power-on and temperature input to COG
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::COG_initial_GU()
{	
	pinMode( spi_basic.panelBusy, INPUT );     //All Pins 0
	
	pinMode( spi_basic.panelDC, OUTPUT );
	digitalWrite(spi_basic.panelDC, HIGH);
	pinMode( spi_basic.panelReset, OUTPUT );
	digitalWrite(spi_basic.panelReset, HIGH);
	pinMode( spi_basic.panelCS, OUTPUT );
	digitalWrite(spi_basic.panelCS, HIGH);

	#if defined(ENERGIA)
	{
		SPI.begin();
		SPI.setDataMode(SPI_MODE0);
		SPI.setClockDivider(SPI_CLOCK_DIV32);
		// SPI.setClockDivider(16000000 / min(16000000, 4000000));
		SPI.setBitOrder(MSBFIRST);
	}
	#else
	{
		SPISettings _settingScreen;
		_settingScreen = {8000000, MSBFIRST, SPI_MODE0};
		SPI.begin();
		SPI.beginTransaction(_settingScreen);
	}
	#endif

	// Power On COG driver sequence
	_reset(5, 5, 10, 20);
	
	_softReset();
	delay(5);
	const uint8_t temp_in = register_data[2];
	_sendIndexData( 0xe5, &temp_in, 1 );  //Input Temperature: 25C
	_sendIndexData( 0xe0, &register_data[3], 1 );  //Active Temperature
	
	if (pdi_size == 0x29)
	{
		const uint8_t settings[] = {0x55, 0x02};
		_sendIndexData( 0x4d, &settings[0], 1);
		_sendIndexData( 0xe9, &settings[1], 1);
	}
	else
	{
		_sendIndexData( 0x00, &register_data[4], 2);  //PSR	>> consult Application Note on Reading OTP
	}
}

void EPD_Driver::COG_initial_FU()
{	
	pinMode( spi_basic.panelBusy, INPUT );     //All Pins 0
	
	pinMode( spi_basic.panelDC, OUTPUT );
	digitalWrite(spi_basic.panelDC, HIGH);
	pinMode( spi_basic.panelReset, OUTPUT );
	digitalWrite(spi_basic.panelReset, HIGH);
	pinMode( spi_basic.panelCS, OUTPUT );
	digitalWrite(spi_basic.panelCS, HIGH);

	#if defined(ENERGIA)
	{
		SPI.begin();
		SPI.setDataMode(SPI_MODE0);
		SPI.setClockDivider(SPI_CLOCK_DIV32);
		// SPI.setClockDivider(16000000 / min(16000000, 4000000));
		SPI.setBitOrder(MSBFIRST);
	}
	#else
	{
		SPISettings _settingScreen;
		_settingScreen = {8000000, MSBFIRST, SPI_MODE0};
		SPI.begin();
		SPI.beginTransaction(_settingScreen);
	}
	#endif

	// Power On COG driver sequence
	_reset(5, 5, 10, 20);
	
	_softReset();
	delay(5);
	const uint8_t temp_in = register_data[2]+0x40;
	_sendIndexData( 0xe5, &temp_in, 1 );  //Input Temperature: 25C
	_sendIndexData( 0xe0, &register_data[3], 1 );  //Active Temperature
	
	if (pdi_size == 0x29)
	{
		const uint8_t settings[] = {0x55, 0x02};
		_sendIndexData( 0x4d, &settings[0], 1);
		_sendIndexData( 0xe9, &settings[1], 1);
	}
	else
	{
		const uint8_t psr[] = {register_data[4]|0x10, register_data[5]|0x02};
		_sendIndexData( 0x00, &psr[0], 2);  //PSR	>> consult Application Note on Reading OTP
	}
	
	const uint8_t hold = 0x07;
	_sendIndexData( 0x50, &hold, 1);  //CDI
}

// CoG shutdown function
//		Shuts down the CoG and DC/DC circuit after all update functions
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::COG_powerOff()
{
	_sendIndexData( 0x02, &register_data[0], 0 );  //Turn off DC/DC
	
	while ( digitalRead( spi_basic.panelBusy ) != HIGH );
	
	digitalWrite( spi_basic.panelDC, LOW );
	digitalWrite( spi_basic.panelCS, LOW );
	digitalWrite( spi_basic.panelBusy, LOW );
	digitalWrite( spi_basic.panelReset, LOW );
}

// Global Update function
//		Implements global update functionality on either small/mid EPD
//		- INPUT:
//			- two image data (either BW and 0x00 or BW and BWR types)
void EPD_Driver::globalUpdate(const uint8_t * data1s, const uint8_t * data2s)
{
	// send first frame
    _sendIndexData(0x10, data1s, image_data_size); // First frame

	// send second frame
	_sendIndexData(0x13, data2s, image_data_size); // Second frame	

	_DCDC_powerOn();
	_displayRefresh();
	digitalWrite(spi_basic.panelCS, HIGH);
}

// Fast Update function
//		Implements fast update functionality
//		- INPUT:
//			- array of image data to iterate on
//			- size of array
void EPD_Driver::fastUpdate(const uint8_t * data1s, const uint8_t * data2s)
{
	uint8_t hold = 0x27;
	uint8_t hold2 = 0x07;
	
	if (!(pdi_size == 0x27 or pdi_size == 0x28 or pdi_size == 0x41))
		_sendIndexData( 0x50, &hold, 1); //  Border setting

	_sendIndexData( 0x10, data1s, image_data_size); //First or previous frame
	_sendIndexData( 0x13, data2s, image_data_size );   //Second or new frame
	
	if (!(pdi_size == 0x27 or pdi_size == 0x28 or pdi_size == 0x41))
		_sendIndexData( 0x50, &hold2, 1 );

	_DCDC_powerOn();	
	_displayRefresh();
}

// ---------- PROTECTED FUNCTIONS -----------

// SPI transfer function
//		Implements SPI transfer of index and data (consult user manual for EPD SPI process)
//		- INPUT:
//			- register address
//			- pointer to data char array
//			- length/size of data
void EPD_Driver::_sendIndexData( uint8_t index, const uint8_t *data, uint32_t len )
{	
	digitalWrite( spi_basic.panelDC, LOW );      //DC Low
	digitalWrite( spi_basic.panelCS, LOW );      //CS Low
	SPI.transfer(index);
	digitalWrite( spi_basic.panelCS, HIGH );     //CS High
	digitalWrite( spi_basic.panelDC, HIGH );     //DC High
	digitalWrite( spi_basic.panelCS, LOW );      //CS Low
	
	for ( uint32_t i = 0; i < len; i++ )
	{
		SPI.transfer(data[ i ]);
	}
	
	digitalWrite( spi_basic.panelCS, HIGH );     //CS High
}

// CoG soft-reset function
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::_softReset()
{
	_sendIndexData( 0x00, &register_data[1], 1 );	//Soft-reset, will reset to run the internal LUT for global update
	while( digitalRead( spi_basic.panelBusy ) != HIGH );
}

// EPD Screen refresh function
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::_displayRefresh()
{
	_sendIndexData( 0x12, &register_data[0], 0 );	//Display Refresh
	while( digitalRead( spi_basic.panelBusy ) != HIGH );
}

// CoG driver power-on hard reset
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4)
{
	// note: group delays into one array
	delay(ms1);
    digitalWrite(spi_basic.panelReset, HIGH); // RES# = 1
    delay(ms2);
    digitalWrite(spi_basic.panelReset, LOW);
    delay(ms3);
    digitalWrite(spi_basic.panelReset, HIGH);
    delay(ms4);
}

// DC-DC power-on command
//		Implemented after image data are uploaded to CoG
//		Specific to small-sized EPDs only
//		- INPUT:
//			- none but requires global variables on SPI pinout and config register data
void EPD_Driver::_DCDC_powerOn()
{
	_sendIndexData( 0x04, &register_data[0], 0);  //Power on
	while( digitalRead( spi_basic.panelBusy ) != HIGH );
}
