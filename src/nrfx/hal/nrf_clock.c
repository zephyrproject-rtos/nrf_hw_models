/*
 * Copyright (c) 2017 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */
#include "hal/nrf_clock.h"
#include "bs_tracing.h"
#include "NRF_CLOCK.h"


void nrf_clock_int_enable(NRF_CLOCK_Type * p_reg, uint32_t mask)
{
  p_reg->INTENSET = mask;
  nrf_clock_reqw_sideeffects_INTENSET();
}

void nrf_clock_int_disable(NRF_CLOCK_Type * p_reg, uint32_t mask)
{
  p_reg->INTENCLR = mask;
  nrf_clock_reqw_sideeffects_INTENCLR();
}

uint32_t nrf_clock_int_enable_check(NRF_CLOCK_Type const * p_reg, uint32_t mask)
{
  /* Note that unlike the real NRF HW, INTENCLR is always
   * reset to 0 by the HW models */
  return p_reg->INTENSET & mask;
}

uint32_t nrf_clock_task_address_get(NRF_CLOCK_Type const * p_reg,
                                    nrf_clock_task_t       task)
{
    return (uint32_t)((uint8_t *)p_reg + (uint32_t)task);
}

void nrf_clock_task_trigger(NRF_CLOCK_Type * p_reg, nrf_clock_task_t task)
{
  if (task == NRF_CLOCK_TASK_HFCLKSTART) {
    NRF_CLOCK_regs.TASKS_HFCLKSTART = 1;
    nrf_clock_reqw_sideeffects_TASKS_HFCLKSTART();
  } else if (task == NRF_CLOCK_TASK_HFCLKSTOP) {
    NRF_CLOCK_regs.TASKS_HFCLKSTOP = 1;
    nrf_clock_reqw_sideeffects_TASKS_HFCLKSTOP();
  } else if (task == NRF_CLOCK_TASK_LFCLKSTART) {
    NRF_CLOCK_regs.TASKS_LFCLKSTART = 1;
    nrf_clock_reqw_sideeffects_TASKS_LFCLKSTART();
  } else if (task == NRF_CLOCK_TASK_LFCLKSTOP) {
    NRF_CLOCK_regs.TASKS_LFCLKSTOP = 1;
    nrf_clock_reqw_sideeffects_TASKS_LFCLKSTOP();
  } else {
    bs_trace_warning_line_time("Not supported task started in nrf_clock, %d\n", task);
  }
}

uint32_t nrf_clock_event_address_get(NRF_CLOCK_Type const * p_reg,
                                     nrf_clock_event_t      event)
{
    return (uint32_t)((uint8_t *)p_reg + (uint32_t)event);
}

void nrf_clock_event_clear(NRF_CLOCK_Type * p_reg, nrf_clock_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
}

bool nrf_clock_event_check(NRF_CLOCK_Type const * p_reg, nrf_clock_event_t event)
{
    return (bool)*((volatile uint32_t *)((uint8_t *)p_reg + event));
}

bool nrf_clock_start_task_check(NRF_CLOCK_Type const * p_reg,
                                nrf_clock_domain_t     domain)
{
    switch (domain)
    {
        case NRF_CLOCK_DOMAIN_LFCLK:
            return ((p_reg->LFCLKRUN & CLOCK_LFCLKRUN_STATUS_Msk)
                    >> CLOCK_LFCLKRUN_STATUS_Pos);
        case NRF_CLOCK_DOMAIN_HFCLK:
            return ((p_reg->HFCLKRUN & CLOCK_HFCLKRUN_STATUS_Msk)
                    >> CLOCK_HFCLKRUN_STATUS_Pos);
        default:
            NRFX_ASSERT(0);
            return false;
    }
}

void nrf_clock_lf_src_set(NRF_CLOCK_Type * p_reg, nrf_clock_lfclk_t source)
{
    p_reg->LFCLKSRC = (uint32_t)(source);
}

nrf_clock_lfclk_t nrf_clock_lf_src_get(NRF_CLOCK_Type const * p_reg)
{
    return (nrf_clock_lfclk_t)(p_reg->LFCLKSRC);
}

