/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Provides a mocked nrf.h.
 * This reuses the nrf.h from the MDK, but defines base registers
 * and peripheral addresses to point to mocked peripherals.
 */

#ifndef NRF_BSIM_H__
#define NRF_BSIM_H__

/* Include the nrf from stable MDK. */
#include <bsp/stable/mdk/nrf.h>

#if !defined(NRF_H_NO_BSIM_REDEFS)
/* For BSIM peripherals registers are not mapped in the same addresses as in
 * the real HW so we need to correct them.
 * For the very special cases in which we want the real HW addresses after
 * including nrf.h, define NRF_H_NO_BSIM_REDEFS before include *any* header */
#include "nrf_bsim_redef.h"
#endif

#endif
