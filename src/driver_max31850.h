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
 * @file      driver_max31850.h
 * @brief     driver max31850 header file
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

#ifndef DRIVER_MAX31850_H
#define DRIVER_MAX31850_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup max31850_driver max31850 driver function
 * @brief    max31850 driver modules
 * @{
 */

/**
 * @addtogroup max31850_advance_driver
 * @{
 */

/**
 * @brief max31850 max search size definition
 */
#ifndef MAX31850_MAX_SEARCH_SIZE
    #define MAX31850_MAX_SEARCH_SIZE 64        /**< max 64 devices */
#endif

/**
 * @}
 */

/**
 * @addtogroup max31850_base_driver
 * @{
 */

/**
 * @brief max31850 mode enumeration definition
 */
typedef enum
{
    MAX31850_MODE_SKIP_ROM  = 0x00,        /**< skip rom mode */
    MAX31850_MODE_MATCH_ROM = 0x01,        /**< match rom mode */
} max31850_mode_t;

/**
 * @brief max31850 power mode enumeration definition
 */
typedef enum
{
    MAX31850_POWER_MODE_PARASITE   = 0x00,        /**< parasite power mode */
    MAX31850_POWER_MODE_EXTERNALLY = 0x01,        /**< externally power mode */
} max31850_power_mode_t;

/**
 * @brief max31850 handle structure definition
 */
typedef struct max31850_handle_s
{
    uint8_t (*bus_init)(void);                              /**< point to a bus_init function address */
    uint8_t (*bus_deinit)(void);                            /**< point to a bus_deinit function address */
    uint8_t (*bus_read)(uint8_t *value);                    /**< point to a bus_read function address */
    uint8_t (*bus_write)(uint8_t value);                    /**< point to a bus_write function address */
    void (*delay_ms)(uint32_t ms);                          /**< point to a delay_ms function address */
    void (*delay_us)(uint32_t us);                          /**< point to a delay_us function address */
    void (*enable_irq)(void);                               /**< point to an enable_irq function address */
    void (*disable_irq)(void);                              /**< point to a disable_irq function address */
    void (*debug_print)(const char *const fmt, ...);        /**< point to a debug_print function address */
    uint8_t inited;                                         /**< inited flag */
    uint8_t mode;                                           /**< chip mode */
    uint8_t rom[8];                                         /**< chip mode */
} max31850_handle_t;

/**
 * @brief max31850 info structure definition
 */
typedef struct max31850_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} max31850_info_t;

/**
 * @}
 */

/**
 * @defgroup max31850_link_driver max31850 link driver function
 * @brief    max31850 link driver modules
 * @ingroup  max31850_driver
 * @{
 */

/**
 * @brief     initialize max31850_handle_t structure
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] STRUCTURE max31850_handle_t
 * @note      none
 */
#define DRIVER_MAX31850_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link bus_init function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a bus_init function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_BUS_INIT(HANDLE, FUC)           (HANDLE)->bus_init = FUC

/**
 * @brief     link bus_deinit function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a bus_deinit function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_BUS_DEINIT(HANDLE, FUC)         (HANDLE)->bus_deinit = FUC

/**
 * @brief     link bus_read function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a bus_read function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_BUS_READ(HANDLE, FUC)           (HANDLE)->bus_read = FUC

/**
 * @brief     link bus_write function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a bus_write function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_BUS_WRITE(HANDLE, FUC)          (HANDLE)->bus_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_DELAY_MS(HANDLE, FUC)           (HANDLE)->delay_ms = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a delay_us function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_DELAY_US(HANDLE, FUC)           (HANDLE)->delay_us = FUC

/**
 * @brief     link enable_irq function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to an enable_irq function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_ENABLE_IRQ(HANDLE, FUC)         (HANDLE)->enable_irq = FUC

/**
 * @brief     link disable_irq function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a disable_irq function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_DISABLE_IRQ(HANDLE, FUC)        (HANDLE)->disable_irq = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a max31850 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_MAX31850_LINK_DEBUG_PRINT(HANDLE, FUC)        (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup max31850_base_driver max31850 base driver function
 * @brief    max31850 base driver modules
 * @ingroup  max31850_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a max31850 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max31850_info(max31850_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a max31850 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t max31850_init(max31850_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a max31850 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max31850_deinit(max31850_handle_t *handle);

/**
 * @brief     set the chip mode
 * @param[in] *handle pointer to a max31850 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max31850_set_mode(max31850_handle_t *handle, max31850_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle pointer to a max31850 handle structure
 * @param[out] *mode pointer to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max31850_get_mode(max31850_handle_t *handle, max31850_mode_t *mode);

/**
 * @brief     set the handle rom
 * @param[in] *handle pointer to a max31850 handle structure
 * @param[in] *rom pointer to a rom buffer
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max31850_set_rom(max31850_handle_t *handle, uint8_t rom[8]);

/**
 * @brief      get the chip rom
 * @param[in]  *handle pointer to a max31850 handle structure
 * @param[out] *rom pointer to a rom buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max31850_get_rom(max31850_handle_t *handle, uint8_t rom[8]);

/**
 * @brief      read data from the chip
 * @param[in]  *handle pointer to a max31850 handle structure
 * @param[out] *addr_pin pointer to an address pin buffer
 * @param[out] *thermocouple_temperature_raw pointer to a thermocouple temperature raw buffer
 * @param[out] *thermocouple_temperature_deg pointer to a converted thermocouple temperature buffer
 * @param[out] *internal_temperature_raw pointer to an internal temperature raw buffer
 * @param[out] *internal_temperature_deg pointer to a converted internal temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 open circuit
 *             - 5 short to gnd
 *             - 6 short to vdd
 *             - 7 find fault
 * @note       none
 */
uint8_t max31850_read(max31850_handle_t *handle, uint8_t *addr_pin,
                      int16_t *thermocouple_temperature_raw, float *thermocouple_temperature_deg,
                      int16_t *internal_temperature_raw, float *internal_temperature_deg);

/**
 * @}
 */

/**
 * @defgroup max31850_advance_driver max31850 advance driver function
 * @brief    max31850 advance driver modules
 * @ingroup  max31850_driver
 * @{
 */

/**
 * @brief         search the max31850 rom
 * @param[in]     *handle pointer to a max31850 handle structure
 * @param[out]    **rom pointer to a rom array
 * @param[in,out] *num pointer to an array size buffer
 * @return        status code
 *                - 0 success
 *                - 1 search rom failed
 * @note          none
 */
uint8_t max31850_search_rom(max31850_handle_t *handle, uint8_t (*rom)[8], uint8_t *num);

/**
 * @brief      get the power mode
 * @param[in]  *handle pointer to a max31850 handle structure
 * @param[out] *power_mode pointer to a power mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get power mode failed
 * @note       none
 */
uint8_t max31850_get_power_mode(max31850_handle_t *handle, max31850_power_mode_t *power_mode);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
