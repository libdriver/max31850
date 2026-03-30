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
 * @file      driver_max31850_register_test.c
 * @brief     driver max31850 register test source file
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

#include "driver_max31850_register_test.h"
#include <stdlib.h>

static max31850_handle_t gs_handle;        /**< max31850 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t max31850_register_test(void)
{
    uint8_t res;
    uint8_t i;
    uint8_t rom[8];
    uint8_t rom_check[8];
    max31850_info_t info;
    max31850_mode_t mode;
    max31850_power_mode_t power_mode;
    
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
    
    /* start register test */
    max31850_interface_debug_print("max31850: start register test.\n");
    
    /* max31850 init */
    res = max31850_init(&gs_handle);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: init failed.\n");
       
        return 1;
    }
    
    /* max31850_set_mode/max31850_get_mode test */
    max31850_interface_debug_print("max31850: max31850_set_mode/max31850_get_mode test.\n");
    
    /* skip rom */
    res = max31850_set_mode(&gs_handle, MAX31850_MODE_SKIP_ROM);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: set mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    max31850_interface_debug_print("max31850: set skip rom mode.\n");
    res = max31850_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: get mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    max31850_interface_debug_print("max31850: check mode %s.\n", (mode == MAX31850_MODE_SKIP_ROM) ? "ok" : "error");
    
    /* match rom */
    res = max31850_set_mode(&gs_handle, MAX31850_MODE_MATCH_ROM);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: set mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    max31850_interface_debug_print("max31850: set match rom mode.\n");
    res = max31850_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: get mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    max31850_interface_debug_print("max31850: check mode %s.\n", (mode == MAX31850_MODE_MATCH_ROM) ? "ok" : "error");
    
    /* max31850_set_rom/max31850_get_rom test */
    max31850_interface_debug_print("max31850: max31850_set_rom/max31850_get_rom test.\n");
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
    max31850_interface_debug_print("max31850: set rom.\n");
    res = max31850_get_rom(&gs_handle, (uint8_t *)rom_check);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: get rom failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    for (i=0; i<8; i++)
    {
        if (rom[i] != rom_check[i])
        {
            res = 1;
        }
    }
    max31850_interface_debug_print("max31850: check rom %s.\n", (res == 0) ? "ok" : "error");
    
    /* max31850_get_power_mode test */
    max31850_interface_debug_print("max31850: max31850_get_power_mode test.\n");
    res = max31850_get_power_mode(&gs_handle, &power_mode);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: get power mode failed.\n");
        (void)max31850_deinit(&gs_handle);
        
        return 1;
    }
    max31850_interface_debug_print("max31850: check power mode %s.\n",
                                   (power_mode == MAX31850_POWER_MODE_EXTERNALLY) ? "externally power" : "parasite power");
    
    /* finish register test */
    max31850_interface_debug_print("max31850: finish register test.\n");
    (void)max31850_deinit(&gs_handle);
    
    return 0;
}
