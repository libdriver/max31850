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
 * @file      driver_max31850_match.c
 * @brief     driver max31850 match source file
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
  
#include "driver_max31850_match.h"

static max31850_handle_t gs_handle;        /**< max31850 handle */

/**
 * @brief  match example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t max31850_match_init(void)
{
    uint8_t res;
    
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
    
    /* max31850 init */
    res = max31850_init(&gs_handle);
    if (res != 0)
    {
        max31850_interface_debug_print("max31850: init failed.\n");
        
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
    
    return 0;
}

/**
 * @brief      match example read
 * @param[in]  *rom pointer to a rom buffer
 * @param[out] *addr_pin pointer to an address pin buffer
 * @param[out] *temperature pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t max31850_match_read(uint8_t rom[8], uint8_t *addr_pin, float *temperature)
{
    uint8_t res;
    int16_t thermocouple_temperature_raw;
    int16_t internal_temperature_raw;
    float internal_temperature_deg;
    
    /* set rom */
    res = max31850_set_rom(&gs_handle, (uint8_t *)rom);
    if (res != 0)
    {
        return 1;
    }
    
    /* read temperature */
    if (max31850_read(&gs_handle, addr_pin, 
                      &thermocouple_temperature_raw, temperature,
                      &internal_temperature_raw, &internal_temperature_deg) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  match example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t max31850_match_deinit(void)
{
    /* max31850 close */
    if (max31850_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
