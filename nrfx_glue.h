/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Provides a minimalistic nrfx_glue to be used with Nordic nrfx
 * when not used together with Zephyr.
 */

#ifndef NRFX_GLUE_H__
#define NRFX_GLUE_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Macro for placing a runtime assertion.
 *
 * @param expression Expression to be evaluated.
 */
#define NRFX_ASSERT(expression)

/* For BSIM we require redefining the pointers to the peripherals.
 * As we only include nrfx.h, and not nrf.h, we here ensure that the peripherals
 * are always redefined. */
#include "nrfx_bsim_redef.h"

#ifdef __cplusplus
}
#endif

#endif // NRFX_GLUE_H__
