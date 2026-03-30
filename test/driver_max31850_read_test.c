/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_max31850_read_test.c
 * @brief     driver max31850 read test source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-04-20
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/04/20  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_max31850_read_test.h"

static max31850_handle_t gs_handle;        /**< max31850 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t max31850_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint8_t rom[8];
    max31850_info_t info;
   
    /* link interface function */
    DRIVER_MAX31850_LINK_INIT(&gs_handle, max31850_handle_t);
    DRIVER_MAX31850_LINK_BUS_INIT(&gs_handle, max31850_interface_init);
    DRIVER_MAX31850_LINK_BUS_DEINIT(&gs_handle, max31850_interface_deinit);
    DRIVER_MAX31850_LINK_BUS_READ(&gs_handle, max31850_interface_read);
    DRIVER_MAX31850_LINK_BUS_WRITE(&gs_handle, max31850_interface_write);
    DRIVER_MAX31850_LINK_DELAY_MS(&gs_handle, max31850_interface_delay_ms);
    DRIVER_MAX31850_LINK_DELAY_US(&gs_handle, max31850_interface_delay_us);
    DRIVER_MAX31850_LINK_ENABLE_IRQ(&gs_handle, max31850_interface_enable_irq);
    DRIVER_MAX31850_LINK_DISABLE_IRQ(&gs_handle, max31850_interface_disable_irq);
    DRIVER_MAX31850_LINK_DEBUG_PRINT(&gs_handle, max31850_interface_debug_print);

    /* get max31850 info */
    res = max31850_info(&info);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print max31850 info */
        max31850_interface_debug_print("max31850: chip is %s.\n", info.chip_name);
        max31850_interface_debug_print("max31850: manufacturer is %s.\n", info.manufacturer_name);
        max31850_interface_debug_print("max31850: interface is %s.\n", info.interface);
        max31850_interface_debug_print("max31850: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max31850_interface_debug_print("max31850: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max31850_interface_debug_print("max31850: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max31850_interface_debug_print("max31850: max current is %0.2fmA.\n", info.max_current_ma);
        max31850_interface_debug_print("max31850: max temperature is %0.1fC.\n", info.temperature_max);
        max31850_interface_debug_print("max31850: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* max31850 init */
    res = max31850_init(&gs_handle);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    max31850_interface_debug_print("max31850: start read test.\n");
    
    /* skip rom mode */
    res = max31850_set_mode(&gs_handle, MAX31850_MODE_SKIP_ROM);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: set mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    max31850_interface_debug_print("max31850: set skip rom.\n"); 
    
    for (i = 0; i < times; i++)
    {
        uint8_t addr_pin;
        int16_t thermocouple_temperature_raw;
        float thermocouple_temperature_deg;
        int16_t internal_temperature_raw;
        float internal_temperature_deg;
        
        /* read data */
        res = max31850_read(&gs_handle, &addr_pin,
                            &thermocouple_temperature_raw, &thermocouple_temperature_deg,
                            &internal_temperature_raw, &internal_temperature_deg);
        if (res != 0)
        {
            max31850_interface_debug_print("max31850: read failed.\n");
            (void)max31850_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        max31850_interface_debug_print("max31850: address pin is 0x%02X.\n", addr_pin);
        max31850_interface_debug_print("max31850: thermocouple temperature is %.01fC.\n", thermocouple_temperature_deg);
        max31850_interface_debug_print("max31850: internal temperature is %.01fC.\n", internal_temperature_deg);
        
        /* delay 2000ms */
        max31850_interface_delay_ms(2000);
    }
    
    /* get rom */
    res = max31850_get_rom(&gs_handle, (uint8_t *)rom);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: get rom failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    res = max31850_set_rom(&gs_handle, (uint8_t *)rom);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: set mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set match rom mode */
    res = max31850_set_mode(&gs_handle, MAX31850_MODE_MATCH_ROM);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: set mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    max31850_interface_debug_print("max31850: set match rom.\n");

    for (i = 0; i < times; i++)
    {
        uint8_t addr_pin;
        int16_t thermocouple_temperature_raw;
        float thermocouple_temperature_deg;
        int16_t internal_temperature_raw;
        float internal_temperature_deg;
        
        /* read data */
        res = max31850_read(&gs_handle, &addr_pin,
                            &thermocouple_temperature_raw, &thermocouple_temperature_deg,
                            &internal_temperature_raw, &internal_temperature_deg);
        if (res != 0)
        {
            max31850_interface_debug_print("max31850: read failed.\n");
            (void)max31850_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        max31850_interface_debug_print("max31850: address pin is 0x%02X.\n", addr_pin);
        max31850_interface_debug_print("max31850: thermocouple temperature is %.01fC.\n", thermocouple_temperature_deg);
        max31850_interface_debug_print("max31850: internal temperature is %.01fC.\n", internal_temperature_deg);
        
        /* delay 2000ms */
        max31850_interface_delay_ms(2000);
    }
    
    /* finish read test */
    max31850_interface_debug_print("max31850: finish read test.\n");
    (void)max31850_deinit(&gs_handle);
    
    return 0;
}
