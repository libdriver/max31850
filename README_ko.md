[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31850

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31850/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX31850/MAX31851 냉접점 보상형 1-Wire 열전대-디지털 변환기는 K, J, N, T, S, R 또는 E형 열전대의 신호를 냉접점 보상하고 디지털화합니다. 이 변환기는 0.25°C 단위의 온도 분해능을 제공하며, 최대 +1768°C에서 최소 -270°C까지의 측정이 가능하고, -200°C에서 +700°C까지의 온도 범위에서 8 LSB(2°C)의 열전대 정확도를 나타냅니다. 마스터 마이크로컨트롤러와의 통신은 1-Wire 버스를 통해 이루어지며, 통신에 필요한 데이터 라인은 하나(및 접지)뿐입니다. 작동 전원은 데이터 라인에서 직접 공급받으므로("기생 전원") 외부 전원 공급 장치가 필요하지 않습니다. 각 장치는 고유한 64비트 직렬 코드를 가지고 있어 여러 장치가 동일한 1-Wire 버스에서 작동할 수 있습니다. 따라서 하나의 마이크로컨트롤러(마스터 장치)를 사용하여 넓은 영역에 분산된 여러 열전대의 온도를 간단하게 모니터링할 수 있습니다.

LibDriver MAX31850은 LibDriver에서 출시한 MAX31850용 완벽한 기능을 갖춘 드라이버입니다. 온도 판독, ROM 매칭 판독, ROM 검색 및 기타 여러 기능을 제공합니다. LibDriver는 MISRA 규정을 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example match](#example-match)
    - [example search](#example-search)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver MAX31850의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver MAX31850용 플랫폼 독립적인 onewire버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver MAX31850드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver MAX31850프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver MAX31850오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 MAX31850데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 onewire버스 템플릿을 참조하여 지정된 플랫폼에 대한 onewire버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/max31850/index.html](https://www.libdriver.com/docs/max31850/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.