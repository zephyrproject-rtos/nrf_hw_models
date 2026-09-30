/*
 * Copyright (c) 2026 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * Notes
 *  * So far, only the VEIF is really modeled
 *  * VPR Timer: VTIM is not modeled
 *  * VPR IO: VIO is not modeled
 *  * Sharing of registers between VEVIF and VIO is therefore also not modeled
 *  * The Debug interface is not implemented in any way, just stubbed
 *  * The processor control (CPURUN, INITPC, NDMRESET, ..) is not implemented, just stubbed
 *  * The CLIC interrupt controller is not implemented.
 *    (the generic irq_ctrl is used instead,
 *     and the integration is expected to adapt its irq handling to its API)
 *    The CLIC registers are purposely not stubbed.
 *
 * Implementation notes:
 *  * As the publish and subscribe channels are hardcoded,
 *    this model has an adhoc implementation of the DPPI interfacing compared to "normal" HW IP models.
 *  * As the INTEN interface is gated by the irq mask we also need an adhoc implementation
 *    for these registers sideeffecs
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "bs_tracing.h"
#include "bs_types.h"
#include "NHW_common_types.h"
#include "NHW_config.h"
#include "NHW_peri_types.h"
#include "NHW_templates.h"
#include "NHW_DPPI.h"
#include "NHW_VPR.h"
#include "irq_ctrl.h"
#include "nsi_tasks.h"
#include "weak_stubs.h"

NRF_VPR_Type NRF_VPR_regs[NHW_VPR_TOTAL_INST];

static struct vpr_status {
  uint inst;
  NRF_VPR_Type *VPR_regs;
  struct vpr_internal_regs intern_regs;

  uint32_t veif_taskevent_mask; /* Mask of overall available TASKS/EVENTS */
  uint32_t veif_dppi_mask; /* Mask of which of these TASKS/EVENTS are connected to the DPPI */
  uint32_t veif_ext_irq_mask; /* Mask of which of these EVENTS can drive the external IRQ */
  uint32_t veif_clic_irq_mask; /* Mask of which of these TASKS are connected to the CLIC */
  /* For each task (0..NHW_VPR_MAX_TASKSEVENTSEVENTS) which dppi channel it is hardcoded to (disconnected ones set to -1) */
  int dppi_channels_tasks[NHW_VPR_VEIF_MAX_TASKSEVENTS];
  /* For each event (0..NHW_VPR_VEIF_MAX_TASKSEVENTS) which dppi channel it is hardcoded to (disconnected ones set to -1)*/
  int dppi_channels_events[NHW_VPR_VEIF_MAX_TASKSEVENTS];
  /* Mapping of VPR instance to DPPI instance */
  uint dppi_map;
  struct nhw_subsc_mem *VPR_subscribed; /* Note subscribe channels are hardcoded in dppi_tasks_channels */
} nhw_vpr_st[NHW_VPR_TOTAL_INST];

struct vpr_internal_regs *nhw_vpr_get_internal_regs(uint inst) {
  return &nhw_vpr_st[inst].intern_regs;
}

