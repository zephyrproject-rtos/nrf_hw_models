/*
 * Copyright (c) 2026, Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */

#include "hal/nrf_vpr.h"
#include "bs_tracing.h"
#include "NHW_config.h"
#include "NHW_VPR.h"

static int vpr_number_from_ptr(NRF_VPR_Type const * p_reg) {
  int i = ( (int)p_reg - (int)&NRF_VPR_regs[0] ) / sizeof(NRF_VPR_Type);
  return i;
}

void nrf_vpr_task_trigger(NRF_VPR_Type * p_reg, nrf_vpr_task_t task)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;

    int i = vpr_number_from_ptr(p_reg);
    int task_nbr = (task - offsetof(NRF_VPR_Type, TASKS_TRIGGER[0]))/sizeof(uint32_t);
    nhw_VPR_regw_sideeffects_TASK_TRIGGER(i, task_nbr);
}

void nrf_vpr_event_clear(NRF_VPR_Type * p_reg, nrf_vpr_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;

    int i = vpr_number_from_ptr(p_reg);
    int event_nbr = (event - offsetof(NRF_VPR_Type, EVENTS_TRIGGERED[0]))/sizeof(uint32_t);
    nhw_VPR_regw_sideeffects_EVENTS_TRIGGERED(i, event_nbr);
}

void nrf_vpr_int_enable(NRF_VPR_Type * p_reg, uint32_t mask)
{
    p_reg->INTENSET = mask;

    int i = vpr_number_from_ptr(p_reg);
    nhw_VPR_regw_sideeffects_INTENSET(i);
}

void nrf_vpr_int_disable(NRF_VPR_Type * p_reg, uint32_t mask)
{
    p_reg->INTENCLR = mask;

    int i = vpr_number_from_ptr(p_reg);
    nhw_VPR_regw_sideeffects_INTENCLR(i);
}
