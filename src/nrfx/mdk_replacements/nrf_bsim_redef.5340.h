/*
 * Copyright (c) 2018 Oticon A/S
 * Copyright (c) 2020-2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#define NRF_FICR_NS_NET_BASE_REAL_HW            0x01FF0000UL
#define NRF_UICR_NS_NET_BASE_REAL_HW            0x01FF8000UL
#define NRF_CTI_NS_NET_BASE_REAL_HW             0xE0042000UL
#define NRF_DCNF_NS_NET_BASE_REAL_HW            0x41000000UL
#define NRF_VREQCTRL_NS_NET_BASE_REAL_HW        0x41004000UL
#define NRF_CLOCK_NS_NET_BASE_REAL_HW           0x41005000UL
#define NRF_POWER_NS_NET_BASE_REAL_HW           0x41005000UL
#define NRF_RESET_NS_NET_BASE_REAL_HW           0x41005000UL
#define NRF_CTRLAP_NS_NET_BASE_REAL_HW          0x41006000UL
#define NRF_RADIO_NS_NET_BASE_REAL_HW           0x41008000UL
#define NRF_RNG_NS_NET_BASE_REAL_HW             0x41009000UL
#define NRF_GPIOTE_NS_NET_BASE_REAL_HW          0x4100A000UL
#define NRF_WDT_NS_NET_BASE_REAL_HW             0x4100B000UL
#define NRF_TIMER0_NS_NET_BASE_REAL_HW          0x4100C000UL
#define NRF_ECB_NS_NET_BASE_REAL_HW             0x4100D000UL
#define NRF_AAR_NS_NET_BASE_REAL_HW             0x4100E000UL
#define NRF_CCM_NS_NET_BASE_REAL_HW             0x4100E000UL
#define NRF_DPPIC_NS_NET_BASE_REAL_HW           0x4100F000UL
#define NRF_TEMP_NS_NET_BASE_REAL_HW            0x41010000UL
#define NRF_RTC0_NS_NET_BASE_REAL_HW            0x41011000UL
#define NRF_IPC_NS_NET_BASE_REAL_HW             0x41012000UL
#define NRF_SPIM0_NS_NET_BASE_REAL_HW           0x41013000UL
#define NRF_SPIS0_NS_NET_BASE_REAL_HW           0x41013000UL
#define NRF_TWIM0_NS_NET_BASE_REAL_HW           0x41013000UL
#define NRF_TWIS0_NS_NET_BASE_REAL_HW           0x41013000UL
#define NRF_UARTE0_NS_NET_BASE_REAL_HW          0x41013000UL
#define NRF_EGU0_NS_NET_BASE_REAL_HW            0x41014000UL
#define NRF_RTC1_NS_NET_BASE_REAL_HW            0x41016000UL
#define NRF_TIMER1_NS_NET_BASE_REAL_HW          0x41018000UL
#define NRF_TIMER2_NS_NET_BASE_REAL_HW          0x41019000UL
#define NRF_SWI0_NS_NET_BASE_REAL_HW            0x4101A000UL
#define NRF_SWI1_NS_NET_BASE_REAL_HW            0x4101B000UL
#define NRF_SWI2_NS_NET_BASE_REAL_HW            0x4101C000UL
#define NRF_SWI3_NS_NET_BASE_REAL_HW            0x4101D000UL
#define NRF_APPMUTEX_NS_NET_BASE_REAL_HW        0x40030000UL
#define NRF_APPMUTEX_S_NET_BASE_REAL_HW         0x50030000UL
#define NRF_ACL_NS_NET_BASE_REAL_HW             0x41080000UL
#define NRF_NVMC_NS_NET_BASE_REAL_HW            0x41080000UL
#define NRF_VMC_NS_NET_BASE_REAL_HW             0x41081000UL
#define NRF_P0_NS_NET_BASE_REAL_HW              0x418C0500UL
#define NRF_P1_NS_NET_BASE_REAL_HW              0x418C0800UL

#define NRF_CACHEDATA_S_APP_BASE_REAL_HW        0x00F00000UL
#define NRF_CACHEINFO_S_APP_BASE_REAL_HW        0x00F08000UL
#define NRF_FICR_S_APP_BASE_REAL_HW             0x00FF0000UL
#define NRF_UICR_S_APP_BASE_REAL_HW             0x00FF8000UL
#define NRF_CTI_S_APP_BASE_REAL_HW              0xE0042000UL
#define NRF_TAD_S_APP_BASE_REAL_HW              0xE0080000UL
#define NRF_DCNF_NS_APP_BASE_REAL_HW            0x40000000UL
#define NRF_FPU_NS_APP_BASE_REAL_HW             0x40000000UL
#define NRF_DCNF_S_APP_BASE_REAL_HW             0x50000000UL
#define NRF_FPU_S_APP_BASE_REAL_HW              0x50000000UL
#define NRF_CACHE_S_APP_BASE_REAL_HW            0x50001000UL
#define NRF_SPU_S_APP_BASE_REAL_HW              0x50003000UL
#define NRF_OSCILLATORS_NS_APP_BASE_REAL_HW     0x40004000UL
#define NRF_REGULATORS_NS_APP_BASE_REAL_HW      0x40004000UL
#define NRF_OSCILLATORS_S_APP_BASE_REAL_HW      0x50004000UL
#define NRF_REGULATORS_S_APP_BASE_REAL_HW       0x50004000UL
#define NRF_CLOCK_NS_APP_BASE_REAL_HW           0x40005000UL
#define NRF_POWER_NS_APP_BASE_REAL_HW           0x40005000UL
#define NRF_RESET_NS_APP_BASE_REAL_HW           0x40005000UL
#define NRF_CLOCK_S_APP_BASE_REAL_HW            0x50005000UL
#define NRF_POWER_S_APP_BASE_REAL_HW            0x50005000UL
#define NRF_RESET_S_APP_BASE_REAL_HW            0x50005000UL
#define NRF_CTRLAP_NS_APP_BASE_REAL_HW          0x40006000UL
#define NRF_CTRLAP_S_APP_BASE_REAL_HW           0x50006000UL
#define NRF_SPIM0_NS_APP_BASE_REAL_HW           0x40008000UL
#define NRF_SPIS0_NS_APP_BASE_REAL_HW           0x40008000UL
#define NRF_TWIM0_NS_APP_BASE_REAL_HW           0x40008000UL
#define NRF_TWIS0_NS_APP_BASE_REAL_HW           0x40008000UL
#define NRF_UARTE0_NS_APP_BASE_REAL_HW          0x40008000UL
#define NRF_SPIM0_S_APP_BASE_REAL_HW            0x50008000UL
#define NRF_SPIS0_S_APP_BASE_REAL_HW            0x50008000UL
#define NRF_TWIM0_S_APP_BASE_REAL_HW            0x50008000UL
#define NRF_TWIS0_S_APP_BASE_REAL_HW            0x50008000UL
#define NRF_UARTE0_S_APP_BASE_REAL_HW           0x50008000UL
#define NRF_SPIM1_NS_APP_BASE_REAL_HW           0x40009000UL
#define NRF_SPIS1_NS_APP_BASE_REAL_HW           0x40009000UL
#define NRF_TWIM1_NS_APP_BASE_REAL_HW           0x40009000UL
#define NRF_TWIS1_NS_APP_BASE_REAL_HW           0x40009000UL
#define NRF_UARTE1_NS_APP_BASE_REAL_HW          0x40009000UL
#define NRF_SPIM1_S_APP_BASE_REAL_HW            0x50009000UL
#define NRF_SPIS1_S_APP_BASE_REAL_HW            0x50009000UL
#define NRF_TWIM1_S_APP_BASE_REAL_HW            0x50009000UL
#define NRF_TWIS1_S_APP_BASE_REAL_HW            0x50009000UL
#define NRF_UARTE1_S_APP_BASE_REAL_HW           0x50009000UL
#define NRF_SPIM4_NS_APP_BASE_REAL_HW           0x4000A000UL
#define NRF_SPIM4_S_APP_BASE_REAL_HW            0x5000A000UL
#define NRF_SPIM2_NS_APP_BASE_REAL_HW           0x4000B000UL
#define NRF_SPIS2_NS_APP_BASE_REAL_HW           0x4000B000UL
#define NRF_TWIM2_NS_APP_BASE_REAL_HW           0x4000B000UL
#define NRF_TWIS2_NS_APP_BASE_REAL_HW           0x4000B000UL
#define NRF_UARTE2_NS_APP_BASE_REAL_HW          0x4000B000UL
#define NRF_SPIM2_S_APP_BASE_REAL_HW            0x5000B000UL
#define NRF_SPIS2_S_APP_BASE_REAL_HW            0x5000B000UL
#define NRF_TWIM2_S_APP_BASE_REAL_HW            0x5000B000UL
#define NRF_TWIS2_S_APP_BASE_REAL_HW            0x5000B000UL
#define NRF_UARTE2_S_APP_BASE_REAL_HW           0x5000B000UL
#define NRF_SPIM3_NS_APP_BASE_REAL_HW           0x4000C000UL
#define NRF_SPIS3_NS_APP_BASE_REAL_HW           0x4000C000UL
#define NRF_TWIM3_NS_APP_BASE_REAL_HW           0x4000C000UL
#define NRF_TWIS3_NS_APP_BASE_REAL_HW           0x4000C000UL
#define NRF_UARTE3_NS_APP_BASE_REAL_HW          0x4000C000UL
#define NRF_SPIM3_S_APP_BASE_REAL_HW            0x5000C000UL
#define NRF_SPIS3_S_APP_BASE_REAL_HW            0x5000C000UL
#define NRF_TWIM3_S_APP_BASE_REAL_HW            0x5000C000UL
#define NRF_TWIS3_S_APP_BASE_REAL_HW            0x5000C000UL
#define NRF_UARTE3_S_APP_BASE_REAL_HW           0x5000C000UL
#define NRF_GPIOTE0_S_APP_BASE_REAL_HW          0x5000D000UL
#define NRF_SAADC_NS_APP_BASE_REAL_HW           0x4000E000UL
#define NRF_SAADC_S_APP_BASE_REAL_HW            0x5000E000UL
#define NRF_TIMER0_NS_APP_BASE_REAL_HW          0x4000F000UL
#define NRF_TIMER0_S_APP_BASE_REAL_HW           0x5000F000UL
#define NRF_TIMER1_NS_APP_BASE_REAL_HW          0x40010000UL
#define NRF_TIMER1_S_APP_BASE_REAL_HW           0x50010000UL
#define NRF_TIMER2_NS_APP_BASE_REAL_HW          0x40011000UL
#define NRF_TIMER2_S_APP_BASE_REAL_HW           0x50011000UL
#define NRF_RTC0_NS_APP_BASE_REAL_HW            0x40014000UL
#define NRF_RTC0_S_APP_BASE_REAL_HW             0x50014000UL
#define NRF_RTC1_NS_APP_BASE_REAL_HW            0x40015000UL
#define NRF_RTC1_S_APP_BASE_REAL_HW             0x50015000UL
#define NRF_DPPIC_NS_APP_BASE_REAL_HW           0x40017000UL
#define NRF_DPPIC_S_APP_BASE_REAL_HW            0x50017000UL
#define NRF_WDT0_NS_APP_BASE_REAL_HW            0x40018000UL
#define NRF_WDT0_S_APP_BASE_REAL_HW             0x50018000UL
#define NRF_WDT1_NS_APP_BASE_REAL_HW            0x40019000UL
#define NRF_WDT1_S_APP_BASE_REAL_HW             0x50019000UL
#define NRF_COMP_NS_APP_BASE_REAL_HW            0x4001A000UL
#define NRF_LPCOMP_NS_APP_BASE_REAL_HW          0x4001A000UL
#define NRF_COMP_S_APP_BASE_REAL_HW             0x5001A000UL
#define NRF_LPCOMP_S_APP_BASE_REAL_HW           0x5001A000UL
#define NRF_EGU0_NS_APP_BASE_REAL_HW            0x4001B000UL
#define NRF_EGU0_S_APP_BASE_REAL_HW             0x5001B000UL
#define NRF_EGU1_NS_APP_BASE_REAL_HW            0x4001C000UL
#define NRF_EGU1_S_APP_BASE_REAL_HW             0x5001C000UL
#define NRF_EGU2_NS_APP_BASE_REAL_HW            0x4001D000UL
#define NRF_EGU2_S_APP_BASE_REAL_HW             0x5001D000UL
#define NRF_EGU3_NS_APP_BASE_REAL_HW            0x4001E000UL
#define NRF_EGU3_S_APP_BASE_REAL_HW             0x5001E000UL
#define NRF_EGU4_NS_APP_BASE_REAL_HW            0x4001F000UL
#define NRF_EGU4_S_APP_BASE_REAL_HW             0x5001F000UL
#define NRF_EGU5_NS_APP_BASE_REAL_HW            0x40020000UL
#define NRF_EGU5_S_APP_BASE_REAL_HW             0x50020000UL
#define NRF_PWM0_NS_APP_BASE_REAL_HW            0x40021000UL
#define NRF_PWM0_S_APP_BASE_REAL_HW             0x50021000UL
#define NRF_PWM1_NS_APP_BASE_REAL_HW            0x40022000UL
#define NRF_PWM1_S_APP_BASE_REAL_HW             0x50022000UL
#define NRF_PWM2_NS_APP_BASE_REAL_HW            0x40023000UL
#define NRF_PWM2_S_APP_BASE_REAL_HW             0x50023000UL
#define NRF_PWM3_NS_APP_BASE_REAL_HW            0x40024000UL
#define NRF_PWM3_S_APP_BASE_REAL_HW             0x50024000UL
#define NRF_PDM0_NS_APP_BASE_REAL_HW            0x40026000UL
#define NRF_PDM0_S_APP_BASE_REAL_HW             0x50026000UL
#define NRF_I2S0_NS_APP_BASE_REAL_HW            0x40028000UL
#define NRF_I2S0_S_APP_BASE_REAL_HW             0x50028000UL
#define NRF_IPC_NS_APP_BASE_REAL_HW             0x4002A000UL
#define NRF_IPC_S_APP_BASE_REAL_HW              0x5002A000UL
#define NRF_QSPI_NS_APP_BASE_REAL_HW            0x4002B000UL
#define NRF_QSPI_S_APP_BASE_REAL_HW             0x5002B000UL
#define NRF_NFCT_NS_APP_BASE_REAL_HW            0x4002D000UL
#define NRF_NFCT_S_APP_BASE_REAL_HW             0x5002D000UL
#define NRF_GPIOTE1_NS_APP_BASE_REAL_HW         0x4002F000UL
#define NRF_MUTEX_NS_APP_BASE_REAL_HW           0x40030000UL
#define NRF_MUTEX_S_APP_BASE_REAL_HW            0x50030000UL
#define NRF_QDEC0_NS_APP_BASE_REAL_HW           0x40033000UL
#define NRF_QDEC0_S_APP_BASE_REAL_HW            0x50033000UL
#define NRF_QDEC1_NS_APP_BASE_REAL_HW           0x40034000UL
#define NRF_QDEC1_S_APP_BASE_REAL_HW            0x50034000UL
#define NRF_USBD_NS_APP_BASE_REAL_HW            0x40036000UL
#define NRF_USBD_S_APP_BASE_REAL_HW             0x50036000UL
#define NRF_USBREGULATOR_NS_APP_BASE_REAL_HW    0x40037000UL
#define NRF_USBREGULATOR_S_APP_BASE_REAL_HW     0x50037000UL
#define NRF_KMU_NS_APP_BASE_REAL_HW             0x40039000UL
#define NRF_NVMC_NS_APP_BASE_REAL_HW            0x40039000UL
#define NRF_KMU_S_APP_BASE_REAL_HW              0x50039000UL
#define NRF_NVMC_S_APP_BASE_REAL_HW             0x50039000UL
#define NRF_P0_NS_APP_BASE_REAL_HW              0x40842500UL
#define NRF_P1_NS_APP_BASE_REAL_HW              0x40842800UL
#define NRF_P0_S_APP_BASE_REAL_HW               0x50842500UL
#define NRF_P1_S_APP_BASE_REAL_HW               0x50842800UL
#define NRF_CRYPTOCELL_S_APP_BASE_REAL_HW       0x50844000UL
#define NRF_CC_AES_S_APP_BASE_REAL_HW           0x50845000UL
#define NRF_CC_AHB_S_APP_BASE_REAL_HW           0x50845000UL
#define NRF_CC_AO_S_APP_BASE_REAL_HW            0x50845000UL
#define NRF_CC_CHACHA_S_APP_BASE_REAL_HW        0x50845000UL
#define NRF_CC_CTL_S_APP_BASE_REAL_HW           0x50845000UL
#define NRF_CC_DIN_S_APP_BASE_REAL_HW           0x50845000UL
#define NRF_CC_DOUT_S_APP_BASE_REAL_HW          0x50845000UL
#define NRF_CC_GHASH_S_APP_BASE_REAL_HW         0x50845000UL
#define NRF_CC_HASH_S_APP_BASE_REAL_HW          0x50845000UL
#define NRF_CC_HOST_RGF_S_APP_BASE_REAL_HW      0x50845000UL
#define NRF_CC_MISC_S_APP_BASE_REAL_HW          0x50845000UL
#define NRF_CC_PKA_S_APP_BASE_REAL_HW           0x50845000UL
#define NRF_CC_RNG_S_APP_BASE_REAL_HW           0x50845000UL
#define NRF_CC_RNG_SRAM_S_APP_BASE_REAL_HW      0x50845000UL
#define NRF_VMC_NS_APP_BASE_REAL_HW             0x40081000UL
#define NRF_VMC_S_APP_BASE_REAL_HW              0x50081000UL

#if defined(NRF5340_XXAA_NETWORK)

extern void *NRF_FICR_regs_p[];
#undef NRF_FICR_NS_BASE
#define NRF_FICR_NS_BASE           (NRF_FICR_regs_p[NHW_FICR_NET])
extern NRF_UICR_Type *NRF_UICR_regs_p[];
#undef NRF_UICR_NS_BASE
#define NRF_UICR_NS_BASE           (NRF_UICR_regs_p[NHW_UICR_NET0])
#undef NRF_CTI_NS_BASE
#define NRF_CTI_NS_BASE            NULL
#undef NRF_DCNF_NS_BASE
#define NRF_DCNF_NS_BASE           NULL
extern NRF_VREQCTRL_Type NRF_VREQCTRL_regs;
#undef NRF_VREQCTRL_NS_BASE
#define NRF_VREQCTRL_NS_BASE       (&NRF_VREQCTRL_regs)
extern NRF_CLOCK_Type *NRF_CLOCK_regs[];
#undef NRF_CLOCK_NS_BASE
#define NRF_CLOCK_NS_BASE          (NRF_CLOCK_regs[NHW_CLKPWR_NET0])
extern NRF_POWER_Type *NRF_POWER_regs[];
#undef NRF_POWER_NS_BASE
#define NRF_POWER_NS_BASE          (NRF_POWER_regs[NHW_CLKPWR_NET0])
extern NRF_RESET_Type *NRF_RESET_regs[];
#undef NRF_RESET_NS_BASE
#define NRF_RESET_NS_BASE          (NRF_RESET_regs[NHW_CLKPWR_NET0])
#undef NRF_CTRLAP_NS_BASE
#define NRF_CTRLAP_NS_BASE         NULL
extern NRF_RADIO_Type NRF_RADIO_regs;
#undef NRF_RADIO_NS_BASE
#define NRF_RADIO_NS_BASE          (&NRF_RADIO_regs)
extern NRF_RNG_Type NRF_RNG_regs;
#undef NRF_RNG_NS_BASE
#define NRF_RNG_NS_BASE            (&NRF_RNG_regs)
extern NRF_GPIOTE_Type NRF_GPIOTE_regs[];
#undef NRF_GPIOTE_NS_BASE
#define NRF_GPIOTE_NS_BASE         (&NRF_GPIOTE_regs[NHW_GPIOTE_NET])
#undef NRF_WDT_NS_BASE
#define NRF_WDT_NS_BASE            NULL
#undef NRF_ECB_NS_BASE
extern NRF_ECB_Type NRF_ECB_regs;
#define NRF_ECB_NS_BASE            (&NRF_ECB_regs)
extern NRF_AAR_Type NRF_AAR_regs;
#undef NRF_AAR_NS_BASE
#define NRF_AAR_NS_BASE            (&NRF_AAR_regs)
extern NRF_CCM_Type NRF_CCM_regs;
#undef NRF_CCM_NS_BASE
#define NRF_CCM_NS_BASE            (&NRF_CCM_regs)
extern NRF_DPPIC_Type NRF_DPPIC_regs[];
#undef NRF_DPPIC_NS_BASE
#define NRF_DPPIC_NS_BASE          (&NRF_DPPIC_regs[NHW_DPPI_NET_0])
extern NRF_TEMP_Type NRF_TEMP_regs;
#undef NRF_TEMP_NS_BASE
#define NRF_TEMP_NS_BASE           (&NRF_TEMP_regs)
extern NRF_RTC_Type NRF_RTC_regs[];
#undef NRF_RTC0_NS_BASE
#define NRF_RTC0_NS_BASE           (&NRF_RTC_regs[NHW_RTC_NET0])
#undef NRF_RTC1_NS_BASE
#define NRF_RTC1_NS_BASE           (&NRF_RTC_regs[NHW_RTC_NET1])
extern NRF_IPC_Type NRF_IPC_regs[NHW_IPC_TOTAL_INST];
#undef NRF_IPC_NS_BASE
#define NRF_IPC_NS_BASE            (&NRF_IPC_regs[NHW_IPC_NET0])
#undef NRF_SPIM0_NS_BASE
#define NRF_SPIM0_NS_BASE          NULL
#undef NRF_SPIS0_NS_BASE
#define NRF_SPIS0_NS_BASE          NULL
#undef NRF_TWIM0_NS_BASE
#define NRF_TWIM0_NS_BASE          NULL
#undef NRF_TWIS0_NS_BASE
#define NRF_TWIS0_NS_BASE          NULL
extern NRF_UARTE_Type NRF_UARTE_regs[];
#undef NRF_UARTE0_NS_BASE
#define NRF_UARTE0_NS_BASE         (&NRF_UARTE_regs[NHW_UARTE_NET0])
extern NRF_EGU_Type NRF_EGU_regs[];
#undef NRF_EGU0_NS_BASE
#define NRF_EGU0_NS_BASE           (&NRF_EGU_regs[NHW_EGU_NET0])
extern NRF_TIMER_Type NRF_TIMER_regs[];
#undef NRF_TIMER0_NS_BASE
#define NRF_TIMER0_NS_BASE         (&NRF_TIMER_regs[NHW_TIMER_NET0])
#undef NRF_TIMER1_NS_BASE
#define NRF_TIMER1_NS_BASE         (&NRF_TIMER_regs[NHW_TIMER_NET1])
#undef NRF_TIMER2_NS_BASE
#define NRF_TIMER2_NS_BASE         (&NRF_TIMER_regs[NHW_TIMER_NET2])
extern int NRF_SWI_regs[];
#undef NRF_SWI0_NS_BASE
#define NRF_SWI0_NS_BASE           (&NRF_SWI_regs[NHW_SWI_NET0])
#undef NRF_SWI1_NS_BASE
#define NRF_SWI1_NS_BASE            (&NRF_SWI_regs[NHW_SWI_NET1])
#undef NRF_SWI2_NS_BASE
#define NRF_SWI2_NS_BASE            (&NRF_SWI_regs[NHW_SWI_NET2])
#undef NRF_SWI3_NS_BASE
#define NRF_SWI3_NS_BASE            (&NRF_SWI_regs[NHW_SWI_NET3])
extern NRF_MUTEX_Type NRF_MUTEX_regs;
#undef NRF_APPMUTEX_NS_BASE
#define NRF_APPMUTEX_NS_BASE       (&NRF_MUTEX_regs)
#undef NRF_APPMUTEX_S_BASE
#define NRF_APPMUTEX_S_BASE        (&NRF_MUTEX_regs)
#undef NRF_ACL_NS_BASE
#define NRF_ACL_NS_BASE            NULL
extern NRF_NVMC_Type *NRF_NVMC_regs_p[];
#undef NRF_NVMC_NS_BASE
#define NRF_NVMC_NS_BASE           (NRF_NVMC_regs_p[NHW_NVMC_NET0])
#undef NRF_VMC_NS_BASE
#define NRF_VMC_NS_BASE            NULL
extern NRF_GPIO_Type NRF_GPIO_regs[];
#undef NRF_P0_NS_BASE
#define NRF_P0_NS_BASE             (&NRF_GPIO_regs[NHW_GPIO_NET_P0])
#undef NRF_P1_NS_BASE
#define NRF_P1_NS_BASE             (&NRF_GPIO_regs[NHW_GPIO_NET_P1])

/********************************************************************/
/********************************************************************/
/********************************************************************/
#elif defined(NRF5340_XXAA_APPLICATION)

