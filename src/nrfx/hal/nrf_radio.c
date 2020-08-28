/*
 * Copyright (c) 2017 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Note that the function prototypes are taken from the NRFx HAL
 */
#include "hal/nrf_radio.h"
#include "bs_tracing.h"
#include "NRF_RADIO.h"

void nrf_radio_task_trigger(NRF_RADIO_Type * p_reg, nrf_radio_task_t task)
{
  if ( task == NRF_RADIO_TASK_TXEN ) {
    p_reg->TASKS_TXEN = 1;
    nrf_radio_regw_sideeffects_TASKS_TXEN();
  } else if ( task == NRF_RADIO_TASK_RXEN ) {
    p_reg->TASKS_RXEN = 1;
    nrf_radio_regw_sideeffects_TASKS_RXEN();
  } else if ( task == NRF_RADIO_TASK_DISABLE ) {
    p_reg->TASKS_DISABLE = 1;
    nrf_radio_regw_sideeffects_TASKS_DISABLE();
  } else if ( task == NRF_RADIO_TASK_RSSISTOP ) {
    p_reg->TASKS_RSSISTOP = 1;
    nrf_radio_regw_sideeffects_TASKS_RSSISTOP();
  } else if ( task == NRF_RADIO_TASK_RSSISTART ) {
    p_reg->TASKS_RSSISTART = 1;
    nrf_radio_regw_sideeffects_TASKS_RSSISTART();
  } else {
    bs_trace_error_line_time("Not supported task started in nrf_radio\n");
  }
}

void nrf_radio_int_enable(NRF_RADIO_Type * p_reg, uint32_t mask)
{
  p_reg->INTENSET = mask;
  nrf_radio_regw_sideeffects_INTENSET();
}

void nrf_radio_int_disable(NRF_RADIO_Type * p_reg, uint32_t mask)
{
  p_reg->INTENCLR = mask;
  nrf_radio_regw_sideeffects_INTENCLR();
}

void nrf_radio_bcc_set(NRF_RADIO_Type * p_reg, uint32_t radio_bcc)
{
  p_reg->BCC = radio_bcc;
  nrf_radio_regw_sideeffects_BCC();
}

void nrf_radio_power_set(NRF_RADIO_Type * p_reg, bool radio_power)
{
  p_reg->POWER = (uint32_t) radio_power;
  nrf_radio_regw_sideeffects_POWER();
}


NRF_STATIC_INLINE void nrf_radio_event_clear(NRF_RADIO_Type * p_reg, nrf_radio_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
#if __CORTEX_M == 0x04
    volatile uint32_t dummy = *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event));
    (void)dummy;
#endif
}

NRF_STATIC_INLINE bool nrf_radio_event_check(NRF_RADIO_Type const * p_reg, nrf_radio_event_t event)
{
    return (bool) *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event));
}

NRF_STATIC_INLINE void nrf_radio_shorts_enable(NRF_RADIO_Type * p_reg, uint32_t shorts_mask)
{
    p_reg->SHORTS |= shorts_mask;
}

NRF_STATIC_INLINE void nrf_radio_shorts_disable(NRF_RADIO_Type * p_reg, uint32_t shorts_mask)
{
    p_reg->SHORTS &= ~shorts_mask;
}

NRF_STATIC_INLINE void nrf_radio_shorts_set(NRF_RADIO_Type * p_reg, uint32_t shorts_mask)
{
    p_reg->SHORTS = shorts_mask;
}

NRF_STATIC_INLINE uint32_t nrf_radio_int_enable_check(NRF_RADIO_Type const * p_reg, uint32_t mask)
{
    return p_reg->INTENSET & mask;
}

NRF_STATIC_INLINE bool nrf_radio_crc_status_check(NRF_RADIO_Type const * p_reg)
{
    return ((p_reg->CRCSTATUS & RADIO_CRCSTATUS_CRCSTATUS_Msk) >> RADIO_CRCSTATUS_CRCSTATUS_Pos)
             == RADIO_CRCSTATUS_CRCSTATUS_CRCOk ;
}

NRF_STATIC_INLINE uint8_t nrf_radio_dai_get(NRF_RADIO_Type const * p_reg)
{
    return (uint8_t)p_reg->DAI;
}

NRF_STATIC_INLINE void nrf_radio_packetptr_set(NRF_RADIO_Type * p_reg, void const * p_packet)
{
    p_reg->PACKETPTR = (uint32_t)p_packet;
}

NRF_STATIC_INLINE void * nrf_radio_packetptr_get(NRF_RADIO_Type const * p_reg)
{
    return (void *)p_reg->PACKETPTR;
}

