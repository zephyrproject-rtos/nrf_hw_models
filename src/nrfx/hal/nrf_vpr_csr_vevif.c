/*
 * Copyright (c) 2026, Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */

#include "hal/nrf_vpr_csr_vevif.h"
#include "bs_tracing.h"
#include "NHW_config.h"
#include "NHW_VPR.h"

uint32_t nrf_vpr_csr_vevif_tasks_get(void)
{
  int inst = nhw_vpr_get_vpr_instance();
  return nhw_vpr_get_internal_regs(inst)->TASKS;
}

void nrf_vpr_csr_vevif_tasks_clear(uint32_t mask)
{
  int inst = nhw_vpr_get_vpr_instance();
  nhw_vpr_get_internal_regs(inst)->TASKS &= ~mask;
  nhw_vpr_regw_sideeffects_csr_TASKS(inst);
}

void nrf_vpr_csr_vevif_tasks_set(uint32_t value)
{
  int inst = nhw_vpr_get_vpr_instance();
  nhw_vpr_get_internal_regs(inst)->TASKS = value;
  nhw_vpr_regw_sideeffects_csr_TASKS(inst);
}

uint32_t nrf_vpr_csr_vevif_events_get(void)
{
  int inst = nhw_vpr_get_vpr_instance();
  return nhw_vpr_get_internal_regs(inst)->EVENTS;
}

void nrf_vpr_csr_vevif_events_set(uint32_t value)
{
  int inst = nhw_vpr_get_vpr_instance();
  nhw_vpr_get_internal_regs(inst)->EVENTS = value;
  nhw_vpr_regw_sideeffects_csr_EVENTS(inst);
}

void nrf_vpr_csr_vevif_events_trigger(uint32_t mask)
{
  int inst = nhw_vpr_get_vpr_instance();
  nhw_vpr_get_internal_regs(inst)->EVENTS |= mask;
  nhw_vpr_regw_sideeffects_csr_EVENTS(inst);
}

void nrf_vpr_csr_vevif_events_buffered_set(uint32_t value)
{
  (void)value;
  bs_trace_warning_line_time("%s not modelled\n", __func__);
}

bool nrf_vpr_csr_vevif_events_buffered_dirty_check(void)
{
  bs_trace_warning_line_time("%s not modelled\n", __func__);
  return false;
}

uint32_t nrf_vpr_csr_vevif_subscribe_get(void)
{
  int inst = nhw_vpr_get_vpr_instance();
  return nhw_vpr_get_internal_regs(inst)->SUBSCRIBE;
}

void nrf_vpr_csr_vevif_subscribe_set(uint32_t value)
{
  int inst = nhw_vpr_get_vpr_instance();
  nhw_vpr_get_internal_regs(inst)->SUBSCRIBE = value;
  nhw_vpr_regw_sideeffects_csr_SUBSCRIBE(inst);
}

uint32_t nrf_vpr_csr_vevif_publish_get(void)
{
  int inst = nhw_vpr_get_vpr_instance();
  return nhw_vpr_get_internal_regs(inst)->PUBLISH;
}

void nrf_vpr_csr_vevif_publish_set(uint32_t value)
{
  int inst = nhw_vpr_get_vpr_instance();
  nhw_vpr_get_internal_regs(inst)->PUBLISH = value;
  nhw_vpr_regw_sideeffects_csr_PUBLISH(inst);
}

void nrf_vpr_csr_vevif_int_enable(uint32_t mask)
{
  int inst = nhw_vpr_get_vpr_instance();
  NRF_VPR_regs[inst].INTEN |= mask;
  nhw_VPR_regw_sideeffects_INTEN(inst);
}

void nrf_vpr_csr_vevif_int_disable(uint32_t mask)
{
  int inst = nhw_vpr_get_vpr_instance();
  NRF_VPR_regs[inst].INTEN &= ~mask;
  nhw_VPR_regw_sideeffects_INTEN(inst);
}

uint32_t nrf_vpr_csr_vevif_int_enable_check(uint32_t mask)
{
  int inst = nhw_vpr_get_vpr_instance();
  return NRF_VPR_regs[inst].INTEN & mask;
}
