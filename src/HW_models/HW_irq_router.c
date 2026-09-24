/*
 * Copyright (c) 2026 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "bs_tracing.h"
#include "nsi_tasks.h"
#include "NHW_common_types.h"
#include "HW_irq_router.h"
#include "NHW_config.h"
#include "irq_ctrl.h"

#define ROUTER_F_BODY(router_nbr, router_irqn, f) \
  if (router_nbr == HW_IRQR_DISCONNECTED) { \
    /* Disconnected interrupt, we are done */ \
    return; \
  } \
  if (router_nbr != HW_IRQR_TO_ROUTER) { \
    bs_trace_error_time_line("Programming error: This interrupt should have gone " \
        "directly to an IRQ controller %i %u\n", router_nbr, router_irqn); \
  } \
  \
  if (router_irqn >= NHW_IRQRTR_NBR_GLB_LINES) { \
    bs_trace_error_time_line("Programming error: router_irqn(%u) >= %i\n", router_irqn, NHW_IRQRTR_NBR_GLB_LINES); \
  } \
  \
  for (int i = 0; i < NHW_INTCTRL_TOTAL_INST; i++) { \
      int target_ctrl = rout_table[router_irqn][i].cntl_inst; \
      unsigned int target_intn = rout_table[router_irqn][i].int_nbr; \
      \
      if (target_ctrl == HW_IRQR_DISCONNECTED) { \
        continue; \
      } else if (target_ctrl == HW_IRQR_TO_ROUTER) { \
        /* Let's allow this even if a bit bizarre */ \
        hw_irq_router_##f(target_ctrl, target_intn); \
      } else { \
        hw_irq_ctrl_##f(target_ctrl, target_intn); \
      } \
  } \

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Woverride-init"
static struct nhw_irq_mapping rout_table[NHW_IRQRTR_NBR_GLB_LINES][NHW_INTCTRL_TOTAL_INST] = NHW_IRQRTR_MAPPING;
#pragma GCC diagnostic pop

void hw_irq_router_set_irq(int router_nbr, unsigned int router_irqn)
{
  ROUTER_F_BODY(router_nbr, router_irqn, set_irq);
}

void hw_irq_router_raise_level_irq_line(int router_nbr, unsigned int router_irqn)
{
  ROUTER_F_BODY(router_nbr, router_irqn, raise_level_irq_line);
}

void hw_irq_router_lower_level_irq_line(int router_nbr, unsigned int router_irqn)
{
  ROUTER_F_BODY(router_nbr, router_irqn, lower_level_irq_line);
}
