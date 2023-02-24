/*
 * Copyright (c) 2017 Oticon A/S
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file includes the RADIO event & signals functionality
 * That is, when a signal is generated:
 *   Setting the EVENTS registers
 *   Sending the signal to the PPI
 *   Generating the corresponding interrupts
 *   Calling tasks if the corresponding shortcuts are enabled
 *
 * There should not be any logic beyond that here.
 */

#include "NRF_RADIO.h"
#include "NRF_PPI.h"
#include "irq_ctrl.h"

extern uint32_t NRF_RADIO_INTEN; //interrupt enable

void nrf_radio_signal_READY(){
  NRF_RADIO_regs.EVENTS_READY = 1;
  nrf_ppi_event(RADIO_EVENTS_READY);

  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_READY_START_Msk ) {
    nrf_radio_tasks_start();
  }

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_READY_Msk ){
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

/* The TX and RX READY are missing in the registers header..
void nrf_radio_signal_TXREADY(){
  NRF_RADIO_regs.EVENTS_TXREADY = 1;
  nrf_ppi_event(RADIO_EVENTS_TXREADY);

  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_TXREADY_START_Msk ) {
    NRF_RADIO_TASK_START();
  }

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_TXREADY_Msk ){
    hw_irq_controller_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_RXREADY(){
  NRF_RADIO_regs.EVENTS_RXREADY = 1;
  nrf_ppi_event(RADIO_EVENTS_RXREADY);

  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_RXREADY_START_Msk ) {
    NRF_RADIO_TASK_START();
  }

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_RXREADY_Msk ){
    hw_irq_controller_set_irq(RADIO_IRQn);
  }
}
*/

extern void nrf_radio_fake_task_TRXEN_TIFS();

void nrf_radio_signal_DISABLED(){
  NRF_RADIO_regs.EVENTS_DISABLED = 1;
  nrf_ppi_event(RADIO_EVENTS_DISABLED);

  //These 2 are fake shortcuts meant to start a HW timer for the TIFS
  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_DISABLED_TXEN_Msk ) {
    nrf_radio_fake_task_TRXEN_TIFS();
  }
  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_DISABLED_RXEN_Msk ) {
    nrf_radio_fake_task_TRXEN_TIFS();
  }

  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_DISABLED_RSSISTOP_Msk ) {
    nrf_radio_tasks_rssistop();
  }

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_DISABLED_Msk ) {
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_RSSIEND(){
  NRF_RADIO_regs.EVENTS_RSSIEND = 1;
  nrf_ppi_event(RADIO_EVENTS_RSSIEND);

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_RSSIEND_Msk ){
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_ADDRESS(){
  NRF_RADIO_regs.EVENTS_ADDRESS = 1;
  nrf_ppi_event(RADIO_EVENTS_ADDRESS);

  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_ADDRESS_RSSISTART_Msk ) {
    nrf_radio_tasks_rssistart();
  }
  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_ADDRESS_BCSTART_Msk ) {
    nrf_radio_tasks_bcstart();
  }

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_ADDRESS_Msk ){
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_PAYLOAD(){
  NRF_RADIO_regs.EVENTS_PAYLOAD = 1;
  nrf_ppi_event(RADIO_EVENTS_PAYLOAD);

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_PAYLOAD_Msk ){
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_CRCOK(){
  NRF_RADIO_regs.EVENTS_CRCOK = 1;
  nrf_ppi_event(RADIO_EVENTS_CRCOK);

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_CRCOK_Msk ) {
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_CRCERROR(){
  NRF_RADIO_regs.EVENTS_CRCERROR = 1;
  nrf_ppi_event(RADIO_EVENTS_CRCERROR);

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_CRCERROR_Msk ) {
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_END(){
  NRF_RADIO_regs.EVENTS_END = 1;
  nrf_ppi_event(RADIO_EVENTS_END);

  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_END_DISABLE_Msk ) {
    nrf_radio_tasks_disable();
  }
  if ( NRF_RADIO_regs.SHORTS & RADIO_SHORTS_END_START_Msk ) {
    nrf_radio_tasks_start();
  }

  if ( NRF_RADIO_INTEN & RADIO_INTENSET_END_Msk ) {
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_DEVMATCH() {
  NRF_RADIO_regs.EVENTS_DEVMATCH = 1;
  nrf_ppi_event(RADIO_EVENTS_DEVMATCH);

  if (NRF_RADIO_INTEN & RADIO_INTENSET_DEVMATCH_Msk) {
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_DEVMISS() {
  NRF_RADIO_regs.EVENTS_DEVMISS = 1;
  nrf_ppi_event(RADIO_EVENTS_DEVMISS);

  if (NRF_RADIO_INTEN & RADIO_INTENSET_DEVMISS_Msk) {
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}

void nrf_radio_signal_BCMATCH() {
  NRF_RADIO_regs.EVENTS_BCMATCH = 1;
  nrf_ppi_event(RADIO_EVENTS_BCMATCH);

  if (NRF_RADIO_INTEN & RADIO_INTENSET_BCMATCH_Msk) {
    hw_irq_ctrl_set_irq(RADIO_IRQn);
  }
}