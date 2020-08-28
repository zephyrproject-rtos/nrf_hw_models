/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Provides a minimalistic nrfx_config to be used with Nordic nrfx
 * when not used together with Zephyr.
 */

#ifndef NRFX_CONFIG_H__
#define NRFX_CONFIG_H__

/* Ensure that all HAL functions are mocked. */
#define NRF_DECLARE_ONLY
#define NRF_STATIC_INLINE

#endif // NRFX_CONFIG_H__

