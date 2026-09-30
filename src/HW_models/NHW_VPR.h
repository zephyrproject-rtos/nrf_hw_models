/*
 * Copyright (c) 2026 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _NRF_HW_MODELS_NHW_VPR_H
#define _NRF_HW_MODELS_NHW_VPR_H

#include <stdint.h>
#include "bs_types.h"
#include "NHW_config.h"

#ifdef __cplusplus
extern "C"{
#endif

struct vpr_internal_regs {
    //INTEN and the VPR_regs one are the same => access it there
    uint32_t EVENTS;
    //uint32_t EVENTSB;
    //uint32_t EVENTSBS;
    uint32_t PUBLISH;
    uint32_t TASKS;
    uint32_t SUBSCRIBE;
};
struct vpr_internal_regs *nhw_vpr_get_internal_regs(uint inst);

void nhw_vpr_regw_sideeffects_csr_TASKS(uint inst);
void nhw_vpr_regw_sideeffects_csr_EVENTS(uint inst);
void nhw_vpr_regw_sideeffects_csr_SUBSCRIBE(uint inst);
void nhw_vpr_regw_sideeffects_csr_PUBLISH(uint inst);

void nhw_VPR_regw_sideeffects_INTEN(uint inst);
void nhw_VPR_regw_sideeffects_INTENSET(uint inst);
void nhw_VPR_regw_sideeffects_INTENCLR(uint inst);

void nhw_VPR_regw_sideeffects_TASK_TRIGGER(uint inst, uint n);
void nhw_VPR_regw_sideeffects_SUBSCRIBE_TRIGGER(uint inst, uint n);
void nhw_VPR_regw_sideeffects_EVENTS_TRIGGERED(uint inst, uint n);
void nhw_VPR_regw_sideeffects_PUBLISH_TRIGGERED(uint inst, uint n);

/* Note this API is meant to be called from SW only*/
int nhw_vpr_get_vpr_instance(void);

#ifdef __cplusplus
}
#endif

#endif /* _NRF_HW_MODELS_NHW_VPR_H */
