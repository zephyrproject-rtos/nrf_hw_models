/*
 * Copyright (c) 2017 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CRC_BLE_H
#define _CRC_BLE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void hwm_crc_append_ble24(uint8_t* buf, unsigned int len, uint32_t crc_init); /* 24bit BLE CRC*/
uint32_t hwm_crc_update_ble24(uint32_t crc, const void *data, size_t data_len);
uint32_t hwm_crc_calc_ble24_b(uint8_t* buf, unsigned int len, uint32_t crc_init);
uint32_t hwm_crc_update_ble32(uint32_t crc, const void *data, size_t data_len);
void hwm_crc_append_ble32(uint8_t* buf, unsigned int len, uint32_t crc_init); /* 32bit BLE CRC */
void hwm_crc_append_154(uint8_t* buf, unsigned int len, uint16_t crc_init);
uint16_t hwm_crc_update_154(uint16_t crc, const void *data, size_t data_len);

#ifdef __cplusplus
}
#endif

#endif
