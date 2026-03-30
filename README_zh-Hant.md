[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31850

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31850/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX31850/MAX31851冷端補償1-Wire熱電偶至數位轉換器可對K型、J型、N型、T型、S型、R型或E型熱電偶的信號進行冷端補償和數位化處理。這些轉換器可將溫度解析度提升至0.25攝氏度，測量範圍高達+1768攝氏度，低至-270攝氏度，在-200攝氏度至+700攝氏度的溫度範圍內，熱電偶精度可達8個最低有效位（2攝氏度）。與主微控制器的通信透過1-Wire總線實現，根據定義，該總線僅需一條數據線（和地線）即可進行通信。工作電源可直接從數據線獲取（「寄生電源」），無需外部電源。每個設備都有一個唯一的64位序列碼，允許多個單元在同一1-Wire總線上工作。因此，使用一個微控制器（主設備）即可輕鬆監測分佈在大面積區域內的多個熱電偶的溫度。

LibDriver MAX31850是LibDriver推出的MAX31850全功能驅動，該驅動提供溫度讀取、ROM匹配溫度讀取和搜索ROM等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example match](#example-match)
    - [example search](#example-search)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver MAX31850的源文件。

/interface目錄包含了LibDriver MAX31850與平台無關的onewire總線模板。

/test目錄包含了LibDriver MAX31850驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver MAX31850編程範例。

/doc目錄包含了LibDriver MAX31850離線文檔。

/datasheet目錄包含了MAX31850數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的onewire總線模板，完成指定平台的onewire總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/max31850/index.html](https://www.libdriver.com/docs/max31850/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
