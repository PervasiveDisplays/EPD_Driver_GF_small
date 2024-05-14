# Introduction
 *  This library code implements the driving code of [Aurora(V231) or Wide-temperature EPDs with iTC driver and embedded OTP LUT](https://www.pervasivedisplays.com/products/) made by [Pervasive Displays Inc (PDi)](https://www.pervasivedisplays.com/). This is compatible with [EPD Extension Kit Gen 3 (EXT3)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-3-ext3/).
 *  It implements the global (GU) and fast update modes (FU).
 *  The library supports the following EPD sizes: 1.52", 1.54", 2.06", 2.13", 2.66", 2.71", 2.71"(A), 2.92", 3.70", 4.20", 4.37"
 *  This library was tested with Launchpad (Tiva-C) with TM4C123, MSP432P401R, Arduino M0 Pro, and Raspberry Pi Pico.

# Installation
  Download the ZIP file of this library and install as instructed in [Arduino](https://www.arduino.cc/en/guide/libraries) or Energia.

# Hardware Setup
 *  If using Launchpad (Tiva-C) with TM4C123 or MSP432P401R, the SPI pins are by default:
``` c++
// Using EXT3
    SCK = 7     // BROWN
    BUSY = 11   // RED
    D/C = 12    // ORANGE
    RST = 13    // YELLOW
    MOSI = 15   // BLUE
    ECSM = 19   // GRAY
    
 ```
 *  If using Arduino M0 Pro,
  ```
    SCK = 13 
    BUSY = 4  
    D/C = 5
    RST = 6
    MOSI = 12
    ECSM = 8
 ```
  *  If using Raspberry Pi Pico,
  ```
    SCK = 18 
    BUSY = 13  
    D/C = 12
    RST = 11
    MOSI = 19
    ECSM = 17
 ```
For further wiring guidance, check out our Wiki: [EXT3](https://docs.pervasivedisplays.com/epd-usage/development-kits/ext3-1).

# EPD_Driver Demo
 *  The sample code implements both global and fast update functionality for a [1.52" Wide Temperature+Fast Update EPD (E2152KS0J1)](https://www.pervasivedisplays.com/product/1-52-e-ink-displays/).  
 
 First, a BW(black and white) image is flashed.  
  Then, after a two-second delay, a sequence of BW fast images are flashed.  
  
 *  The demo currently includes sample images for all the supported EPD sizes mentioned above. To implement the demo on these other sizes, update the following lines
``` c++
//------------------------------------------------------------
// DEMO Image Set <Comment out when in User Mode>
// Screen Size: 152, 154, 206, 213, 266, 271, 292, 370, 417, 437
#define SCREEN 152
#include "globalupdate_src/demoImageData.h"
#include "fastupdate_src/demoImageData.h"
```
 *  Then select the appropriate EPD size, development board and extension kit:
``` c++
#define EPD_SIZE eScreen_EPD_152
#define BOARD_TYPE boardRaspberryPiPico_RP2040_EXT3
```

#  Tech Support
 *  For more information, please visit [Pervasive Displays, Inc. (龍亭新技股份有限公司)](https://www.pervasivedisplays.com/)
 *  [PDi Product Line up](https://www.pervasivedisplays.com/products/)
 *  [EPD Extension Kit Gen 3 (EXT3)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-3-ext3/)
 *  [24/7 Support Service](https://www.pervasivedisplays.com/technical-support/)
 *  [PDI Wiki](https://docs.pervasivedisplays.com/)