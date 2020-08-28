/*
 * Copyright (c) 2017 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */
#include "hal/nrf_ccm.h"
#include "bs_tracing.h"
#include "NRF_AES_CCM.h"


void nrf_ccm_event_clear(NRF_CCM_Type *  p_reg,
                         nrf_ccm_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
}

bool nrf_ccm_event_check(NRF_CCM_Type const * p_reg,
                         nrf_ccm_event_t      event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event);
}

void nrf_ccm_int_enable(NRF_CCM_Type * p_reg, uint32_t mask)
{
  p_reg->INTENSET = mask;
  nrf_ccm_regw_sideeffects_INTENSET();
}

void nrf_ccm_int_disable(NRF_CCM_Type * p_reg, uint32_t mask)
{
  p_reg->INTENCLR = mask;
  nrf_ccm_regw_sideeffects_INTENCLR();
}

void nrf_ccm_enable(NRF_CCM_Type * p_reg)
{
    p_reg->ENABLE = (CCM_ENABLE_ENABLE_Enabled << CCM_ENABLE_ENABLE_Pos);
}

void nrf_ccm_disable(NRF_CCM_Type * p_reg)
{
    p_reg->ENABLE = (CCM_ENABLE_ENABLE_Disabled << CCM_ENABLE_ENABLE_Pos);
}

void nrf_ccm_configure(NRF_CCM_Type *           p_reg,
                       nrf_ccm_config_t const * p_config)
{
    p_reg->MODE = (((uint32_t)p_config->mode     << CCM_MODE_MODE_Pos) |
#if defined(CCM_MODE_DATARATE_Pos)
                   ((uint32_t)p_config->datarate << CCM_MODE_DATARATE_Pos) |
#endif
#if defined(CCM_MODE_LENGTH_Pos)
                   ((uint32_t)p_config->length   << CCM_MODE_LENGTH_Pos) |
#endif
                   0);
}

bool nrf_ccm_micstatus_get(NRF_CCM_Type const * p_reg)
{
    return (bool)(p_reg->MICSTATUS);
}

void nrf_ccm_cnfptr_set(NRF_CCM_Type *   p_reg,
                        uint32_t const * p_data)
{
    p_reg->CNFPTR = (uint32_t)p_data;
}

void nrf_ccm_inptr_set(NRF_CCM_Type *   p_reg,
                       uint32_t const * p_data)
{
    p_reg->INPTR = (uint32_t)p_data;
}

void nrf_ccm_outptr_set(NRF_CCM_Type *   p_reg,
                        uint32_t const * p_data)
{
    p_reg->OUTPTR = (uint32_t)p_data;
}

void nrf_ccm_scratchptr_set(NRF_CCM_Type *   p_reg,
                            uint32_t const * p_area)
{
    p_reg->SCRATCHPTR = (uint32_t)p_area;
}

void nrf_ccm_task_trigger(NRF_CCM_Type * p_reg, nrf_ccm_task_t task)
{
  if ( task == NRF_CCM_TASK_KSGEN ) {
    NRF_CCM->TASKS_KSGEN = 1;
    nrf_ccm_regw_sideeffects_TASKS_KSGEN();
  } else if ( task == NRF_CCM_TASK_STOP ) {
    p_reg->TASKS_STOP = 1;
    nrf_ccm_regw_sideeffects_TASKS_STOP();
  } else {
    bs_trace_error_line_time("Not supported task started in nrf_ccm\n");
  }
}
