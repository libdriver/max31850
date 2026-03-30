[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31850

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31850/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Die 1-Wire-Thermoelement-Digital-Wandler MAX31850/MAX31851 mit Kaltstellenkompensation führen eine Kaltstellenkompensation durch und digitalisieren das Signal von Thermoelementen der Typen K, J, N, T, S, R oder E. Die Wandler erreichen eine Temperaturauflösung von 0,25 °C, messen Temperaturen von bis zu +1768 °C und bis zu -270 °C und weisen eine Thermoelementgenauigkeit von 8 LSB (2 °C) im Temperaturbereich von -200 °C bis +700 °C auf. Die Kommunikation mit dem Master-Mikrocontroller erfolgt über einen 1-Wire-Bus, der definitionsgemäß nur eine Datenleitung (und Masse) benötigt. Die Betriebsspannung kann direkt von der Datenleitung bezogen werden („parasitäre Leistungsaufnahme“), wodurch ein externes Netzteil entfällt. Jedes Gerät verfügt über einen eindeutigen 64-Bit-Seriellcode, der den Betrieb mehrerer Geräte am selben 1-Wire-Bus ermöglicht. Daher ist es einfach, mit einem Mikrocontroller (dem Mastergerät) die Temperatur vieler über eine große Fläche verteilter Thermoelemente zu überwachen.

LibDriver MAX31850 ist ein umfassender Treiber für den MAX31850, entwickelt von LibDriver. Er bietet Funktionen wie Temperaturmessung, ROM-Zuordnung, ROM-Suche und weitere. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example match](#example-match)
    - [example search](#example-search)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MAX31850-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MAX31850 onewire.

/test enthält den Testcode des LibDriver MAX31850-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MAX31850-Beispielcode.

/doc enthält das LibDriver MAX31850-Offlinedokument.

/Datenblatt enthält MAX31850-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige onewire-Schnittstellenvorlage und stellen Sie Ihren Plattform-onewire-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/max31850/index.html](https://www.libdriver.com/docs/max31850/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.