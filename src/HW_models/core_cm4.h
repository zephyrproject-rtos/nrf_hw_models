/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * Mocks the CMSIS dependency of the nRF MDK headers.
 */

#ifndef CORE_CM4__
#define CORE_CM4__

#define __I
#define __IO
#define __O

/**
 * The model of the CPU & IRQ controller driver must provide
 * these functions below. These HW models do not provide them
 */
extern void __WFE(void);
extern void __SEV(void);
extern void NVIC_SetPendingIRQ(IRQn_Type IRQn);
extern void NVIC_ClearPendingIRQ(IRQn_Type IRQn);

#endif 
