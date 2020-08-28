/*
 * Copyright (c) 2017 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */
#include "hal/nrf_rng.h"
#include "bs_tracing.h"
#include "NRF_RNG.h"


uint32_t nrf_rng_int_enable_check(NRF_RNG_Type const * p_reg, uint32_t mask)
{
    return p_reg->INTENSET & mask;
}

void nrf_rng_event_clear(NRF_RNG_Type * p_reg, nrf_rng_event_t rng_event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)rng_event)) = 0x0UL;
}

bool nrf_rng_event_check(NRF_RNG_Type const * p_reg, nrf_rng_event_t rng_event)
{
    return (bool) * ((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)rng_event));
}

void nrf_rng_shorts_disable(NRF_RNG_Type * p_reg, uint32_t mask)
{
     p_reg->SHORTS &= ~mask;
}

uint8_t nrf_rng_random_value_get(NRF_RNG_Type const * p_reg)
{
    return (uint8_t)(p_reg->VALUE & RNG_VALUE_VALUE_Msk);
}

void nrf_rng_error_correction_enable(NRF_RNG_Type * p_reg)
{
    p_reg->CONFIG |= RNG_CONFIG_DERCEN_Msk;
}

void nrf_rng_error_correction_disable(NRF_RNG_Type * p_reg)
{
    p_reg->CONFIG &= ~RNG_CONFIG_DERCEN_Msk;
}

void nrf_rng_task_trigger(NRF_RNG_Type * p_reg, nrf_rng_task_t rng_task)
{
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)rng_task)) = 0x1UL;

  if ( rng_task == NRF_RNG_TASK_START ) {
    NRF_RNG_regs.TASKS_START = 1;
    nrf_rng_regw_sideeffects_TASK_START();
  } else if ( rng_task == NRF_RNG_TASK_STOP ) {
    NRF_RNG_regs.TASKS_STOP = 1;
    nrf_rng_regw_sideeffects_TASK_STOP();
  } else {
    bs_trace_error_line_time("Not supported task started in nrf_rng\n");
  }
}

void nrf_rng_int_enable(NRF_RNG_Type * p_reg, uint32_t mask)
{
  NRF_RNG_regs.INTENSET = mask;
  nrf_rng_regw_sideeffects_INTENSET();
}

void nrf_rng_int_disable(NRF_RNG_Type * p_reg, uint32_t mask)
{
  NRF_RNG_regs.INTENCLR = mask;
  nrf_rng_regw_sideeffects_INTENCLEAR();
}