NRF_STATIC_INLINE void nrf_radio_frequency_set(NRF_RADIO_Type * p_reg, uint16_t radio_frequency)
{
    NRFX_ASSERT(radio_frequency <= 2500);
    NRFX_ASSERT(radio_frequency >= 2400);
    p_reg->FREQUENCY = (uint32_t)(radio_frequency - 2400);
}

NRF_STATIC_INLINE void nrf_radio_txpower_set(NRF_RADIO_Type * p_reg, nrf_radio_txpower_t tx_power)
{
    p_reg->TXPOWER = (((uint32_t)tx_power) << RADIO_TXPOWER_TXPOWER_Pos);
}

NRF_STATIC_INLINE void nrf_radio_mode_set(NRF_RADIO_Type * p_reg, nrf_radio_mode_t radio_mode)
{
    p_reg->MODE = ((uint32_t) radio_mode << RADIO_MODE_MODE_Pos);
}

NRF_STATIC_INLINE nrf_radio_mode_t nrf_radio_mode_get(NRF_RADIO_Type const * p_reg)
{
    return (nrf_radio_mode_t)((p_reg->MODE & RADIO_MODE_MODE_Msk) >> RADIO_MODE_MODE_Pos);
}

NRF_STATIC_INLINE void nrf_radio_packet_configure(NRF_RADIO_Type *                p_reg,
                                                  nrf_radio_packet_conf_t const * p_config)
{
    p_reg->PCNF0 = (((uint32_t)p_config->lflen << RADIO_PCNF0_LFLEN_Pos) |
                    ((uint32_t)p_config->s0len << RADIO_PCNF0_S0LEN_Pos) |
                    ((uint32_t)p_config->s1len << RADIO_PCNF0_S1LEN_Pos) |
#if defined(RADIO_PCNF0_S1INCL_Msk)
                    (p_config->s1incl ?
                        (RADIO_PCNF0_S1INCL_Include   << RADIO_PCNF0_S1INCL_Pos) :
                        (RADIO_PCNF0_S1INCL_Automatic << RADIO_PCNF0_S1INCL_Pos) ) |
#endif
#if defined(RADIO_PCNF0_CILEN_Msk)
                    ((uint32_t)p_config->cilen << RADIO_PCNF0_CILEN_Pos) |
#endif
#if defined(RADIO_PCNF0_PLEN_Msk)
                    ((uint32_t)p_config->plen << RADIO_PCNF0_PLEN_Pos) |
#endif
#if defined(RADIO_PCNF0_CRCINC_Msk)
                    (p_config->crcinc ?
                        (RADIO_PCNF0_CRCINC_Include << RADIO_PCNF0_CRCINC_Pos) :
                        (RADIO_PCNF0_CRCINC_Exclude << RADIO_PCNF0_CRCINC_Pos) ) |
#endif
#if defined(RADIO_PCNF0_TERMLEN_Msk)
                    ((uint32_t)p_config->termlen << RADIO_PCNF0_TERMLEN_Pos) |
#endif
                    0);

    p_reg->PCNF1 = (((uint32_t)p_config->maxlen  << RADIO_PCNF1_MAXLEN_Pos) |
                    ((uint32_t)p_config->statlen << RADIO_PCNF1_STATLEN_Pos) |
                    ((uint32_t)p_config->balen   << RADIO_PCNF1_BALEN_Pos) |
                    (p_config->big_endian ?
                         (RADIO_PCNF1_ENDIAN_Big    << RADIO_PCNF1_ENDIAN_Pos) :
                         (RADIO_PCNF1_ENDIAN_Little << RADIO_PCNF1_ENDIAN_Pos) ) |
                    (p_config->whiteen ?
                         (RADIO_PCNF1_WHITEEN_Enabled  << RADIO_PCNF1_WHITEEN_Pos) :
                         (RADIO_PCNF1_WHITEEN_Disabled << RADIO_PCNF1_WHITEEN_Pos) ));
}

NRF_STATIC_INLINE void nrf_radio_base0_set(NRF_RADIO_Type * p_reg, uint32_t address)
{
    p_reg->BASE0 = address;
}

NRF_STATIC_INLINE void nrf_radio_prefix0_set(NRF_RADIO_Type * p_reg, uint32_t prefixes)
{
    p_reg->PREFIX0 = prefixes;
}

NRF_STATIC_INLINE void nrf_radio_rxaddresses_set(NRF_RADIO_Type * p_reg, uint8_t rxaddresses)
{
    p_reg->RXADDRESSES = (uint32_t)(rxaddresses);
}

