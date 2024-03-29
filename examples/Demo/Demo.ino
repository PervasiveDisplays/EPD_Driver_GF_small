/*
  EPD_Driver_demo
  This is a demo sketch for the small PS-type EPDs from Pervasive Displays, Inc.
  The aim of this demo and the library used is to introduce CoG usage, global and fast update functionality.
  
  Hardware Suggested:
  * Launchpad MSP432P401R or (Tiva-C) with TM4C123/Arduino M0 Pro/Raspberry Pi Pico
  * EPD Extension Kit (EXT3 or EXT3-1)
  * Small-sized (<5") EPD (PS-type)
  * 10/20-pin rainbow cable
*/

#include <EPD_Driver.h>

// DEMO Image Set <Comment out when in User Mode>
// Screen Size: 152, 154, 206, 213, 266, 271, 292, 370, 417, 437
#define SCREEN 152
#include "globalupdate_src/demoImageData.h"
#include "fastupdate_src/demoImageData.h"
//------------------------------------------------------------

#define EPD_SIZE eScreen_EPD_152
#define BOARD_TYPE boardRaspberryPiPico_RP2040_EXT3

void setup()
{
	EPD_Driver epdtest(EPD_SIZE, BOARD_TYPE);

	// Initialize CoG for GU
	epdtest.COG_initial_GU();
	// Global Update Call
	epdtest.globalUpdate(BW_monoBuffer, BW_0x00Buffer);

	// Turn off CoG
	epdtest.COG_powerOff();

	delay(2000);

	// Initialize CoG for FU
	epdtest.COG_initial_FU();
	// Fast Update Call
	epdtest.fastUpdate(FastPic_1, FastPic_b);
	epdtest.fastUpdate(FastPic_b, FastPic_w);
	epdtest.fastUpdate(FastPic_w, FastPic_2);
	epdtest.fastUpdate(FastPic_2, FastPic_3);
	epdtest.fastUpdate(FastPic_3, FastPic_4);
	
	delay(2000);
	epdtest.fastUpdate(FastPic_4, FastPic_b);
	epdtest.fastUpdate(FastPic_b, FastPic_w);
	
	delay(1000);
	// Turn off CoG
	epdtest.COG_powerOff();
}

void loop()
{
	delay(1000);
}
