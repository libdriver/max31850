[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31850

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31850/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MAX31850/MAX31851 cold-junction compensated, 1-Wire thermocouple-to-digital converters perform cold-junction compensation and digitize the signal from a K-, J-, N-, T-, S-, R-, or E-type thermocouple. The converters resolve temperatures to 0.25C, allow readings as high as +1768C and as low as -270C, and exhibit thermocouple accuracy of 8 LSBs (2C) for temperatures ranging from -200C to +700C. Communication with the master microcontroller is over a 1-Wire bus that by definition requires only one data line (and ground) for communication. Operating power can be obtained directly from the data line (“parasite power”), eliminating the need for an external power supply. Each device has a unique 64-bit serial code, which allows multiple units to function on the same 1-Wire bus. Therefore, it is simple to use one microcontroller (the master device) to monitor temperature from many thermocouples distributed over a large area.

LibDriver MAX31850 is a full-featured driver for MAX31850, launched by LibDriver. It provides temperature reading, ROM matching reading, ROM searching and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example match](#example-match)
    - [example search](#example-search)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MAX31850 source files.

/interface includes LibDriver MAX31850 onewire platform independent template.

/test includes LibDriver MAX31850 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MAX31850 sample code.

/doc includes LibDriver MAX31850 offline document.

/datasheet includes MAX31850 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface onewire platform independent template and finish your platform onewire driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_max31850_basic.h"

uint8_t res;
uint8_t addr_pin;
uint32_t i;
float temperature;

/* init */
res = max31850_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 2000ms */
    max31850_interface_delay_ms(2000);

    /* read data */
    res = max31850_basic_read(&addr_pin, &temperature);
    if (res != 0)
    {
        (void)max31850_basic_deinit();

        return 1;
    }

    /* output */
    max31850_interface_debug_print("max31850: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
    max31850_interface_debug_print("max31850: address pin is 0x%02X.\n", addr_pin);
    max31850_interface_debug_print("max31850: temperature is %0.2fC.\n", temperature);
    
    ...
}

...
    
/* deinit */
(void)max31850_basic_deinit();

return 0;
```

#### example match

```C
#include "driver_max31850_match.h"

uint8_t res;
uint8_t addr_pin;
uint8_t rom[8] = {0};
uint32_t i;
float temperature;

/* init */
res = max31850_match_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 2000ms */
    max31850_interface_delay_ms(2000);

    /* read data */
    res = max31850_match_read((uint8_t *)rom, &addr_pin, &temperature);
    if (res != 0)
    {
        (void)max31850_match_deinit();

        return 1;
    }

    /* output */
    max31850_interface_debug_print("max31850: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
    max31850_interface_debug_print("max31850: address pin is 0x%02X.\n", addr_pin);
    max31850_interface_debug_print("max31850: temperature is %0.2fC.\n", temperature);
    
    ...
}

...
    
/* deinit */
(void)max31850_match_deinit();

return 0;
```

#### example search

```C
#include "driver_max31850_search.h"

uint8_t res, i, j;
uint8_t rom[8][8];
uint8_t num;

res = max31850_search_init();
if (res != 0)
{
    return 1;
}

...

num = 8;
res = max31850_search((uint8_t (*)[8])rom, (uint8_t *)&num);
if (res != 0)
{
    (void)max31850_search_deinit();

    return 1;
}
max31850_interface_debug_print("max31850: find %d rom(s).\n", num);

...

for (i = 0; i < num; i++)
{
    max31850_interface_debug_print("max31850: %d/%d is ", (uint32_t)(i+1), (uint32_t)num);
    for (j = 0; j < 8; j++)
    {
        max31850_interface_debug_print("%02X ", rom[i][j]);
    }
    max31850_interface_debug_print(".\n");
    
    ...
    
}

...
    
(void)max31850_search_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/max31850/index.html](https://www.libdriver.com/docs/max31850/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.