### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

DATA Pin: PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MAX31850

#### 3.1 Command Instruction

1. Show max31850 chip and driver information.

    ```shell
    max31850 (-i | --information)
    ```

2. Show max31850 help.

   ```shell
   max31850 (-h | --help)
   ```

3. Show max31850 pin connections of the current board.

   ```shell
   max31850 (-p | --port)
   ```

4. Run max31850 register test.

   ```shell
   max31850 (-t reg | --test=reg)
   ```

5.  Run max31850 read test, num means the test times.

   ```shell
   max31850 (-t read | --test=read) [--times=<num>]
   ```

6. Run max31850 search test.

   ```shell
   max31850 (-t search | --test=search)
   ```

7. Run max31850 read function, num means the read times.

   ```shell
   max31850 (-e read | --example=read) [--times=<num>]
   ```

8. Run max31850 match function, num means the read times, code means the rom code with the length of 8 and it is hexadecimal.

   ```shell
   max31850 (-e match | --example=match) --rom=<code> [--times=<num>]
   ```

9. Run max31850 search rom function.

   ```shell
   max31850 (-e search | --example=search)
   ```

#### 3.2 Command Example

```shell
max31850 -i

max31850: chip is Maxim Integrated MAX31850.
max31850: manufacturer is Maxim Integrated.
max31850: interface is GPIO.
max31850: driver version is 1.0.
max31850: min supply voltage is 3.0V.
max31850: max supply voltage is 3.7V.
max31850: max current is 4.00mA.
max31850: max temperature is 125.0C.
max31850: min temperature is -40.0C.
```

```shell
max31850 -p

max31850: DQ pin connected to GPIOA PIN8.
```

```shell
max31850 -t reg

max31850: chip is Maxim Integrated MAX31850.
max31850: manufacturer is Maxim Integrated.
max31850: interface is GPIO.
max31850: driver version is 1.0.
max31850: min supply voltage is 3.0V.
max31850: max supply voltage is 3.7V.
max31850: max current is 4.00mA.
max31850: max temperature is 125.0C.
max31850: min temperature is -40.0C.
max31850: start register test.
max31850: max31850_set_mode/max31850_get_mode test.
max31850: set skip rom mode.
max31850: check mode ok.
max31850: set match rom mode.
max31850: check mode ok.
max31850: max31850_set_rom/max31850_get_rom test.
max31850: set rom.
max31850: check rom ok.
max31850: max31850_get_power_mode test.
max31850: check power mode externally power.
max31850: finish register test.
```

```shell
max31850 -t search

max31850: chip is Maxim Integrated MAX31850.
max31850: manufacturer is Maxim Integrated.
max31850: interface is GPIO.
max31850: driver version is 1.0.
max31850: min supply voltage is 3.0V.
max31850: max supply voltage is 3.7V.
max31850: max current is 4.00mA.
max31850: max temperature is 125.0C.
max31850: min temperature is -40.0C.
max31850: start search test.
max31850: search rom...
max31850: find 1 rom.
max31850: rom 3BAF288713D04C50.
max31850: finish search test.
```

```shell
max31850 -t read --times=3

max31850: chip is Maxim Integrated MAX31850.
max31850: manufacturer is Maxim Integrated.
max31850: interface is GPIO.
max31850: driver version is 1.0.
max31850: min supply voltage is 3.0V.
max31850: max supply voltage is 3.7V.
max31850: max current is 4.00mA.
max31850: max temperature is 125.0C.
max31850: min temperature is -40.0C.
max31850: start read test.
max31850: set skip rom.
max31850: address pin is 0x00.
max31850: thermocouple temperature is 27.8C.
max31850: internal temperature is 29.0C.
max31850: address pin is 0x00.
max31850: thermocouple temperature is 27.8C.
max31850: internal temperature is 29.0C.
max31850: address pin is 0x00.
max31850: thermocouple temperature is 27.8C.
max31850: internal temperature is 29.0C.
max31850: set match rom.
max31850: address pin is 0x00.
max31850: thermocouple temperature is 27.8C.
max31850: internal temperature is 28.9C.
max31850: address pin is 0x00.
max31850: thermocouple temperature is 27.8C.
max31850: internal temperature is 28.9C.
max31850: address pin is 0x00.
max31850: thermocouple temperature is 28.0C.
max31850: internal temperature is 29.0C.
max31850: finish read test.
```

```shell
max31850 -e search

max31850: find 1 rom(s).
max31850: 1/1 is 3BAF288713D04C50.
```

```shell
max31850 -e read --times=3

max31850: 1/3.
max31850: address pin is 0x00.
max31850: temperature is 27.75C.
max31850: 2/3.
max31850: address pin is 0x00.
max31850: temperature is 27.75C.
max31850: 3/3.
max31850: address pin is 0x00.
max31850: temperature is 27.50C.
```

```shell
max31850 -e match --times=3 --rom=3BAF288713D04C50

max31850: 1/3.
max31850: address pin is 0x00.
max31850: temperature is 27.75C.
max31850: 2/3.
max31850: address pin is 0x00.
max31850: temperature is 27.75C.
max31850: 3/3.
max31850: address pin is 0x00.
max31850: temperature is 28.00C.
```

```shell
max31850 -h

Usage:
  max31850 (-i | --information)
  max31850 (-h | --help)
  max31850 (-p | --port)
  max31850 (-t reg | --test=reg)
  max31850 (-t read | --test=read) [--times=<num>]
  max31850 (-t search | --test=search)
  max31850 (-e read | --example=read) [--times=<num>]
  max31850 (-e match | --example=match) --rom=<code> [--times=<num>]
  max31850 (-e search | --example=search)

Options:
  -e <read | match | search>, --example=<read | match | search>
                                 Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
      --rom=<code>               Set the rom with the length of 8 and it is hexadecimal.
  -t <reg | read | search>, --test=<reg | read | search>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