#undef NRF_CACHEDATA_S_BASE
#define NRF_CACHEDATA_S_BASE        NULL
#undef NRF_CACHEINFO_S_BASE
#define NRF_CACHEINFO_S_BASE        NULL
extern void *NRF_FICR_regs_p[];
#undef NRF_FICR_S_BASE
#define NRF_FICR_S_BASE             (NRF_FICR_regs_p[NHW_FICR_APP])
extern NRF_UICR_Type *NRF_UICR_regs_p[];
#undef NRF_UICR_S_BASE
#define NRF_UICR_S_BASE             (NRF_UICR_regs_p[NHW_UICR_APP0])
#undef NRF_CTI_S_BASE
#define NRF_CTI_S_BASE              NULL
#undef NRF_TAD_S_BASE
#define NRF_TAD_S_BASE              NULL
#undef NRF_DCNF_NS_BASE
#define NRF_DCNF_NS_BASE            NULL
#undef NRF_FPU_NS_BASE
#define NRF_FPU_NS_BASE             NULL
#undef NRF_DCNF_S_BASE
#define NRF_DCNF_S_BASE             NULL
#undef NRF_FPU_S_BASE
#define NRF_FPU_S_BASE              NULL
#undef NRF_CACHE_S_BASE
#define NRF_CACHE_S_BASE            NULL
extern NRF_SPU_Type NRF_SPU_regs[];
#undef NRF_SPU_S_BASE
#define NRF_SPU_S_BASE              (&NRF_SPU_regs[NHW_SPU_APP0])
extern NRF_OSCILLATORS_Type NRF_OSCILLATORS_regs;
#undef NRF_OSCILLATORS_NS_BASE
#define NRF_OSCILLATORS_NS_BASE     (&NRF_OSCILLATORS_regs)
#undef NRF_REGULATORS_NS_BASE
#define NRF_REGULATORS_NS_BASE      NULL
#undef NRF_OSCILLATORS_S_BASE
#define NRF_OSCILLATORS_S_BASE      (&NRF_OSCILLATORS_regs)
#undef NRF_REGULATORS_S_BASE
#define NRF_REGULATORS_S_BASE       NULL
extern NRF_CLOCK_Type *NRF_CLOCK_regs[];
#undef NRF_CLOCK_NS_BASE
#define NRF_CLOCK_NS_BASE          (NRF_CLOCK_regs[NHW_CLKPWR_APP0])
extern NRF_POWER_Type *NRF_POWER_regs[];
#undef NRF_POWER_NS_BASE
#define NRF_POWER_NS_BASE          (NRF_POWER_regs[NHW_CLKPWR_APP0])
extern NRF_RESET_Type *NRF_RESET_regs[];
#undef NRF_RESET_NS_BASE
#define NRF_RESET_NS_BASE          (NRF_RESET_regs[NHW_CLKPWR_APP0])
#undef NRF_CLOCK_S_BASE
#define NRF_CLOCK_S_BASE           (NRF_CLOCK_regs[NHW_CLKPWR_APP0])
#undef NRF_POWER_S_BASE
#define NRF_POWER_S_BASE           (NRF_POWER_regs[NHW_CLKPWR_APP0])
#undef NRF_RESET_S_BASE
#define NRF_RESET_S_BASE           (NRF_RESET_regs[NHW_CLKPWR_APP0])
#undef NRF_CTRLAP_NS_BASE
#define NRF_CTRLAP_NS_BASE          NULL
#undef NRF_CTRLAP_S_BASE
#define NRF_CTRLAP_S_BASE           NULL
#undef NRF_SPIM0_NS_BASE
#define NRF_SPIM0_NS_BASE           NULL
#undef NRF_SPIS0_NS_BASE
#define NRF_SPIS0_NS_BASE           NULL
#undef NRF_TWIM0_NS_BASE
#define NRF_TWIM0_NS_BASE           NULL
#undef NRF_TWIS0_NS_BASE
#define NRF_TWIS0_NS_BASE           NULL
extern NRF_UARTE_Type NRF_UARTE_regs[];
#undef NRF_UARTE0_NS_BASE
#define NRF_UARTE0_NS_BASE          (&NRF_UARTE_regs[NHW_UARTE_APP0])
#undef NRF_SPIM0_S_BASE
#define NRF_SPIM0_S_BASE            NULL
#undef NRF_SPIS0_S_BASE
#define NRF_SPIS0_S_BASE            NULL
#undef NRF_TWIM0_S_BASE
#define NRF_TWIM0_S_BASE            NULL
#undef NRF_TWIS0_S_BASE
#define NRF_TWIS0_S_BASE            NULL
#undef NRF_UARTE0_S_BASE
#define NRF_UARTE0_S_BASE          (&NRF_UARTE_regs[NHW_UARTE_APP0])
#undef NRF_SPIM1_NS_BASE
#define NRF_SPIM1_NS_BASE           NULL
#undef NRF_SPIS1_NS_BASE
#define NRF_SPIS1_NS_BASE           NULL
#undef NRF_TWIM1_NS_BASE
#define NRF_TWIM1_NS_BASE           NULL
#undef NRF_TWIS1_NS_BASE
#define NRF_TWIS1_NS_BASE           NULL
#undef NRF_UARTE1_NS_BASE
#define NRF_UARTE1_NS_BASE          (&NRF_UARTE_regs[NHW_UARTE_APP1])
#undef NRF_SPIM1_S_BASE
#define NRF_SPIM1_S_BASE            NULL
#undef NRF_SPIS1_S_BASE
#define NRF_SPIS1_S_BASE            NULL
#undef NRF_TWIM1_S_BASE
#define NRF_TWIM1_S_BASE            NULL
#undef NRF_TWIS1_S_BASE
#define NRF_TWIS1_S_BASE            NULL
#undef NRF_UARTE1_S_BASE
#define NRF_UARTE1_S_BASE           (&NRF_UARTE_regs[NHW_UARTE_APP1])
#undef NRF_SPIM4_NS_BASE
#define NRF_SPIM4_NS_BASE           NULL
#undef NRF_SPIM4_S_BASE
#define NRF_SPIM4_S_BASE            NULL
#undef NRF_SPIM2_NS_BASE
#define NRF_SPIM2_NS_BASE           NULL
#undef NRF_SPIS2_NS_BASE
#define NRF_SPIS2_NS_BASE           NULL
#undef NRF_TWIM2_NS_BASE
#define NRF_TWIM2_NS_BASE           NULL
#undef NRF_TWIS2_NS_BASE
#define NRF_TWIS2_NS_BASE           NULL
#undef NRF_UARTE2_NS_BASE
#define NRF_UARTE2_NS_BASE          (&NRF_UARTE_regs[NHW_UARTE_APP2])
#undef NRF_SPIM2_S_BASE
#define NRF_SPIM2_S_BASE            NULL
#undef NRF_SPIS2_S_BASE
#define NRF_SPIS2_S_BASE            NULL
#undef NRF_TWIM2_S_BASE
#define NRF_TWIM2_S_BASE            NULL
#undef NRF_TWIS2_S_BASE
#define NRF_TWIS2_S_BASE            NULL
#undef NRF_UARTE2_S_BASE
#define NRF_UARTE2_S_BASE           (&NRF_UARTE_regs[NHW_UARTE_APP2])
#undef NRF_SPIM3_NS_BASE
#define NRF_SPIM3_NS_BASE           NULL
#undef NRF_SPIS3_NS_BASE
#define NRF_SPIS3_NS_BASE           NULL
#undef NRF_TWIM3_NS_BASE
#define NRF_TWIM3_NS_BASE           NULL
#undef NRF_TWIS3_NS_BASE
#define NRF_TWIS3_NS_BASE           NULL
#undef NRF_UARTE3_NS_BASE
#define NRF_UARTE3_NS_BASE          (&NRF_UARTE_regs[NHW_UARTE_APP3])
#undef NRF_SPIM3_S_BASE
#define NRF_SPIM3_S_BASE            NULL
#undef NRF_SPIS3_S_BASE
#define NRF_SPIS3_S_BASE            NULL
#undef NRF_TWIM3_S_BASE
#define NRF_TWIM3_S_BASE            NULL
#undef NRF_TWIS3_S_BASE
#define NRF_TWIS3_S_BASE            NULL
#undef NRF_UARTE3_S_BASE
#define NRF_UARTE3_S_BASE           (&NRF_UARTE_regs[NHW_UARTE_APP3])
extern NRF_GPIOTE_Type NRF_GPIOTE_regs[];
#undef NRF_GPIOTE0_S_BASE
#define NRF_GPIOTE0_S_BASE          (&NRF_GPIOTE_regs[NHW_GPIOTE_APP0])
#undef NRF_SAADC_NS_BASE
#define NRF_SAADC_NS_BASE           NULL
#undef NRF_SAADC_S_BASE
#define NRF_SAADC_S_BASE            NULL
extern NRF_TIMER_Type NRF_TIMER_regs[];
#undef NRF_TIMER0_NS_BASE
#define NRF_TIMER0_NS_BASE          (&NRF_TIMER_regs[NHW_TIMER_APP0])
#undef NRF_TIMER0_S_BASE
#define NRF_TIMER0_S_BASE           (&NRF_TIMER_regs[NHW_TIMER_APP0])
#undef NRF_TIMER1_NS_BASE
#define NRF_TIMER1_NS_BASE          (&NRF_TIMER_regs[NHW_TIMER_APP1])
#undef NRF_TIMER1_S_BASE
#define NRF_TIMER1_S_BASE           (&NRF_TIMER_regs[NHW_TIMER_APP1])
#undef NRF_TIMER2_NS_BASE
#define NRF_TIMER2_NS_BASE          (&NRF_TIMER_regs[NHW_TIMER_APP2])
#undef NRF_TIMER2_S_BASE
#define NRF_TIMER2_S_BASE           (&NRF_TIMER_regs[NHW_TIMER_APP2])
extern NRF_RTC_Type NRF_RTC_regs[];
#undef NRF_RTC0_NS_BASE
#define NRF_RTC0_NS_BASE            (&NRF_RTC_regs[NHW_RTC_APP0])
#undef NRF_RTC0_S_BASE
#define NRF_RTC0_S_BASE             (&NRF_RTC_regs[NHW_RTC_APP0])
#undef NRF_RTC1_NS_BASE
#define NRF_RTC1_NS_BASE            (&NRF_RTC_regs[NHW_RTC_APP1])
#undef NRF_RTC1_S_BASE
#define NRF_RTC1_S_BASE             (&NRF_RTC_regs[NHW_RTC_APP1])
extern NRF_DPPIC_Type NRF_DPPIC_regs[];
#undef NRF_DPPIC_NS_BASE
#define NRF_DPPIC_NS_BASE           (&NRF_DPPIC_regs[NHW_DPPI_APP_0])
#undef NRF_DPPIC_S_BASE
#define NRF_DPPIC_S_BASE            (&NRF_DPPIC_regs[NHW_DPPI_APP_0])
#undef NRF_WDT0_NS_BASE
#define NRF_WDT0_NS_BASE            NULL
#undef NRF_WDT0_S_BASE
#define NRF_WDT0_S_BASE             NULL
#undef NRF_WDT1_NS_BASE
#define NRF_WDT1_NS_BASE            NULL
#undef NRF_WDT1_S_BASE
#define NRF_WDT1_S_BASE             NULL
#undef NRF_COMP_NS_BASE
#define NRF_COMP_NS_BASE            NULL
#undef NRF_LPCOMP_NS_BASE
#define NRF_LPCOMP_NS_BASE          NULL
#undef NRF_COMP_S_BASE
#define NRF_COMP_S_BASE             NULL
#undef NRF_LPCOMP_S_BASE
#define NRF_LPCOMP_S_BASE           NULL
extern NRF_EGU_Type NRF_EGU_regs[];
#undef NRF_EGU0_NS_BASE
#define NRF_EGU0_NS_BASE           (&NRF_EGU_regs[NHW_EGU_APP0])
#undef NRF_EGU0_S_BASE
#define NRF_EGU0_S_BASE            (&NRF_EGU_regs[NHW_EGU_APP0])
#undef NRF_EGU1_NS_BASE
#define NRF_EGU1_NS_BASE           (&NRF_EGU_regs[NHW_EGU_APP1])
#undef NRF_EGU1_S_BASE
#define NRF_EGU1_S_BASE            (&NRF_EGU_regs[NHW_EGU_APP1])
#undef NRF_EGU2_NS_BASE
#define NRF_EGU2_NS_BASE           (&NRF_EGU_regs[NHW_EGU_APP2])
#undef NRF_EGU2_S_BASE
#define NRF_EGU2_S_BASE            (&NRF_EGU_regs[NHW_EGU_APP2])
#undef NRF_EGU3_NS_BASE
#define NRF_EGU3_NS_BASE           (&NRF_EGU_regs[NHW_EGU_APP3])
#undef NRF_EGU3_S_BASE
#define NRF_EGU3_S_BASE            (&NRF_EGU_regs[NHW_EGU_APP3])
#undef NRF_EGU4_NS_BASE
#define NRF_EGU4_NS_BASE           (&NRF_EGU_regs[NHW_EGU_APP4])
#undef NRF_EGU4_S_BASE
#define NRF_EGU4_S_BASE            (&NRF_EGU_regs[NHW_EGU_APP4])
#undef NRF_EGU5_NS_BASE
#define NRF_EGU5_NS_BASE           (&NRF_EGU_regs[NHW_EGU_APP5])
#undef NRF_EGU5_S_BASE
#define NRF_EGU5_S_BASE            (&NRF_EGU_regs[NHW_EGU_APP5])
#undef NRF_PWM0_NS_BASE
#define NRF_PWM0_NS_BASE            NULL
#undef NRF_PWM0_S_BASE
#define NRF_PWM0_S_BASE             NULL
#undef NRF_PWM1_NS_BASE
#define NRF_PWM1_NS_BASE            NULL
#undef NRF_PWM1_S_BASE
#define NRF_PWM1_S_BASE             NULL
#undef NRF_PWM2_NS_BASE
#define NRF_PWM2_NS_BASE            NULL
#undef NRF_PWM2_S_BASE
#define NRF_PWM2_S_BASE             NULL
#undef NRF_PWM3_NS_BASE
#define NRF_PWM3_NS_BASE            NULL
#undef NRF_PWM3_S_BASE
#define NRF_PWM3_S_BASE             NULL
#undef NRF_PDM0_NS_BASE
#define NRF_PDM0_NS_BASE            NULL
#undef NRF_PDM0_S_BASE
#define NRF_PDM0_S_BASE             NULL
#undef NRF_I2S0_NS_BASE
#define NRF_I2S0_NS_BASE            NULL
#undef NRF_I2S0_S_BASE
#define NRF_I2S0_S_BASE             NULL
extern NRF_IPC_Type NRF_IPC_regs[NHW_IPC_TOTAL_INST];
#undef NRF_IPC_NS_BASE
#define NRF_IPC_NS_BASE             (&NRF_IPC_regs[NHW_IPC_APP0])
#undef NRF_IPC_S_BASE
#define NRF_IPC_S_BASE              (&NRF_IPC_regs[NHW_IPC_APP0])
#undef NRF_QSPI_NS_BASE
#define NRF_QSPI_NS_BASE            NULL
#undef NRF_QSPI_S_BASE
#define NRF_QSPI_S_BASE             NULL
extern NRF_NFCT_Type NRF_NFCT_regs;
#undef NRF_NFCT_NS_BASE
#define NRF_NFCT_NS_BASE            (&NRF_NFCT_regs)
#undef NRF_NFCT_S_BASE
#define NRF_NFCT_S_BASE             (&NRF_NFCT_regs)
#undef NRF_GPIOTE1_NS_BASE
#define NRF_GPIOTE1_NS_BASE         (&NRF_GPIOTE_regs[NHW_GPIOTE_APP1])
extern NRF_MUTEX_Type NRF_MUTEX_regs;
#undef NRF_MUTEX_NS_BASE
#define NRF_MUTEX_NS_BASE           (&NRF_MUTEX_regs)
#undef NRF_MUTEX_S_BASE
#define NRF_MUTEX_S_BASE            (&NRF_MUTEX_regs)
#undef NRF_QDEC0_NS_BASE
#define NRF_QDEC0_NS_BASE           NULL
#undef NRF_QDEC0_S_BASE
#define NRF_QDEC0_S_BASE            NULL
#undef NRF_QDEC1_NS_BASE
#define NRF_QDEC1_NS_BASE           NULL
#undef NRF_QDEC1_S_BASE
#define NRF_QDEC1_S_BASE            NULL
#undef NRF_USBD_NS_BASE
#define NRF_USBD_NS_BASE            NULL
#undef NRF_USBD_S_BASE
#define NRF_USBD_S_BASE             NULL
#undef NRF_USBREGULATOR_NS_BASE
#define NRF_USBREGULATOR_NS_BASE    NULL
#undef NRF_USBREGULATOR_S_BASE
#define NRF_USBREGULATOR_S_BASE     NULL
#undef NRF_KMU_NS_BASE
#define NRF_KMU_NS_BASE             NULL
extern NRF_NVMC_Type *NRF_NVMC_regs_p[];
#undef NRF_NVMC_NS_BASE
#define NRF_NVMC_NS_BASE            (NRF_NVMC_regs_p[NHW_NVMC_APP0])
#undef NRF_KMU_S_BASE
#define NRF_KMU_S_BASE              NULL
#undef NRF_NVMC_S_BASE
#define NRF_NVMC_S_BASE             (NRF_NVMC_regs_p[NHW_NVMC_APP0])
extern NRF_GPIO_Type NRF_GPIO_regs[];
#undef NRF_P0_NS_BASE
#define NRF_P0_NS_BASE              (&NRF_GPIO_regs[NHW_GPIO_APP_P0])
#undef NRF_P1_NS_BASE
#define NRF_P1_NS_BASE              (&NRF_GPIO_regs[NHW_GPIO_APP_P1])
#undef NRF_P0_S_BASE
#define NRF_P0_S_BASE               (&NRF_GPIO_regs[NHW_GPIO_APP_P0])
#undef NRF_P1_S_BASE
#define NRF_P1_S_BASE               (&NRF_GPIO_regs[NHW_GPIO_APP_P1])
#undef NRF_CRYPTOCELL_S_BASE
#define NRF_CRYPTOCELL_S_BASE       NULL
#undef NRF_VMC_NS_BASE
#define NRF_VMC_NS_BASE             NULL
#undef NRF_VMC_S_BASE
#define NRF_VMC_S_BASE              NULL

#endif //defined(NRF5340_XXAA_NETWORK) || defined(NRF5340_XXAA_APPLICATION)