static void nhw_vpr_init(void) {
  static uint dppi_map[NHW_VPR_TOTAL_INST]             = NHW_VPR_DPPI_MAP;
  static uint veif_taskevent_masks[NHW_VPR_TOTAL_INST] = NHW_VPR_VEIF_BASE_TASKSEVENTS_MASK;
  static uint veif_dppi_masks[NHW_VPR_TOTAL_INST]      = NHW_VPR_VEIF_DPPI_MASK;
  static uint veif_ext_irq_masks[NHW_VPR_TOTAL_INST]   = NHW_VPR_VEIF_EXTIRQ_MASK;
  static uint veif_clic_irq_masks[NHW_VPR_TOTAL_INST]  = NHW_VPR_VEIF_CLICIRQ_MASK;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Woverride-init"
  static int dppi_channels_tasks[NHW_VPR_TOTAL_INST][NHW_VPR_VEIF_MAX_TASKSEVENTS] = NHW_VPR_DPPI_CHANNELS_TASKS;
  static int dppi_channels_events[NHW_VPR_TOTAL_INST][NHW_VPR_VEIF_MAX_TASKSEVENTS] = NHW_VPR_DPPI_CHANNELS_EVENTS;
#pragma GCC diagnostic pop

  for (int i = 0; i < NHW_VPR_TOTAL_INST; i++) {
    nhw_vpr_st[i].VPR_regs = &NRF_VPR_regs[i];
    nhw_vpr_st[i].dppi_map = dppi_map[i];
    nhw_vpr_st[i].veif_taskevent_mask = veif_taskevent_masks[i];
    nhw_vpr_st[i].veif_dppi_mask = veif_dppi_masks[i];
    nhw_vpr_st[i].veif_ext_irq_mask = veif_ext_irq_masks[i];
    nhw_vpr_st[i].veif_clic_irq_mask = veif_clic_irq_masks[i];
    memcpy(&nhw_vpr_st[i].dppi_channels_tasks, &dppi_channels_tasks[i], sizeof(int)*NHW_VPR_VEIF_MAX_TASKSEVENTS);
    memcpy(&nhw_vpr_st[i].dppi_channels_events, &dppi_channels_events[i], sizeof(int)*NHW_VPR_VEIF_MAX_TASKSEVENTS);

    NRF_VPR_regs[i].DEBUGIF.DMSTATUS = VPR_DEBUGIF_DMSTATUS_ResetValue;
    NRF_VPR_regs[i].DEBUGIF.ABSTRACTCS = VPR_DEBUGIF_ABSTRACTCS_ResetValue;
    NRF_VPR_regs[i].DEBUGIF.SBCS = VPR_DEBUGIF_SBCS_ResetValue;
  }
}

NSI_TASK(nhw_vpr_init, HW_INIT, 100);

/* External interrupts (not internally towards CLIC) */
static void nhw_VPR_eval_interrupt(uint inst) {
  static bool vpr_int_line[NHW_VPR_TOTAL_INST]; /* Is the VPR currently driving its interrupt line high */
  /* Mapping of peripheral instance to {int controller instance, int number} */
  static struct nhw_irq_mapping nhw_vpr_ext_irq_map[NHW_VPR_TOTAL_INST] = NHW_VPR_INT_MAP;
  bool new_int_line = false;

  new_int_line = ( nhw_vpr_st[inst].intern_regs.EVENTS
                 & nhw_vpr_st[inst].VPR_regs->INTEN
                 & nhw_vpr_st[inst].veif_ext_irq_mask
                 ) != 0;

  NRF_VPR_regs[inst].INTPEND = nhw_vpr_st[inst].intern_regs.EVENTS & NRF_VPR_regs[inst].INTEN;

  hw_irq_ctrl_toggle_level_irq_line_if(&vpr_int_line[inst],
                                       new_int_line,
                                       &nhw_vpr_ext_irq_map[inst]);
}

static void nhw_VPR_eval_clic_interrupt(uint inst) {
  static bool vpr_clic_int_line[NHW_VPR_TOTAL_INST][NHW_VPR_VEIF_MAX_TASKSEVENTS]; /* Is the VPR currently driving this CLIC interrupt line high */
  /* Mapping of [peripheral instance][line] to {int controller instance, int number} */
  static struct nhw_irq_mapping nhw_vpr_clic_irq_map[NHW_VPR_TOTAL_INST][NHW_VPR_VEIF_MAX_TASKSEVENTS] = NHW_VPR_CLIC_INT_MAP;

  uint64_t TASKS_to_CLIC = nhw_vpr_st[inst].intern_regs.TASKS & nhw_vpr_st[inst].veif_clic_irq_mask;

  for (int line = 0; line < NHW_VPR_VEIF_MAX_TASKSEVENTS; line ++) {
      bool new_int_line = (TASKS_to_CLIC >> line) & 1;

      hw_irq_ctrl_toggle_level_irq_line_if(&vpr_clic_int_line[inst][line],
                                           new_int_line,
                                           &nhw_vpr_clic_irq_map[inst][line]);
  }
}