NRF_STATIC_INLINE void nrf_radio_crc_configure(NRF_RADIO_Type *     p_reg,
                                               uint8_t              crc_length,
                                               nrf_radio_crc_addr_t crc_address,
                                               uint32_t             crc_polynominal)
{
    p_reg->CRCCNF = ((uint32_t)crc_length  << RADIO_CRCCNF_LEN_Pos) |
                    ((uint32_t)crc_address << RADIO_CRCCNF_SKIPADDR_Pos);
    p_reg->CRCPOLY = (crc_polynominal << RADIO_CRCPOLY_CRCPOLY_Pos);
}

NRF_STATIC_INLINE void nrf_radio_crcinit_set(NRF_RADIO_Type * p_reg, uint32_t crc_init_value)
{
    p_reg->CRCINIT = crc_init_value;
}

NRF_STATIC_INLINE uint32_t nrf_radio_crcinit_get(NRF_RADIO_Type const * p_reg)
{
    return p_reg->CRCINIT;
}

NRF_STATIC_INLINE uint8_t nrf_radio_rssi_sample_get(NRF_RADIO_Type const * p_reg)
{
    return (uint8_t)((p_reg->RSSISAMPLE & RADIO_RSSISAMPLE_RSSISAMPLE_Msk) >>
                     RADIO_RSSISAMPLE_RSSISAMPLE_Pos);
}

NRF_STATIC_INLINE nrf_radio_state_t nrf_radio_state_get(NRF_RADIO_Type const * p_reg)
{
    return (nrf_radio_state_t) p_reg->STATE;
}

NRF_STATIC_INLINE void nrf_radio_datawhiteiv_set(NRF_RADIO_Type * p_reg, uint8_t datawhiteiv)
{
    p_reg->DATAWHITEIV = (((uint32_t)datawhiteiv) & RADIO_DATAWHITEIV_DATAWHITEIV_Msk);
}

NRF_STATIC_INLINE void nrf_radio_dab_set(NRF_RADIO_Type * p_reg,
                                         uint32_t         dab_value,
                                         uint8_t          segment)
{
    NRFX_ASSERT(segment < 8);
    p_reg->DAB[segment] = dab_value;
}

NRF_STATIC_INLINE void nrf_radio_dap_set(NRF_RADIO_Type * p_reg,
                                         uint16_t         dap_value,
                                         uint8_t          prefix_index)
{
    NRFX_ASSERT(prefix_index < 8);
    p_reg->DAP[prefix_index] = (uint32_t)dap_value;
}

NRF_STATIC_INLINE void nrf_radio_dacnf_set(NRF_RADIO_Type * p_reg, uint8_t ena, uint8_t txadd)
{
    p_reg->DACNF = (((uint32_t)ena   << RADIO_DACNF_ENA0_Pos) |
                    ((uint32_t)txadd << RADIO_DACNF_TXADD0_Pos));
}

NRF_STATIC_INLINE uint8_t nrf_radio_dacnf_ena_get(NRF_RADIO_Type const * p_reg)
{
    return (p_reg->DACNF & (RADIO_DACNF_ENA0_Msk |
                            RADIO_DACNF_ENA1_Msk |
                            RADIO_DACNF_ENA2_Msk |
                            RADIO_DACNF_ENA3_Msk |
                            RADIO_DACNF_ENA4_Msk |
                            RADIO_DACNF_ENA5_Msk |
                            RADIO_DACNF_ENA6_Msk |
                            RADIO_DACNF_ENA7_Msk)) >> RADIO_DACNF_ENA0_Pos;
}

NRF_STATIC_INLINE uint8_t nrf_radio_dacnf_txadd_get(NRF_RADIO_Type const * p_reg)
{
    return (p_reg->DACNF & (RADIO_DACNF_TXADD0_Msk |
                            RADIO_DACNF_TXADD1_Msk |
                            RADIO_DACNF_TXADD2_Msk |
                            RADIO_DACNF_TXADD3_Msk |
                            RADIO_DACNF_TXADD4_Msk |
                            RADIO_DACNF_TXADD5_Msk |
                            RADIO_DACNF_TXADD6_Msk |
                            RADIO_DACNF_TXADD7_Msk)) >> RADIO_DACNF_TXADD0_Pos;
}

NRF_STATIC_INLINE void nrf_radio_modecnf0_set(NRF_RADIO_Type * p_reg,
                                              bool             fast_ramp_up,
                                              uint8_t          default_tx)
{
    p_reg->MODECNF0 = (fast_ramp_up ? (RADIO_MODECNF0_RU_Fast    << RADIO_MODECNF0_RU_Pos) :
                                      (RADIO_MODECNF0_RU_Default << RADIO_MODECNF0_RU_Pos) ) |
                      (((uint32_t)default_tx) << RADIO_MODECNF0_DTX_Pos);
}
