/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _NRF_HW_MODEL_UTILS_H
#define _NRF_HW_MODEL_UTILS_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif

void hwu_reverse_byte_order(const unsigned char *in_data, unsigned char *out_data, size_t len);
int hwu_readline(char *s, int size, FILE *stream);
uint8_t hwu_rev_byte(uint8_t input);
uint32_t hwu_rev_32(uint32_t input);
uint32_t hwu_rev_24(uint32_t input);
uint16_t hwu_rev_16(uint16_t input);

#ifdef __cplusplus
}
#endif

#endif /* _NRF_HW_MODEL_UTILS_H */