static void nhw_vpr_common_subscribe_sideeffect(unsigned int dppi_inst,
                                         bool en,
                                         bool new_channel,
                                         struct nhw_subsc_mem *last,
                                         dppi_callback_t callback,
                                         void *param)
{
  if ((last->is_subscribed == en)
    && (last->subscribed_ch == new_channel)) {
    //Nothing has changed
    return;
  }

  if (last->is_subscribed == true) {
    nhw_dppi_channel_unsubscribe(dppi_inst,
                                 last->subscribed_ch,
                                 callback,
                                 param);
  }
  last->is_subscribed = en;
  last->subscribed_ch = new_channel;
  if (en) {
    nhw_dppi_channel_subscribe(dppi_inst,
                               new_channel,
                               callback,
                               param);
  }
}

#define LIMIT_REG_TO_MASK(this, reg, mask) \
  do { \
    if (this->intern_regs.reg & ~(mask)) { \
      bs_trace_warning_time_line("Unconnected bits of " #reg " set (0x%X), discarding them\n", this->intern_regs.reg); \
      this->intern_regs.reg &= (mask); \
    } \
  } while (0)

static void nhw_vpr_inner_TASKS_changed(uint inst) {
  struct vpr_status *this = &nhw_vpr_st[inst];
  LIMIT_REG_TO_MASK(this, TASKS, this->veif_taskevent_mask);

  nhw_VPR_eval_clic_interrupt(inst);
}

#define FOR_EACH_BITINDEX_i_IN_MASK(mask) \
  for (uint32_t _mask = (mask), i = 0; \
       _mask != 0 && (i = __builtin_ctz(_mask), 1); \
       _mask &= _mask - 1)

static void nhw_vpr_inner_EVENTS_changed(uint inst, uint32_t value) {
  struct vpr_status *this = &nhw_vpr_st[inst];

  LIMIT_REG_TO_MASK(this, EVENTS, this->veif_taskevent_mask);
  value &= this->veif_taskevent_mask;

  nhw_VPR_eval_interrupt(inst);

  FOR_EACH_BITINDEX_i_IN_MASK(value) {
    if ((this->intern_regs.PUBLISH >> i) & 1) {
      int ch = this->dppi_channels_events[i];

      nhw_dppi_event_signal(this->dppi_map, ch);
    }
  }
}

static void nhw_vpr_inner_TASKS_set(uint inst, int n) {
  struct vpr_status *this = &nhw_vpr_st[inst];
  this->intern_regs.TASKS |= (1U << n);
  nhw_vpr_inner_TASKS_changed(inst);
}

static void nhw_VPR_TASK_dppi_wrap(void *p) {
  int inst = (intptr_t)p >> 8;
  int task_nbr = (intptr_t)p & 0xFF;
  nhw_vpr_inner_TASKS_set(inst, task_nbr);
}

static void nhw_vpr_inner_SUBSCRIBE_changed(uint inst) {
  static struct nhw_subsc_mem subscribed[NHW_VPR_TOTAL_INST][NHW_VPR_VEIF_MAX_TASKSEVENTS];
  struct vpr_status *this = &nhw_vpr_st[inst];

  LIMIT_REG_TO_MASK(this, SUBSCRIBE, this->veif_dppi_mask);

  FOR_EACH_BITINDEX_i_IN_MASK(this->veif_dppi_mask) {
    int en = (this->intern_regs.SUBSCRIBE >> i) & 1;
    int ch = this->dppi_channels_tasks[i];

    nhw_vpr_common_subscribe_sideeffect(this->dppi_map,
                                        en,
                                        ch,
                                        &subscribed[inst][i],
                                        nhw_VPR_TASK_dppi_wrap,
                                        (void*)(((intptr_t)inst << 8) + i));
  }
}

#define NHW_VPR_UPDATE_SUBSCRIBE_TRIGGER(inst, n, en) \
  NRF_VPR_regs[inst].SUBSCRIBE_TRIGGER[n] = (uint32_t)en << VPR_SUBSCRIBE_TRIGGER_EN_Pos | n

#define NHW_VPR_UPDATE_PUBLISH_TRIGGERED(inst, n, en) \
  NRF_VPR_regs[inst].PUBLISH_TRIGGERED[n] = (uint32_t)en << VPR_PUBLISH_TRIGGERED_EN_Pos | n

#define NHW_VPR_UPDATE_EVENTS_TRIGGERED(inst, n, en) \
  NRF_VPR_regs[inst].EVENTS_TRIGGERED[n] = (uint32_t)en << VPR_EVENTS_TRIGGERED_EVENTS_TRIGGERED_Pos


void nhw_vpr_regw_sideeffects_csr_TASKS(uint inst) {
  nhw_vpr_inner_TASKS_changed(inst);

  //Note the APB TASKS_TRIGGERED registers always read as 0. Nothing needs updating.
}

void nhw_vpr_regw_sideeffects_csr_EVENTS(uint inst) {
  nhw_vpr_inner_EVENTS_changed(inst, nhw_vpr_st[inst].intern_regs.EVENTS);

  //Update all APB EVENTS_TRIGGERED registers:
  uint32_t EVENTS = nhw_vpr_st[inst].intern_regs.EVENTS;

  FOR_EACH_BITINDEX_i_IN_MASK(nhw_vpr_st[inst].veif_taskevent_mask) {
    bool en = (EVENTS >> i) & 1;
    NHW_VPR_UPDATE_EVENTS_TRIGGERED(inst, i, en);
  }
}

void nhw_vpr_regw_sideeffects_csr_SUBSCRIBE(uint inst) {
  nhw_vpr_inner_SUBSCRIBE_changed(inst);

  //Update all APB SUBSCRIBE_TRIGERED registers:
  uint32_t SUBSCRIBE = nhw_vpr_st[inst].intern_regs.SUBSCRIBE;

  FOR_EACH_BITINDEX_i_IN_MASK(nhw_vpr_st[inst].veif_dppi_mask) {
    bool en = (SUBSCRIBE >> i) & 1;
    NHW_VPR_UPDATE_SUBSCRIBE_TRIGGER(inst, i, en);
  }
}

void nhw_vpr_regw_sideeffects_csr_PUBLISH(uint inst) {
  struct vpr_status *this = &nhw_vpr_st[inst];

  LIMIT_REG_TO_MASK(this, PUBLISH, this->veif_dppi_mask);

  //Update all APB PUBLISH_TRIGERED registers:
  uint32_t PUBLISH = this->intern_regs.PUBLISH;

  FOR_EACH_BITINDEX_i_IN_MASK(this->veif_dppi_mask) {
    bool en = (PUBLISH >> i) & 1;
    NHW_VPR_UPDATE_PUBLISH_TRIGGERED(inst, i, en);
  }
}

NHW_SIDEEFFECTS_INTCLR(VPR, NRF_VPR_regs[inst]., NRF_VPR_regs[inst].INTEN)
void nhw_VPR_regw_sideeffects_INTEN(uint inst) {
  NRF_VPR_regs[inst].INTEN &= nhw_vpr_st[inst].veif_ext_irq_mask;
  NRF_VPR_regs[inst].INTENSET = NRF_VPR_regs[inst].INTEN;
  nhw_VPR_eval_interrupt(inst);
}

void nhw_VPR_regw_sideeffects_INTENSET(uint inst) {
  if (NRF_VPR_regs[inst].INTENSET) { /* LCOV_EXCL_BR_LINE */
    NRF_VPR_regs[inst].INTEN |= NRF_VPR_regs[inst].INTENSET;
    nhw_VPR_regw_sideeffects_INTEN(inst);
  }
}

void nhw_VPR_regw_sideeffects_TASK_TRIGGER(uint inst, uint n) {
  if (NRF_VPR_regs[inst].TASKS_TRIGGER[n] & VPR_TASKS_TRIGGER_TASKS_TRIGGER_Msk) {
    nhw_vpr_inner_TASKS_set(inst, n);
  }

  //Set it back to the read value: Always 0
  NRF_VPR_regs[inst].TASKS_TRIGGER[n] = 0;
}

void nhw_VPR_regw_sideeffects_EVENTS_TRIGGERED(uint inst, uint n) {
  struct vpr_status *this = &nhw_vpr_st[inst];
  bool en = NRF_VPR_regs[inst].EVENTS_TRIGGERED[n] & VPR_EVENTS_TRIGGERED_EVENTS_TRIGGERED_Msk;

  if (en == false) { //EVENTS_TRIGGERED can only clear EVENTS[n], it cannot set it
    this->intern_regs.EVENTS &= ~(1U << n);
    nhw_vpr_inner_EVENTS_changed(inst, 0);
  }

  //Set it back to the read value:
  en = (this->intern_regs.EVENTS >> n) & 1;
  NHW_VPR_UPDATE_EVENTS_TRIGGERED(inst, n, en);
}

void nhw_VPR_regw_sideeffects_SUBSCRIBE_TRIGGER(uint inst, uint n) {
  struct vpr_status *this = &nhw_vpr_st[inst];
  uint32_t reg = NRF_VPR_regs[inst].SUBSCRIBE_TRIGGER[n];
  uint32_t mask = 1U << n;
  bool en = (reg & VPR_SUBSCRIBE_TRIGGER_EN_Msk) || (reg & 1);

  if ((mask & nhw_vpr_st[inst].veif_dppi_mask) == 0) {
    bs_trace_warning_time_line("VPR[%i].SUBSCRIBE_TRIGGER[%i] is not a valid register, "
                               "clearing and ignoring it\n", inst, n);
    NRF_VPR_regs[inst].SUBSCRIBE_TRIGGER[n] = 0;
    return;
  } else {
    if (en) {
      this->intern_regs.SUBSCRIBE |= mask;
    } else {
      this->intern_regs.SUBSCRIBE &= ~mask;
    }
  }

  //Set it back to the read value:
  NHW_VPR_UPDATE_SUBSCRIBE_TRIGGER(inst, n, en);

  nhw_vpr_inner_SUBSCRIBE_changed(inst);
}

void nhw_VPR_regw_sideeffects_PUBLISH_TRIGGERED(uint inst, uint n) {
  struct vpr_status *this = &nhw_vpr_st[inst];
  uint32_t reg = NRF_VPR_regs[inst].PUBLISH_TRIGGERED[n];
  uint32_t mask = 1U << n;
  bool en = (reg & VPR_PUBLISH_TRIGGERED_EN_Msk) || (reg & 1);

  if ((mask & nhw_vpr_st[inst].veif_dppi_mask) == 0) {
    bs_trace_warning_time_line("VPR[%i].PUBLISH_TRIGGERED[%i] is not a valid register, "
                               "clearing and ignoring it\n", inst, n);
    NRF_VPR_regs[inst].PUBLISH_TRIGGERED[n] = 0;
    return;
  } else {
    if (en) {
      this->intern_regs.PUBLISH |= mask;
    } else {
      this->intern_regs.PUBLISH &= ~mask;
    }
  }

  //Set it back to the read value:
  NHW_VPR_UPDATE_PUBLISH_TRIGGERED(inst, n, en);
}


/* Try to get the VPR instance number which matches the currently running CPU number.
 * If we cannot return 0 (the first instance) */
int nhw_vpr_get_vpr_instance(void) {
  static int instances[] = NHW_VPR_CPU_NBRS;
  int current_cpu_nbr = nce_get_current_cpu_nbr();

  if (current_cpu_nbr < 0) {
    bs_trace_warning_line_time("Could not get the current_cpu_nbr from integration (%i)\n", current_cpu_nbr);
    return 0;
  }

  for (unsigned int i = 0; i < NSI_ARRAY_SIZE(instances); i++) {
    if (instances[i] == current_cpu_nbr) {
      return i;
    }
  }
  bs_trace_warning_line_time("current_cpu_nbr (%i) does not match any known VPR instance\n", current_cpu_nbr);
  return 0;
}