bool nrf_clock_is_running(NRF_CLOCK_Type const * p_reg,
                          nrf_clock_domain_t     domain,
                          void *                 p_clk_src)
{
    switch (domain)
    {
        case NRF_CLOCK_DOMAIN_LFCLK:
            if (p_clk_src != NULL)
            {
                (*(nrf_clock_lfclk_t *)p_clk_src) =
                    (nrf_clock_lfclk_t)((p_reg->LFCLKSTAT & CLOCK_LFCLKSTAT_SRC_Msk)
                                        >> CLOCK_LFCLKSTAT_SRC_Pos);
            }
            if ((p_reg->LFCLKSTAT & CLOCK_LFCLKSTAT_STATE_Msk)
                >> CLOCK_LFCLKSTAT_STATE_Pos)
            {
                return true;
            }
            break;
        case NRF_CLOCK_DOMAIN_HFCLK:
            if (p_clk_src != NULL)
            {
                (*(nrf_clock_hfclk_t *)p_clk_src) =
                    (nrf_clock_hfclk_t)((p_reg->HFCLKSTAT & CLOCK_HFCLKSTAT_SRC_Msk)
                                        >> CLOCK_HFCLKSTAT_SRC_Pos);
            }
            if ((p_reg->HFCLKSTAT & CLOCK_HFCLKSTAT_STATE_Msk)
                >> CLOCK_HFCLKSTAT_STATE_Pos)
            {
                return true;
            }
            break;
#if NRF_CLOCK_HAS_HFCLK192M
        case NRF_CLOCK_DOMAIN_HFCLK192M:
            if (p_clk_src != NULL)
            {
                (*(nrf_clock_hfclk_t *)p_clk_src) =
                    (nrf_clock_hfclk_t)((p_reg->HFCLK192MSTAT & CLOCK_HFCLK192MSTAT_SRC_Msk)
                                        >> CLOCK_HFCLK192MSTAT_SRC_Pos);
            }
            if ((p_reg->HFCLK192MSTAT & CLOCK_HFCLK192MSTAT_STATE_Msk)
                >> CLOCK_HFCLK192MSTAT_STATE_Pos)
            {
                return true;
            }
            break;
#endif
#if NRF_CLOCK_HAS_HFCLKAUDIO
        case NRF_CLOCK_DOMAIN_HFCLKAUDIO:
            return (p_reg->HFCLKAUDIOSTAT & CLOCK_HFCLKAUDIOSTAT_STATE_Msk) ==
                   CLOCK_HFCLKAUDIOSTAT_STATE_Msk;
#endif
        default:
            NRFX_ASSERT(0);
            return false;
    }
    return false;
}

nrf_clock_lfclk_t nrf_clock_lf_srccopy_get(NRF_CLOCK_Type const * p_reg)
{
  /*simple approximation LFCLKSRC = LFCLKSRCCOPY*/
  return (nrf_clock_lfclk_t)((p_reg->LFCLKSRC & CLOCK_LFCLKSRC_SRC_Msk)
                                >> CLOCK_LFCLKSRC_SRC_Pos);
}

nrf_clock_hfclk_t nrf_clock_hf_src_get(NRF_CLOCK_Type const * p_reg)
{
  return (nrf_clock_hfclk_t)((p_reg->HFCLKSTAT & CLOCK_HFCLKSTAT_SRC_Msk)
                                >> CLOCK_HFCLKSTAT_SRC_Pos);
}

bool nrf_clock_hf_is_running(NRF_CLOCK_Type const * p_reg,
                             nrf_clock_hfclk_t      clk_src)
{
    nrf_clock_hfclk_t active_clk_src;
    bool ret = nrf_clock_is_running(p_reg, NRF_CLOCK_DOMAIN_HFCLK, &active_clk_src);
    return (ret && (active_clk_src == clk_src));
}

void nrf_clock_cal_timer_timeout_set(NRF_CLOCK_Type * p_reg, uint32_t interval)
{
  /*We don't want to model clock calibration as per now*/
}
