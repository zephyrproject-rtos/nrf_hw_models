/*
 * Copyright (c) 2020 Oticon A/S
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */
#include "hal/nrf_aar.h"
#include "bs_tracing.h"
#include "NRF_AAR.h"


NRF_STATIC_INLINE bool nrf_aar_event_check(NRF_AAR_Type const * p_reg,
                                           nrf_aar_event_t      aar_event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)aar_event);
}

NRF_STATIC_INLINE void nrf_aar_event_clear(NRF_AAR_Type *  p_reg,
                                           nrf_aar_event_t aar_event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)aar_event)) = 0;
#if __CORTEX_M == 0x04
    volatile uint32_t dummy = *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)aar_event));
    (void)dummy;
#endif
}

void nrf_aar_int_disable(NRF_AAR_Type * p_reg, uint32_t mask)
{
  p_reg->INTENCLR = mask;
  nrf_aar_regw_sideeffects_INTENCLR();
}

void nrf_aar_task_trigger(NRF_AAR_Type * p_reg, nrf_aar_task_t task)
{
  if (task == NRF_AAR_TASK_START) {
    p_reg->TASKS_START = 1;
    nrf_aar_regw_sideeffects_TASKS_START();
  } else if (task == NRF_AAR_TASK_STOP) {
    p_reg->TASKS_STOP = 1;
    nrf_aar_regw_sideeffects_TASKS_STOP();
  }  else {
    bs_trace_error_line_time("Not supported task started in nrf_aar\n");
  }
}

NRF_STATIC_INLINE void nrf_aar_enable(NRF_AAR_Type * p_reg)
{
    p_reg->ENABLE = AAR_ENABLE_ENABLE_Enabled << AAR_ENABLE_ENABLE_Pos;
}

NRF_STATIC_INLINE void nrf_aar_disable(NRF_AAR_Type * p_reg)
{
    p_reg->ENABLE = AAR_ENABLE_ENABLE_Disabled << AAR_ENABLE_ENABLE_Pos;
}

NRF_STATIC_INLINE void nrf_aar_irk_pointer_set(NRF_AAR_Type * p_reg, uint8_t const * irk_ptr)
{
    p_reg->IRKPTR = (uint32_t)irk_ptr;
}

NRF_STATIC_INLINE void nrf_aar_irk_number_set(NRF_AAR_Type * p_reg, uint8_t irk_num)
{
    p_reg->NIRK = irk_num;
}

NRF_STATIC_INLINE void nrf_aar_addr_pointer_set(NRF_AAR_Type * p_reg, uint8_t const * addr_ptr)
{
    p_reg->ADDRPTR = (uint32_t)addr_ptr;
}

NRF_STATIC_INLINE void nrf_aar_scratch_pointer_set(NRF_AAR_Type * p_reg, uint8_t * scratch_ptr)
{
    p_reg->SCRATCHPTR = (uint32_t)scratch_ptr;
}

NRF_STATIC_INLINE uint8_t nrf_aar_resolution_status_get(NRF_AAR_Type const * p_reg)
{
    return (uint8_t)(p_reg->STATUS);
}
