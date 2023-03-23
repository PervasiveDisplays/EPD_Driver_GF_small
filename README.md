# Introduction
 *  This library code implements the driving code of [Aurora(V231) or Spectra EPDs with iTC driver](https://www.pervasivedisplays.com/products/epd-product-selection/) made by [Pervasive Displays Inc (PDi)](https://www.pervasivedisplays.com/). This is compatible with [EPD Extension Kit Gen 3 (EXT3)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-3-ext3/).
 *  It implements the global (GU) and fast update modes (FU).
 *  The library supports the following EPD sizes: 1.54", 2.13", 2.66", 2.71", 2.87", 3.70", 4.20", 4.37"
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
 *  The sample code implements a global update functionality for a [2.71" Spectra R2.0 EPD (E2271PS091)](https://www.pervasivedisplays.com/product/2-71-e-ink-displays//).  
 
 First, a BW(black and white) image is flashed.  
  <p align="center"><img src="https://github.com/PervasiveDisplays/EPD_Driver_GU_small/blob/main/examples/Demo_271/globalupdate_src/images/2.71/271_264x176_BW.bmp"></p>
 After a second, a BWR (black, white, red) image follows.  
 <p align="center"><img src="https://github.com/PervasiveDisplays/EPD_Driver_GU_small/blob/main/examples/Demo_271/globalupdate_src/images/2.71/271_264x176_BWR.bmp"></p>
 
 *  The demo currently includes sample images for all the supported EPD sizes mentioned above. To implement the demo on these other sizes, update the following lines
``` c++
//------------------------------------------------------------
// DEMO Image Set <Comment out when in User Mode>
// Screen Size: 154, 213, 266, 271, 287, 370, 420, 437
#define SCREEN 271
#include "globalupdate_src/demoImageData.h"
```
 *  Then select the appropriate EPD size, development board and extension kit:
```
  // EPD_Driver epdtest(eScreen_EPD_271, boardLaunchPad_EXT3);
  // EPD_Driver epdtest(eScreen_EPD_271, boardArduinoM0Pro_EXT2);
  EPD_Driver epdtest(eScreen_EPD_271, boardRaspberryPiPico_RP2040_EXT3);
  // EPD_Driver epdtest(eScreen_EPD_271, boardRaspberryPiPico_RP2040_EXT2);
```

#  Tech Support
 *  For more information, please visit [Pervasive Displays, Inc. (龍亭新技股份有限公司)](https://www.pervasivedisplays.com/)
 *  [PDi Product Line up](https://www.pervasivedisplays.com/products/)
 *  [EPD Extension Kit Gen 3 (EXT3)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-3-ext3/)
 *  [24/7 Support Service](https://www.pervasivedisplays.com/technical-support/)

