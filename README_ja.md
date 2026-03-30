[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31850

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31850/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX31850/MAX31851冷接点補償型1-Wire熱電対-デジタル変換器は、K、J、N、T、S、R、またはEタイプの熱電対からの信号を冷接点補償してデジタル化します。この変換器は、0.25℃の分解能で温度を測定でき、最高+1768℃、最低-270℃の読み取りが可能で、-200℃から+700℃の温度範囲で8 LSB（2℃）の熱電対精度を実現します。マスターマイクロコントローラとの通信は、定義上、通信に必要なデータライン（およびグランド）が1本だけの1-Wireバスを介して行われます。動作電力はデータラインから直接供給されるため（「寄生電力」）、外部電源は不要です。各デバイスには固有の64ビットシリアルコードがあり、複数のユニットを同じ1-Wireバス上で動作させることができます。したがって、1つのマイクロコントローラ（マスターデバイス）を使用して、広い範囲に分散配置された多数の熱電対からの温度を監視することは容易である。

LibDriver MAX31850は、LibDriver社が開発したMAX31850用のフル機能ドライバです。温度読み取り、ROMマッチング読み取り、ROM検索などの機能を提供します。LibDriverはMISRA規格に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example match](#example-match)
    - [example search](#example-search)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MAX31850のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MAX31850用のプラットフォームに依存しないonewireバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MAX31850ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MAX31850プログラミング例が含まれています。

/ docディレクトリには、LibDriver MAX31850オフラインドキュメントが含まれています。

/ datasheetディレクトリには、MAX31850データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないonewireバステンプレートを参照して、指定したプラットフォームのonewireバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/max31850/index.html](https://www.libdriver.com/docs/max31850/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。