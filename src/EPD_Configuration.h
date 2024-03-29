///
/// @file EPD_Configuration.h
/// @brief Configuration of the options for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// 1- List of supported Pervasive Displays screens
/// 2- List of pre-configured boards
/// 3- Register initializations
///
/// @author Pervasive Displays, Inc.
/// @date 25 Nov 2021
///
/// @copyright (c) Pervasive Displays, Inc., 2010-2021
/// @copyright All rights reserved
///
/// * Basic edition: for hobbyists and for personal usage
/// @n Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// * Advanced edition: for professionals or organisations, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///

// SDK
#include "stdint.h"

#ifndef hV_CONFIGURATION_RELEASE
///
/// @brief Release
///
#define hV_CONFIGURATION_RELEASE
\
///
/// @name 1- List of supported Pervasive Displays screens
/// @see https://www.pervasivedisplays.com/products/
/// @{
///
#define eScreen_EPD_t uint32_t ///< screen type
///
/// * Monochrome screens and default colour screens
#define eScreen_EPD_152 (uint32_t)0x1520 ///< reference xE2152KSxxx
#define eScreen_EPD_154 (uint32_t)0x1540 ///< reference xE2154xSxxx
#define eScreen_EPD_206 (uint32_t)0x2000 ///< reference xE2206xSxxx
#define eScreen_EPD_213 (uint32_t)0x2100 ///< reference xE2213xSxxx
#define eScreen_EPD_266 (uint32_t)0x2600 ///< reference xE2266xSxxx
#define eScreen_EPD_271 (uint32_t)0x2700 ///< reference xE2271xSxxx
#define eScreen_EPD_287 (uint32_t)0x2800 ///< reference xE2287xSxxx
#define eScreen_EPD_292 (uint32_t)0x2900 ///< reference xE2290xSxxx
#define eScreen_EPD_370 (uint32_t)0x3700 ///< reference xE2370xSxxx
#define eScreen_EPD_417 (uint32_t)0x4100 ///< reference xE2417xSxxx
#define eScreen_EPD_437 (uint32_t)0x430C ///< reference xE2437xSxxx

/// @}

///
/// @name Frame Frame-buffer sizes
/// @details Frame-buffer size = width * height / 8 * depth, uint32_t
/// @note Only one frame buffer is required.
/// @n Depth = 2 for black-white-red screens and monochrome screens
///

#define frameSize_EPD_EXT3_154 (uint32_t)(2888)
#define frameSize_EPD_EXT3_206 (uint32_t)(2756)
#define frameSize_EPD_EXT3_213 (uint32_t)(2756)
#define frameSize_EPD_EXT3_266 (uint32_t)(5624)
#define frameSize_EPD_EXT3_271 (uint32_t)(5808)
#define frameSize_EPD_EXT3_287 (uint32_t)(4736)
#define frameSize_EPD_EXT3_292 (uint32_t)(8064)
#define frameSize_EPD_EXT3_370 (uint32_t)(12480)
#define frameSize_EPD_EXT3_417 (uint32_t)(15000)
#define frameSize_EPD_EXT3_437 (uint32_t)(10560)


/// @name 2- List of pre-configured boards
/// @{

///
/// @brief Not connected pin
///
#define NOT_CONNECTED (uint8_t)0xff

///
/// @brief Board configuration structure
///

struct pins_t
{
    // uint8_t panelSCL;
    ///< EXT3 pin 1 Black -> +3.3V
    ///< EXT3 pin 2 Brown -> SPI SCK
    uint8_t panelBusy; ///< EXT3 pin 3 Red
    uint8_t panelDC; ///< EXT3 pin 4 Orange
    uint8_t panelReset; ///< EXT3 pin 5 Yellow
    ///< EXT3 pin 6 Green -> SPI MISO
    ///< EXT3 pin 7 Blue -> SPI MOSI
    // uint8_t panelSDA;
    uint8_t panelCS;
    uint8_t panelON_EXT2;
    uint8_t panelSPI43_EXT2;
    uint8_t flashCS;
};

///
/// @brief MSP430 and MSP432 LaunchPad configuration, tested
///
const pins_t boardLaunchPad_EXT3 =
{
    .panelBusy = 11, ///< EXT3 pin 3 Red
    .panelDC = 12, ///< EXT3 pin 4 Orange
    .panelReset = 13, ///< EXT3 pin 5 Yellow
    .panelCS = 19,
    .panelON_EXT2 = NOT_CONNECTED,
    .panelSPI43_EXT2 = NOT_CONNECTED,
    .flashCS = NOT_CONNECTED
};

///
/// @brief Raspberry Pi Pico with default RP2040 configuration, tested
///
const pins_t boardRaspberryPiPico_RP2040_EXT3 =
{
    .panelBusy = 13, ///< EXT3 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 pin 5 Yellow -> GP11
    .panelCS = 17,
    .panelON_EXT2 = NOT_CONNECTED,
    .panelSPI43_EXT2 = NOT_CONNECTED,
    .flashCS = 10
};

///
/// @brief Arduino M0Pro configuration, tested
///
const pins_t boardArduinoM0Pro_EXT3 =
{
    .panelBusy = 4, ///< EXT3 pin 3 Red
    .panelDC = 5, ///< EXT3 pin 4 Orange
    .panelReset = 6, ///< EXT3 pin 5 Yellow
    .panelCS = 8,
    .panelON_EXT2 = NOT_CONNECTED,
    .panelSPI43_EXT2 = NOT_CONNECTED,
    .flashCS = NOT_CONNECTED
};

/// @}

///
/// @name 3- Register initializations
/// @{
///

//0x00, soft-reset, temperature, active temp, PSR0, PSR1
const uint8_t register_data_sm[] = { 0x00, 0x0e, 0x19, 0x02, 0xcf, 0x8d };

//TSSET, PSR_GU, Border, PSR_FU
const uint8_t register_data_152[] = { 0x19, 0xd7, 0xc0, 0xdf, 0x00, 0x00};
/// @}

#endif // hV_CONFIGURATION_RELEASE
