/*
 * Copyright (c) 2026 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _NRF_HW_MODEL_SRC_HW_MODELS_HW_IRQ_ROUTER_H
#define _NRF_HW_MODEL_SRC_HW_MODELS_HW_IRQ_ROUTER_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This interrupt router component can route interrupts from one peripheral into
 * multiple interrupt controllers.
 *
 * Note this does not try to model a typical real HW component, just hard-wiring.
 */

#define HW_IRQR_TO_ROUTER    -1 /* Interrupt line is connected to the router */
#define HW_IRQR_DISCONNECTED -2 /* Interrupt line is not connected to anything */

/*
 * Equivalent APIs to hw_irq_ctrl_*() which are routed through the irq_router.
 * The router will forward the interrupt to the necessary interrupt controllers,
 * given the "global" router_irqn and its lookup table.
 */
void hw_irq_router_set_irq(int router_nbr, unsigned int router_irqn);
void hw_irq_router_raise_level_irq_line(int router_nbr, unsigned int router_irqn);
void hw_irq_router_lower_level_irq_line(int router_nbr, unsigned int router_irqn);

#ifdef __cplusplus
}
#endif

#endif /* _NRF_HW_MODEL_SRC_HW_MODELS_HW_IRQ_ROUTER_H */
