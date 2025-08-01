/*
 * Copyright (c) 2017 Oticon A/S
 * Copyright (c) 2023, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */
#include "hal/nrf_clock.h"
#include "bs_tracing.h"
#if defined(NRF54L_SERIES)
#include "NHW_54L_CLOCK.h"
#else
#include "NHW_CLOCK.h"
#endif

static int clock_number_from_ptr(NRF_CLOCK_Type * p_reg)
{
  union NRF_CLKPWR_Type *p = (union NRF_CLKPWR_Type *)p_reg;

  int i = ( (int)p - (int)&NRF_CLKPWR_regs[0] ) / sizeof(union NRF_CLKPWR_Type);
  return i;
}

void nrf_clock_int_enable(NRF_CLOCK_Type * p_reg, uint32_t mask)
{
  p_reg->INTENSET = mask;

  int i = clock_number_from_ptr(p_reg);
  nhw_CLOCK_regw_sideeffects_INTENSET(i);
}

void nrf_clock_int_disable(NRF_CLOCK_Type * p_reg, uint32_t mask)
{
  p_reg->INTENCLR = mask;

  int i = clock_number_from_ptr(p_reg);
  nhw_CLOCK_regw_sideeffects_INTENCLR(i);
}

void nrf_clock_task_trigger(NRF_CLOCK_Type * p_reg, nrf_clock_task_t task)
{
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;

  int i = clock_number_from_ptr(p_reg);

#define CASE_TASK(TASKN) \
  case NRF_CLOCK_TASK_##TASKN: nhw_CLOCK_regw_sideeffects_TASKS_##TASKN(i); break;

  switch (task) {
#if NRF_CLOCK_HAS_XO
    case NRF_CLOCK_TASK_HFCLKSTART: nhw_CLOCK_regw_sideeffects_TASKS_XOSTART(i); break;
    case NRF_CLOCK_TASK_HFCLKSTOP : nhw_CLOCK_regw_sideeffects_TASKS_XOSTOP(i);  break;
#else
    CASE_TASK(HFCLKSTART)
    CASE_TASK(HFCLKSTOP)
#endif
#if NRF_CLOCK_HAS_PLL
    CASE_TASK(PLLSTART)
    CASE_TASK(PLLSTOP)
#endif
#if NHW_CLKPWR_HAS_LFCLK
    CASE_TASK(LFCLKSTART)
    CASE_TASK(LFCLKSTOP)
#endif
#if NRF_CLOCK_HAS_CALIBRATION
    CASE_TASK(CAL)
#endif
#if NRF_CLOCK_HAS_CALIBRATION_TIMER
    CASE_TASK(CTSTART)
    CASE_TASK(CTSTOP)
#endif
#if NRF_CLOCK_HAS_HFCLKAUDIO
    CASE_TASK(HFCLKAUDIOSTART)
    CASE_TASK(HFCLKAUDIOSTOP)
#endif
#if NRF_CLOCK_HAS_HFCLK192M
    CASE_TASK(HFCLK192MSTART)
    CASE_TASK(HFCLK192MSTOP)
#endif
#if NRF_CLOCK_HAS_HFCLK24M
    case NRF_CLOCK_TASK_HFCLK24MSTART: nhw_CLOCK_regw_sideeffects_TASKS_XO24MSTART(i); break;
    case NRF_CLOCK_TASK_HFCLK24MSTOP : nhw_CLOCK_regw_sideeffects_TASKS_XO24MSTOP(i);  break;
#endif
#if NRF_CLOCK_HAS_XO_TUNE
    CASE_TASK(XOTUNE)
    CASE_TASK(XOTUNEABORT)
#endif
    default:
      bs_trace_error_line_time("Not supported task started in nrf_clock, %d\n", task);
      break;
  }
#undef CASE_TASK
}

void nrf_clock_event_clear(NRF_CLOCK_Type * p_reg, nrf_clock_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;

    int i = clock_number_from_ptr(p_reg);
    nhw_pwrclk_regw_sideeffects_EVENTS_all(i);
}

#if defined(DPPI_PRESENT)

static void nrf_clock_subscribe_common(NRF_CLOCK_Type * p_reg,
                                       nrf_clock_task_t task)
{
  int i = clock_number_from_ptr(p_reg);

#define CASE_TASK(TASKN) \
  case NRF_CLOCK_TASK_##TASKN: nhw_CLOCK_regw_sideeffects_SUBSCRIBE_##TASKN(i); break;

  switch (task) {
#if NRF_CLOCK_HAS_XO
    case NRF_CLOCK_TASK_HFCLKSTART: nhw_CLOCK_regw_sideeffects_SUBSCRIBE_XOSTART(i); break;
    case NRF_CLOCK_TASK_HFCLKSTOP:  nhw_CLOCK_regw_sideeffects_SUBSCRIBE_XOSTOP(i);  break;
#else
    CASE_TASK(HFCLKSTART)
    CASE_TASK(HFCLKSTOP)
#endif
#if NRF_CLOCK_HAS_PLL
    CASE_TASK(PLLSTART)
    CASE_TASK(PLLSTOP)
#endif
#if NHW_CLKPWR_HAS_LFCLK
    CASE_TASK(LFCLKSTART)
    CASE_TASK(LFCLKSTOP)
#endif
#if NRF_CLOCK_HAS_CALIBRATION
    CASE_TASK(CAL)
#endif
#if NRF_CLOCK_HAS_HFCLKAUDIO
    CASE_TASK(HFCLKAUDIOSTART)
    CASE_TASK(HFCLKAUDIOSTOP)
#endif
#if NRF_CLOCK_HAS_HFCLK192M
    CASE_TASK(HFCLK192MSTART)
    CASE_TASK(HFCLK192MSTOP)
#endif
#if NRF_CLOCK_HAS_HFCLK24M
    case NRF_CLOCK_TASK_HFCLK24MSTART: nhw_CLOCK_regw_sideeffects_SUBSCRIBE_XO24MSTART(i); break;
    case NRF_CLOCK_TASK_HFCLK24MSTOP : nhw_CLOCK_regw_sideeffects_SUBSCRIBE_XO24MSTOP(i);  break;
#endif
#if defined(CLOCK_SUBSCRIBE_XOTUNE_EN_Msk)
    CASE_TASK(XOTUNE)
    CASE_TASK(XOTUNEABORT)
#endif
    default:
      bs_trace_error_line_time("Attempted to subscribe to a not-supported task in the nrf_clock (%i)\n",
                                task);
      break;
  }
#undef CASE_TASK
}

void nrf_clock_subscribe_set(NRF_CLOCK_Type * p_reg,
                             nrf_clock_task_t task,
                             uint8_t          channel)
{
    *((volatile uint32_t *) ((uint8_t *) p_reg + (uint32_t) task + 0x80uL)) =
            ((uint32_t)channel | NRF_SUBSCRIBE_PUBLISH_ENABLE);
    nrf_clock_subscribe_common(p_reg, task);
}

void nrf_clock_subscribe_clear(NRF_CLOCK_Type * p_reg,
                               nrf_clock_task_t task)
{
    *((volatile uint32_t *) ((uint8_t *) p_reg + (uint32_t) task + 0x80uL)) = 0;
    nrf_clock_subscribe_common(p_reg, task);
}

#endif /* defined(DPPI_PRESENT) */
