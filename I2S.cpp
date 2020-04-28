/* mbed Microcontroller Library
 * Copyright (c) 2017 Nuvoton
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"

#include "PeripheralNames.h"
#include "pinmap.h"
#include "nu_modutil.h"

#include "I2S.h"

#if defined(TARGET_NUMAKER_PFM_NANO130)
typedef void(*pfn_i2s_callback)(void);
static pfn_i2s_callback s_i2s_callback;

extern "C" void I2S_IRQHandler(void)
{
    s_i2s_callback();
}
#endif

static void donothing() {}

#if defined(TARGET_NUMAKER_PFM_NANO130)
/* defined in PeripheralNames.h */
#else
typedef enum {
    #if defined(TARGET_NUMAKER_PFM_NUC472)
    I2S_0 = (int) NU_MODNAME(I2S0_BASE, 0, 0),
    I2S_1 = (int) NU_MODNAME(I2S1_BASE, 1, 0)
    #elif defined(TARGET_NUMAKER_PFM_M453)
    I2S_0 = (int) NU_MODNAME(SPI1_BASE, 0, 0),
    I2S_1 = (int) NU_MODNAME(SPI2_BASE, 1, 0)
    #elif defined(TARGET_NUMAKER_PFM_M487)
    I2S_0 = (int) NU_MODNAME(I2S_BASE,  0, 0)
    /* TODO SPI for I2S */
    #elif defined(TARGET_NUMAKER_IOT_M487)
    I2S_0 = (int) NU_MODNAME(I2S_BASE,  0, 0)
    /* TODO SPI for I2S */
    #endif
} I2SName;
#endif

const PinMap PinMap_I2S_DO[] = {
    #if defined(TARGET_NUMAKER_PFM_NUC472)
    {PA_3,  I2S_0, SYS_GPA_MFPL_PA3MFP_I2S0_DO},
    {PB_15, I2S_1, SYS_GPB_MFPH_PB15MFP_I2S1_DO},
    {PC_4,  I2S_1, SYS_GPC_MFPL_PC4MFP_I2S1_DO},
    {PG_3,  I2S_1, SYS_GPG_MFPL_PG3MFP_I2S1_DO},
    {PG_8,  I2S_1, SYS_GPG_MFPH_PG8MFP_I2S1_DO},
    #elif defined(TARGET_NUMAKER_PFM_M453)
    {PA_5,  I2S_0, SYS_GPA_MFPL_PA5MFP_SPI1_MOSI},
    {PB_5,  I2S_0, SYS_GPB_MFPL_PB5MFP_SPI1_MOSI},
    {PE_3,  I2S_0, SYS_GPE_MFPL_PE3MFP_SPI1_MOSI},
    {PE_11, I2S_0, SYS_GPE_MFPH_PE11MFP_SPI1_MOSI},
    {PC_3,  I2S_1, SYS_GPC_MFPL_PC3MFP_SPI2_MOSI},
    {PC_10, I2S_1, SYS_GPC_MFPH_PC10MFP_SPI2_MOSI},
    {PD_13, I2S_1, SYS_GPD_MFPH_PD13MFP_SPI2_MOSI},
    #elif defined(TARGET_NUMAKER_PFM_M487)
    {PA_15, I2S_0, SYS_GPA_MFPH_PA15MFP_I2S0_DO},
    {PB_2,  I2S_0, SYS_GPB_MFPL_PB2MFP_I2S0_DO},
    {PC_1,  I2S_0, SYS_GPC_MFPL_PC1MFP_I2S0_DO},
    {PE_11, I2S_0, SYS_GPE_MFPH_PE11MFP_I2S0_DO},
    {PF_7,  I2S_0, SYS_GPF_MFPL_PF7MFP_I2S0_DO},
    {PH_9,  I2S_0, SYS_GPH_MFPH_PH9MFP_I2S0_DO},
    /* TODO SPI for I2S */
    #elif defined(TARGET_NUMAKER_PFM_NANO130)
    {PC_3,  I2S_0, SYS_PC_L_MFP_PC3_MFP_I2S_DOUT},
    {PD_5,  I2S_0, SYS_PD_L_MFP_PD5_MFP_I2S_DOUT},
    #elif defined(TARGET_NUMAKER_IOT_M487)
    {PA_15, I2S_0, SYS_GPA_MFPH_PA15MFP_I2S0_DO},
    {PB_2,  I2S_0, SYS_GPB_MFPL_PB2MFP_I2S0_DO},
    {PC_1,  I2S_0, SYS_GPC_MFPL_PC1MFP_I2S0_DO},
    {PE_11, I2S_0, SYS_GPE_MFPH_PE11MFP_I2S0_DO},
    {PF_7,  I2S_0, SYS_GPF_MFPL_PF7MFP_I2S0_DO},
    {PH_9,  I2S_0, SYS_GPH_MFPH_PH9MFP_I2S0_DO},
    /* TODO SPI for I2S */
    #endif
    {NC,    NC,    0}
};

const PinMap PinMap_I2S_DI[] = {
    #if defined(TARGET_NUMAKER_PFM_NUC472)
    {PA_4,  I2S_0, SYS_GPA_MFPL_PA4MFP_I2S0_DI},
    {PC_0,  I2S_1, SYS_GPC_MFPL_PC0MFP_I2S1_DI},
    {PG_4,  I2S_1, SYS_GPG_MFPL_PG4MFP_I2S1_DI},
    {PG_9,  I2S_1, SYS_GPG_MFPH_PG9MFP_I2S1_DI},
    #elif defined(TARGET_NUMAKER_PFM_M453)
    {PA_6,  I2S_0, SYS_GPA_MFPL_PA6MFP_SPI1_MISO},
    {PB_3,  I2S_0, SYS_GPB_MFPL_PB3MFP_SPI1_MISO},
    {PB_6,  I2S_0, SYS_GPB_MFPL_PB6MFP_SPI1_MISO},
    {PD_5,  I2S_0, SYS_GPD_MFPL_PD5MFP_SPI1_MISO},
    {PE_10, I2S_0, SYS_GPE_MFPH_PE10MFP_SPI1_MISO},
    {PC_4,  I2S_1, SYS_GPC_MFPL_PC4MFP_SPI2_MISO},
    {PC_11, I2S_1, SYS_GPC_MFPH_PC11MFP_SPI2_MISO},
    {PD_14, I2S_1, SYS_GPD_MFPH_PD14MFP_SPI2_MISO},
    #elif defined(TARGET_NUMAKER_PFM_M487)
    {PA_14, I2S_0, SYS_GPA_MFPH_PA14MFP_I2S0_DI},
    {PB_3,  I2S_0, SYS_GPB_MFPL_PB3MFP_I2S0_DI},
    {PC_2,  I2S_0, SYS_GPC_MFPL_PC2MFP_I2S0_DI},
    {PE_10, I2S_0, SYS_GPE_MFPH_PE10MFP_I2S0_DI},
    {PF_8,  I2S_0, SYS_GPF_MFPH_PF8MFP_I2S0_DI},
    {PH_8,  I2S_0, SYS_GPH_MFPH_PH8MFP_I2S0_DI},
    /* TODO SPI for I2S */
    #elif defined(TARGET_NUMAKER_PFM_NANO130)
    {PC_2,  I2S_0, SYS_PC_L_MFP_PC2_MFP_I2S_DIN},
    {PD_4,  I2S_0, SYS_PD_L_MFP_PD4_MFP_I2S_DIN},
    #elif defined(TARGET_NUMAKER_IOT_M487)
    {PA_14, I2S_0, SYS_GPA_MFPH_PA14MFP_I2S0_DI},
    {PB_3,  I2S_0, SYS_GPB_MFPL_PB3MFP_I2S0_DI},
    {PC_2,  I2S_0, SYS_GPC_MFPL_PC2MFP_I2S0_DI},
    {PE_10, I2S_0, SYS_GPE_MFPH_PE10MFP_I2S0_DI},
    {PF_8,  I2S_0, SYS_GPF_MFPH_PF8MFP_I2S0_DI},
    {PH_8,  I2S_0, SYS_GPH_MFPH_PH8MFP_I2S0_DI},
    /* TODO SPI for I2S */
    #endif
    {NC,    NC,    0}
};

const PinMap PinMap_I2S_BCLK[] = {
    #if defined(TARGET_NUMAKER_PFM_NUC472)
    {PA_5,  I2S_0, SYS_GPA_MFPL_PA5MFP_I2S0_BCLK},
    {PC_1,  I2S_1, SYS_GPC_MFPL_PC1MFP_I2S1_BCLK},
    {PG_5,  I2S_1, SYS_GPG_MFPL_PG5MFP_I2S1_BCLK},
    {PI_11, I2S_1, SYS_GPI_MFPH_PI11MFP_I2S1_BCLK},
    #elif defined(TARGET_NUMAKER_PFM_M453)
    {PA_7,  I2S_0, SYS_GPA_MFPL_PA7MFP_SPI1_CLK},
    {PB_2,  I2S_0, SYS_GPB_MFPL_PB2MFP_SPI1_CLK},
    {PB_7,  I2S_0, SYS_GPB_MFPL_PB7MFP_SPI1_CLK},
    {PD_4,  I2S_0, SYS_GPD_MFPL_PD4MFP_SPI1_CLK},
    {PE_13, I2S_0, SYS_GPE_MFPH_PE13MFP_SPI1_CLK},
    {PC_0,  I2S_1, SYS_GPC_MFPL_PC0MFP_SPI2_CLK},
    {PC_12, I2S_1, SYS_GPC_MFPH_PC12MFP_SPI2_CLK},
    {PD_15, I2S_1, SYS_GPD_MFPH_PD15MFP_SPI2_CLK},
    {PE_0,  I2S_1, SYS_GPE_MFPL_PE0MFP_SPI2_CLK},
    #elif defined(TARGET_NUMAKER_PFM_M487)
    {PA_12, I2S_0, SYS_GPA_MFPH_PA12MFP_I2S0_BCLK},
    {PB_5,  I2S_0, SYS_GPB_MFPL_PB5MFP_I2S0_BCLK},
    {PC_4,  I2S_0, SYS_GPC_MFPL_PC4MFP_I2S0_BCLK},
    {PE_1,  I2S_0, SYS_GPE_MFPL_PE1MFP_I2S0_BCLK},
    {PE_8,  I2S_0, SYS_GPE_MFPH_PE8MFP_I2S0_BCLK},
    {PF_10, I2S_0, SYS_GPF_MFPH_PF10MFP_I2S0_BCLK},
    /* TODO SPI for I2S */
    #elif defined(TARGET_NUMAKER_PFM_NANO130)
    {PC_1,  I2S_0, SYS_PC_L_MFP_PC1_MFP_I2S_BCLK},
    {PD_3,  I2S_0, SYS_PD_L_MFP_PD3_MFP_I2S_BCLK},
    #elif defined(TARGET_NUMAKER_IOT_M487)
    {PA_12, I2S_0, SYS_GPA_MFPH_PA12MFP_I2S0_BCLK},
    {PB_5,  I2S_0, SYS_GPB_MFPL_PB5MFP_I2S0_BCLK},
    {PC_4,  I2S_0, SYS_GPC_MFPL_PC4MFP_I2S0_BCLK},
    {PE_1,  I2S_0, SYS_GPE_MFPL_PE1MFP_I2S0_BCLK},
    {PE_8,  I2S_0, SYS_GPE_MFPH_PE8MFP_I2S0_BCLK},
    {PF_10, I2S_0, SYS_GPF_MFPH_PF10MFP_I2S0_BCLK},
    /* TODO SPI for I2S */
    #endif
    {NC,    NC,    0}
};

const PinMap PinMap_I2S_MCLK[] = {
    #if defined(TARGET_NUMAKER_PFM_NUC472)
    {PA_2,  I2S_0, SYS_GPA_MFPL_PA2MFP_I2S0_MCLK},
    {PB_14, I2S_1, SYS_GPB_MFPH_PB14MFP_I2S1_MCLK},
    {PC_3,  I2S_1, SYS_GPC_MFPL_PC3MFP_I2S1_MCLK},
    {PG_7,  I2S_1, SYS_GPG_MFPL_PG7MFP_I2S1_MCLK},
    #elif defined(TARGET_NUMAKER_PFM_M453)
    {PA_0,  I2S_0, SYS_GPA_MFPL_PA0MFP_SPI1_I2SMCLK},
    {PA_12, I2S_0, SYS_GPA_MFPH_PA12MFP_SPI1_I2SMCLK},
    {PD_0,  I2S_0, SYS_GPD_MFPL_PD0MFP_SPI1_I2SMCLK},
    {PE_9,  I2S_0, SYS_GPE_MFPH_PE9MFP_SPI1_I2SMCLK},
    {PC_5,  I2S_1, SYS_GPC_MFPL_PC5MFP_SPI2_I2SMCLK},
    {PC_9,  I2S_1, SYS_GPC_MFPH_PC9MFP_SPI2_I2SMCLK},
    #elif defined(TARGET_NUMAKER_PFM_M487)
    {PA_13, I2S_0, SYS_GPA_MFPH_PA13MFP_I2S0_MCLK},
    {PB_4,  I2S_0, SYS_GPB_MFPL_PB4MFP_I2S0_MCLK},
    {PC_3,  I2S_0, SYS_GPC_MFPL_PC3MFP_I2S0_MCLK},
    {PE_0,  I2S_0, SYS_GPE_MFPL_PE0MFP_I2S0_MCLK},
    {PE_9,  I2S_0, SYS_GPE_MFPH_PE9MFP_I2S0_MCLK},
    {PF_9,  I2S_0, SYS_GPF_MFPH_PF9MFP_I2S0_MCLK},
    /* TODO SPI for I2S */
    #elif defined(TARGET_NUMAKER_PFM_NANO130)
    {PA_15, I2S_0, SYS_PA_H_MFP_PA15_MFP_I2S_MCLK},
    {PE_0,  I2S_0, SYS_PE_L_MFP_PE0_MFP_I2S_MCLK},
    #elif defined(TARGET_NUMAKER_IOT_M487)
    {PA_13, I2S_0, SYS_GPA_MFPH_PA13MFP_I2S0_MCLK},
    {PB_4,  I2S_0, SYS_GPB_MFPL_PB4MFP_I2S0_MCLK},
    {PC_3,  I2S_0, SYS_GPC_MFPL_PC3MFP_I2S0_MCLK},
    {PE_0,  I2S_0, SYS_GPE_MFPL_PE0MFP_I2S0_MCLK},
    {PE_9,  I2S_0, SYS_GPE_MFPH_PE9MFP_I2S0_MCLK},
    {PF_9,  I2S_0, SYS_GPF_MFPH_PF9MFP_I2S0_MCLK},
    /* TODO SPI for I2S */
    #endif
    {NC,    NC,    0}
};

const PinMap PinMap_I2S_LRCK[] = {
    #if defined(TARGET_NUMAKER_PFM_NUC472)
    {PA_6,  I2S_0, SYS_GPA_MFPL_PA6MFP_I2S0_LRCK},
    {PC_2,  I2S_1, SYS_GPC_MFPL_PC2MFP_I2S1_LRCK},
    {PG_6,  I2S_1, SYS_GPG_MFPL_PG6MFP_I2S1_LRCK},
    {PI_12, I2S_1, SYS_GPI_MFPH_PI12MFP_I2S1_LRCK},
    #elif defined(TARGET_NUMAKER_PFM_M453)
    {PA_4,  I2S_0, SYS_GPA_MFPL_PA4MFP_SPI1_SS},
    {PB_4,  I2S_0, SYS_GPB_MFPL_PB4MFP_SPI1_SS},
    {PD_6,  I2S_0, SYS_GPD_MFPL_PD6MFP_SPI1_SS},
    {PE_12, I2S_0, SYS_GPE_MFPH_PE12MFP_SPI1_SS},
    {PC_2,  I2S_1, SYS_GPC_MFPL_PC2MFP_SPI2_SS},
    {PC_13, I2S_1, SYS_GPC_MFPH_PC13MFP_SPI2_SS},
    {PD_12, I2S_1, SYS_GPD_MFPH_PD12MFP_SPI2_SS},
    #elif defined(TARGET_NUMAKER_PFM_M487)
    {PB_1,  I2S_0, SYS_GPB_MFPL_PB1MFP_I2S0_LRCK},
    {PC_0,  I2S_0, SYS_GPC_MFPL_PC0MFP_I2S0_LRCK},
    {PE_12, I2S_0, SYS_GPE_MFPH_PE12MFP_I2S0_LRCK},
    {PF_6,  I2S_0, SYS_GPF_MFPL_PF6MFP_I2S0_LRCK},
    {PH_10, I2S_0, SYS_GPH_MFPH_PH10MFP_I2S0_LRCK},
    /* TODO SPI for I2S */
    #elif defined(TARGET_NUMAKER_PFM_NANO130)
    {PC_0,  I2S_0, SYS_PC_L_MFP_PC0_MFP_I2S_WS},
    {PD_2,  I2S_0, SYS_PD_L_MFP_PD2_MFP_I2S_WS},
    #elif defined(TARGET_NUMAKER_IOT_M487)
    {PB_1,  I2S_0, SYS_GPB_MFPL_PB1MFP_I2S0_LRCK},
    {PC_0,  I2S_0, SYS_GPC_MFPL_PC0MFP_I2S0_LRCK},
    {PE_12, I2S_0, SYS_GPE_MFPH_PE12MFP_I2S0_LRCK},
    {PF_6,  I2S_0, SYS_GPF_MFPL_PF6MFP_I2S0_LRCK},
    {PH_10, I2S_0, SYS_GPH_MFPH_PH10MFP_I2S0_LRCK},
    /* TODO SPI for I2S */
    #endif
    {NC,    NC,    0}
};

static const struct nu_modinit_s i2s_modinit_tab[] = {
    #if defined(TARGET_NUMAKER_PFM_NUC472)
    {I2S_0, I2S0_MODULE, CLK_CLKSEL3_I2S0SEL_HXT, 0, I2S0_RST, I2S0_IRQn, NULL},
    {I2S_1, I2S1_MODULE, CLK_CLKSEL3_I2S1SEL_HXT, 0, I2S1_RST, I2S1_IRQn, NULL},
    #elif defined(TARGET_NUMAKER_PFM_M453)
    {I2S_0, SPI1_MODULE, CLK_CLKSEL2_SPI1SEL_HXT, 0, SPI1_RST, SPI1_IRQn, NULL},
    {I2S_1, SPI2_MODULE, CLK_CLKSEL2_SPI2SEL_HXT, 0, SPI2_RST, SPI2_IRQn, NULL},
    #elif defined(TARGET_NUMAKER_PFM_M487)
    {I2S_0, I2S0_MODULE, CLK_CLKSEL3_I2S0SEL_HXT, 0, I2S0_RST, I2S0_IRQn, NULL},
    /* TODO SPI for I2S */
    #elif defined(TARGET_NUMAKER_PFM_NANO130)
    {I2S_0, I2S_MODULE,  CLK_CLKSEL2_I2S_S_HXT,   0, I2S_RST,  I2S_IRQn,  NULL},
    #elif defined(TARGET_NUMAKER_IOT_M487)
    {I2S_0, I2S0_MODULE, CLK_CLKSEL3_I2S0SEL_HXT, 0, I2S0_RST, I2S0_IRQn, NULL},
    /* TODO SPI for I2S */
    #endif
    {NC, 0, 0, 0, 0, (IRQn_Type) 0, NULL}
};

NuI2SDevice::NuI2SDevice(PinName i2s_do, PinName i2s_di, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrck) :
            m_i2s_irq_thunk(this, &NuI2SDevice::m_i2s_irq) {
    m_masterMode = 0; // i2s as slave mode
    
    uint32_t i2s_do_mod   = pinmap_peripheral(i2s_do,   PinMap_I2S_DO);
    uint32_t i2s_di_mod   = pinmap_peripheral(i2s_di,   PinMap_I2S_DI);
    uint32_t i2s_bclk_mod = pinmap_peripheral(i2s_bclk, PinMap_I2S_BCLK);
    uint32_t i2s_mclk_mod = pinmap_peripheral(i2s_mclk, PinMap_I2S_MCLK);
    uint32_t i2s_lrck_mod = pinmap_peripheral(i2s_lrck, PinMap_I2S_LRCK);
    uint32_t i2s_dodi_mod         = pinmap_merge(i2s_do_mod,       i2s_di_mod);
    uint32_t i2s_bclkmclk_mod     = pinmap_merge(i2s_bclk_mod,     i2s_mclk_mod);
    uint32_t i2s_bclkmclklrck_mod = pinmap_merge(i2s_bclkmclk_mod, i2s_lrck_mod);
    uint32_t i2s_mod              = pinmap_merge(i2s_dodi_mod,     i2s_bclkmclklrck_mod);
    
    if (i2s_mod == (uint32_t) NC) {
        printf("I2S pinmap error\n");
    }
    
    _i2s_modinit = get_modinit(i2s_mod, i2s_modinit_tab);
    
    // Configure I2S multi-function pins
    pinmap_pinout(i2s_do,   PinMap_I2S_DO);
    pinmap_pinout(i2s_di,   PinMap_I2S_DI);
    pinmap_pinout(i2s_bclk, PinMap_I2S_BCLK);
    pinmap_pinout(i2s_mclk, PinMap_I2S_MCLK);
    pinmap_pinout(i2s_lrck, PinMap_I2S_LRCK);
    
    // Determine I2S base dependent on passed-in pins
    /* TODO M487 SPI for I2S */
    #if defined(TARGET_NUMAKER_PFM_NUC472) || defined(TARGET_NUMAKER_PFM_M487) || defined(TARGET_NUMAKER_PFM_NANO130) || defined(TARGET_NUMAKER_IOT_M487)
    _i2s_base = (I2S_T *) NU_MODBASE((I2SName) i2s_mod);
    #elif defined(TARGET_NUMAKER_PFM_M453)
    _i2s_base = (SPI_T *) NU_MODBASE((I2SName) i2s_mod);
    #endif
    
    /* Enable IP clock */
    CLK_EnableModuleClock(_i2s_modinit->clkidx);
    
    // select source from HXT(12MHz)
    CLK_SetModuleClock(_i2s_modinit->clkidx, _i2s_modinit->clksrc, _i2s_modinit->clkdiv);
    
    #if defined(TARGET_NUMAKER_PFM_NANO130)
    s_i2s_callback = (pfn_i2s_callback)m_i2s_irq_thunk.entry();
    #endif
}

NuI2SDevice::NuI2SDevice(PinName i2s_do, PinName i2s_di, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrck, char i2s_master_enable) :
            m_i2s_irq_thunk(this, &NuI2SDevice::m_i2s_irq) {
    /* FIXME */
    m_masterMode = i2s_master_enable;
    
    uint32_t i2s_do_mod   = pinmap_peripheral(i2s_do,   PinMap_I2S_DO);
    uint32_t i2s_di_mod   = pinmap_peripheral(i2s_di,   PinMap_I2S_DI);
    uint32_t i2s_bclk_mod = pinmap_peripheral(i2s_bclk, PinMap_I2S_BCLK);
    uint32_t i2s_mclk_mod = pinmap_peripheral(i2s_mclk, PinMap_I2S_MCLK);
    uint32_t i2s_lrck_mod = pinmap_peripheral(i2s_lrck, PinMap_I2S_LRCK);
    uint32_t i2s_dodi_mod         = pinmap_merge(i2s_do_mod,       i2s_di_mod);
    uint32_t i2s_bclkmclk_mod     = pinmap_merge(i2s_bclk_mod,     i2s_mclk_mod);
    uint32_t i2s_bclkmclklrck_mod = pinmap_merge(i2s_bclkmclk_mod, i2s_lrck_mod);
    uint32_t i2s_mod              = pinmap_merge(i2s_dodi_mod,     i2s_bclkmclklrck_mod);
    
    if (i2s_mod == (uint32_t) NC) {
        printf("I2S pinmap error\n");
    }
    
    _i2s_modinit = get_modinit(i2s_mod, i2s_modinit_tab);
    
    // Configure I2S multi-function pins
    pinmap_pinout(i2s_do,   PinMap_I2S_DO);
    pinmap_pinout(i2s_di,   PinMap_I2S_DI);
    pinmap_pinout(i2s_bclk, PinMap_I2S_BCLK);
    pinmap_pinout(i2s_mclk, PinMap_I2S_MCLK);
    pinmap_pinout(i2s_lrck, PinMap_I2S_LRCK);
    
    // Determine I2S base dependent on passed-in pins
    /* TODO M487 SPI for I2S */
    #if defined(TARGET_NUMAKER_PFM_NUC472) || defined(TARGET_NUMAKER_PFM_M487) || defined(TARGET_NUMAKER_PFM_NANO130) || defined(TARGET_NUMAKER_IOT_M487)
    _i2s_base = (I2S_T *) NU_MODBASE((I2SName) i2s_mod);
    #elif defined(TARGET_NUMAKER_PFM_M453)
    _i2s_base = (SPI_T *) NU_MODBASE((I2SName) i2s_mod);
    #endif
    
    /* Enable IP clock */
    CLK_EnableModuleClock(_i2s_modinit->clkidx);
    
    // select clock source
    CLK_SetModuleClock(_i2s_modinit->clkidx, _i2s_modinit->clksrc, _i2s_modinit->clkdiv);
    
    #if defined(TARGET_NUMAKER_PFM_NANO130)
    s_i2s_callback = (pfn_i2s_callback)m_i2s_irq_thunk.entry();
    #endif
}

void NuI2SDevice::start(void) {
    int channelCount;
    int sampleBitLength;
    int masterSlave;
    
    if (m_channelCount == 2) {
        #if defined(TARGET_NUMAKER_PFM_M487)
        channelCount = I2S_DISABLE_MONO;
        #elif defined(TARGET_NUMAKER_IOT_M487)
        channelCount = I2S_DISABLE_MONO;
        #else
        channelCount = I2S_STEREO;
        #endif
    } else {
        #if defined(TARGET_NUMAKER_PFM_M487)
        channelCount = I2S_ENABLE_MONO;
        #elif defined(TARGET_NUMAKER_IOT_M487)
        channelCount = I2S_ENABLE_MONO;
        #else
        channelCount = I2S_MONO;
        #endif
    }
    
    if (m_sampleBitLength == 16) {
        sampleBitLength = I2S_DATABIT_16;
    } else if (m_sampleBitLength == 32) {
        sampleBitLength = I2S_DATABIT_32;
    } else {
        /* TODO */
        sampleBitLength = I2S_DATABIT_32;
    }
    
    if (m_masterMode == 0) {
        masterSlave = I2S_MODE_SLAVE;
    } else {
        masterSlave = I2S_MODE_MASTER;
    }
    
#if defined(TARGET_NUMAKER_PFM_NUC472)
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    _i2s_base->CTL |= (I2S_FIFO_TX_LEVEL_WORD_0 | I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Enable I2S Tx function to send data */
    I2S_ENABLE_TX(_i2s_base);
    
    /* Enable Tx threshold level interrupt */
    I2S_EnableInt(_i2s_base, I2S_IEN_TXTHIEN_Msk);
#elif defined(TARGET_NUMAKER_PFM_M453)
    /* Slave mode, 16-bit word width, stereo mode, I2S format. Set TX and RX FIFO threshold to middle value. */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_DISABLE_TX(_i2s_base);
    I2S_DISABLE_RX(_i2s_base);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Enable I2S Tx function to send data */
    I2S_ENABLE_TX(_i2s_base);
    
    /* Start I2S play iteration */
    I2S_EnableInt(_i2s_base, I2S_FIFO_TXTH_INT_MASK);
#elif defined(TARGET_NUMAKER_PFM_M487)
    /* Open I2S0 as slave mode */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    //_i2s_base->CTL0 |= I2S_CTL0_ORDER_Msk;
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    I2S_ENABLE_TX(_i2s_base);
    
    I2S_EnableInt(_i2s_base, I2S_IEN_TXTHIEN_Msk);
#elif defined(TARGET_NUMAKER_PFM_NANO130)
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    _i2s_base->CTRL |= BIT22;
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Enable I2S Tx function to send data */
    I2S_ENABLE_TX(_i2s_base);
    
    /* Enable Tx threshold level interrupt */
    I2S_EnableInt(_i2s_base, I2S_INTEN_TXTHIE_Msk);
#elif defined(TARGET_NUMAKER_IOT_M487)
    /* Open I2S0 as slave mode */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    //_i2s_base->CTL0 |= I2S_CTL0_ORDER_Msk;
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    I2S_ENABLE_TX(_i2s_base);
    
    I2S_EnableInt(_i2s_base, I2S_IEN_TXTHIEN_Msk);
#endif
}

void NuI2SDevice::record(void) {
    int channelCount;
    int sampleBitLength;
    int masterSlave;
    
    if (m_channelCount == 2) {
        #if defined(TARGET_NUMAKER_PFM_M487)
        channelCount = I2S_DISABLE_MONO;
        #elif defined(TARGET_NUMAKER_IOT_M487)
        channelCount = I2S_DISABLE_MONO;
        #else
        channelCount = I2S_STEREO;
        #endif
    } else {
        #if defined(TARGET_NUMAKER_PFM_M487)
        channelCount = I2S_ENABLE_MONO;
        #elif defined(TARGET_NUMAKER_IOT_M487)
        channelCount = I2S_ENABLE_MONO;
        #else
        channelCount = I2S_MONO;
        #endif
    }
    
    if (m_sampleBitLength == 16) {
        sampleBitLength = I2S_DATABIT_16;
    } else if (m_sampleBitLength == 32) {
        sampleBitLength = I2S_DATABIT_32;
    } else {
        /* TODO */
        sampleBitLength = I2S_DATABIT_32;
    }
    
    if (m_masterMode == 0) {
        masterSlave = I2S_MODE_SLAVE;
    } else {
        masterSlave = I2S_MODE_MASTER;
    }
    
#if defined(TARGET_NUMAKER_PFM_NUC472)
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Enable Rx threshold level interrupt */
    I2S_EnableInt(_i2s_base, I2S_IEN_RXTHIEN_Msk);
    
    /* Enable I2S Rx function to receive data */
    I2S_ENABLE_RX(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_M453)
    /* Slave mode, 16-bit word width, stereo mode, I2S format. Set TX and RX FIFO threshold to middle value. */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    /* Start I2S record iteration */
    I2S_EnableInt(_i2s_base, I2S_FIFO_RXTH_INT_MASK);
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
#elif defined(TARGET_NUMAKER_PFM_M487)
    /* Open I2S0 as slave mode */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    //_i2s_base->CTL0 |= I2S_CTL0_ORDER_Msk;
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    I2S_EnableInt(_i2s_base, I2S_IEN_RXTHIEN_Msk);
    
    I2S_ENABLE_RX(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_NANO130)
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    _i2s_base->CTRL |= BIT22;
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    //NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Enable Rx threshold level interrupt */
    I2S_EnableInt(_i2s_base, I2S_INTEN_RXTHIE_Msk);
    
    /* Enable I2S Rx function to receive data */
    I2S_ENABLE_RX(_i2s_base);
#elif defined(TARGET_NUMAKER_IOT_M487)
    /* Open I2S0 as slave mode */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    //_i2s_base->CTL0 |= I2S_CTL0_ORDER_Msk;
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    I2S_EnableInt(_i2s_base, I2S_IEN_RXTHIEN_Msk);
    
    I2S_ENABLE_RX(_i2s_base);
#endif
}

void NuI2SDevice::stop(void) {
    I2S_DISABLE_TX(_i2s_base);
    I2S_DISABLE_RX(_i2s_base);
    
#if defined(TARGET_NUMAKER_PFM_NUC472)
    I2S_DisableInt(_i2s_base, (I2S_IEN_TXTHIEN_Msk    | I2S_IEN_RXTHIEN_Msk));
#elif defined(TARGET_NUMAKER_PFM_M453)
    I2S_DisableInt(_i2s_base, (I2S_FIFO_TXTH_INT_MASK | I2S_FIFO_RXTH_INT_MASK));
#elif defined(TARGET_NUMAKER_PFM_M487)
    I2S_DisableInt(_i2s_base, (I2S_IEN_TXTHIEN_Msk    | I2S_IEN_RXTHIEN_Msk));
#elif defined(TARGET_NUMAKER_PFM_NANO130)
    I2S_DisableInt(_i2s_base, (I2S_INTEN_TXTHIE_Msk   | I2S_INTEN_RXTHIE_Msk));
#elif defined(TARGET_NUMAKER_IOT_M487)
    I2S_DisableInt(_i2s_base, (I2S_IEN_TXTHIEN_Msk    | I2S_IEN_RXTHIEN_Msk));
#endif
    
    NVIC_DisableIRQ(_i2s_modinit->irq_n);
}

void NuI2SDevice::write(int* buffer, int from, int length) {
    int to = from + length;
    for (int i = from; i < to; i++) {
        I2S_WRITE_TX_FIFO(_i2s_base, buffer[i]);
    }
}

void NuI2SDevice::read(void) {
#if defined(TARGET_NUMAKER_PFM_NUC472)
    rxBuffer[0] = I2S_READ_RX_FIFO(_i2s_base);
    rxBuffer[1] = I2S_READ_RX_FIFO(_i2s_base);
    rxBuffer[2] = I2S_READ_RX_FIFO(_i2s_base);
    rxBuffer[3] = I2S_READ_RX_FIFO(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_M453)
    rxBuffer[0] = I2S_READ_RX_FIFO(_i2s_base);
    rxBuffer[1] = I2S_READ_RX_FIFO(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_M487)
    rxBuffer[0] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[1] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[2] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[3] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[4] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[5] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[6] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[7] = I2S_READ_RX_FIFO(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_NANO130)
    rxBuffer[0] = I2S_READ_RX_FIFO(_i2s_base);
    rxBuffer[1] = I2S_READ_RX_FIFO(_i2s_base);
    rxBuffer[2] = I2S_READ_RX_FIFO(_i2s_base);
    rxBuffer[3] = I2S_READ_RX_FIFO(_i2s_base);
#elif defined(TARGET_NUMAKER_IOT_M487)
    rxBuffer[0] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[1] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[2] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[3] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[4] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[5] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[6] = I2S_READ_RX_FIFO(_i2s_base);
    //rxBuffer[7] = I2S_READ_RX_FIFO(_i2s_base);
#endif
}

void NuI2SDevice::attach(void(*fptr)(void)) {
    if (fptr) {
        m_i2s_callback = fptr;
    } else {
        m_i2s_callback = donothing;
    }
}

void NuI2SDevice::attach(Callback<void()> func) {
    if (func) {
        m_i2s_callback = func;
    } else {
        m_i2s_callback = donothing;
    }
}

int NuI2SDevice::status(void) {
#if defined(TARGET_NUMAKER_PFM_NUC472)
    return _i2s_base->STATUS;
#elif defined(TARGET_NUMAKER_PFM_M453)
    return _i2s_base->I2SSTS;
#elif defined(TARGET_NUMAKER_PFM_M487)
    return _i2s_base->STATUS0;
#elif defined(TARGET_NUMAKER_PFM_NANO130)
    return _i2s_base->STATUS;
#elif defined(TARGET_NUMAKER_IOT_M487)
    return _i2s_base->STATUS0;
#endif
}

int NuI2SDevice::status1(void) {
#if defined(TARGET_NUMAKER_PFM_NUC472)
    return _i2s_base->STATUS;
#elif defined(TARGET_NUMAKER_PFM_M453)
    return _i2s_base->I2SSTS;
#elif defined(TARGET_NUMAKER_PFM_M487)
    return _i2s_base->STATUS1;
#elif defined(TARGET_NUMAKER_PFM_NANO130)
    return _i2s_base->STATUS;
#elif defined(TARGET_NUMAKER_IOT_M487)
    return _i2s_base->STATUS1;
#endif
}

void NuI2SDevice::format(int rate, char count, char length) {
    m_samplingRate    = rate;
    m_channelCount    = count;
    m_sampleBitLength = length;
}

void NuI2SDevice::m_i2s_irq(void) {
    m_i2s_callback.call();
}

void NuI2SDevice::lock(void) {
    NVIC_DisableIRQ(_i2s_modinit->irq_n);
}

void NuI2SDevice::unlock(void) {
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
}

void NuI2SDevice::readwrite(void) {
    I2S_WRITE_TX_FIFO(_i2s_base, I2S_READ_RX_FIFO(_i2s_base));
}

void NuI2SDevice::loopback(void) {
    int channelCount;
    int sampleBitLength;
    int masterSlave;
    
    if (m_channelCount == 2) {
        #if defined(TARGET_NUMAKER_PFM_M487)
        channelCount = I2S_DISABLE_MONO;
        #elif defined(TARGET_NUMAKER_IOT_M487)
        channelCount = I2S_DISABLE_MONO;
        #else
        channelCount = I2S_STEREO;
        #endif
    } else {
        #if defined(TARGET_NUMAKER_PFM_M487)
        channelCount = I2S_ENABLE_MONO;
        #elif defined(TARGET_NUMAKER_IOT_M487)
        channelCount = I2S_ENABLE_MONO;
        #else
        channelCount = I2S_MONO;
        #endif
    }
    
    if (m_sampleBitLength == 16) {
        sampleBitLength = I2S_DATABIT_16;
    } else if (m_sampleBitLength == 32) {
        sampleBitLength = I2S_DATABIT_32;
    } else {
        /* TODO */
        sampleBitLength = I2S_DATABIT_32;
    }
    
    if (m_masterMode == 0) {
        masterSlave = I2S_MODE_SLAVE;
    } else {
        masterSlave = I2S_MODE_MASTER;
    }
    
#if defined(TARGET_NUMAKER_PFM_NUC472)
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    _i2s_base->CTL |= (I2S_FIFO_TX_LEVEL_WORD_0 | I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Enable Tx threshold level interrupt */
    I2S_EnableInt(_i2s_base, I2S_IEN_RXTHIEN_Msk);
    
    /* Enable I2S Tx function to send data */
    I2S_ENABLE_RX(_i2s_base);
    
    while ( I2S_GET_TX_FIFO_LEVEL(_i2s_base) < 1 );
    I2S_ENABLE_TX(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_M453)
    /* Slave mode, 16-bit word width, stereo mode, I2S format. Set TX and RX FIFO threshold to middle value. */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_DISABLE_TX(_i2s_base);
    I2S_DISABLE_RX(_i2s_base);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Start I2S play iteration */
    I2S_EnableInt(_i2s_base, I2S_FIFO_RXTH_INT_MASK);
    
    /* Enable I2S Tx function to send data */
    I2S_ENABLE_RX(_i2s_base);
    
    while ( I2S_GET_TX_FIFO_LEVEL(_i2s_base) < 1 );
    I2S_ENABLE_TX(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_M487)
    /* Open I2S0 as slave mode */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    //_i2s_base->CTL0 |= I2S_CTL0_ORDER_Msk;
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    //I2S_EnableInt(_i2s_base, I2S_IEN_TXTHIEN_Msk);
    
    //I2S_ENABLE_TX(_i2s_base);
    
    I2S_EnableInt(_i2s_base, I2S_IEN_RXTHIEN_Msk);
    
    I2S_ENABLE_RX(_i2s_base);
    
    while ( I2S_GET_TX_FIFO_LEVEL(_i2s_base) < 1 );
    I2S_ENABLE_TX(_i2s_base);
#elif defined(TARGET_NUMAKER_PFM_NANO130)
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    _i2s_base->CTRL |= BIT22;
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    #if 0
    //NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    /* Enable Tx threshold level interrupt */
    I2S_EnableInt(_i2s_base, I2S_INTEN_TXTHIE_Msk);
    
    /* Enable I2S Tx function to send data */
    I2S_ENABLE_TX(_i2s_base);
    #else
    I2S_EnableInt(_i2s_base, I2S_INTEN_RXTHIE_Msk);
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    I2S_ENABLE_RX(_i2s_base);
    
    while ( I2S_GET_TX_FIFO_LEVEL(_i2s_base) < 1 );
    I2S_ENABLE_TX(_i2s_base);
    #endif
#elif defined(TARGET_NUMAKER_IOT_M487)
    /* Open I2S0 as slave mode */
    I2S_Open(_i2s_base, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    I2S_SetFIFO(_i2s_base, I2S_FIFO_TX_LEVEL_WORD_0, I2S_FIFO_RX_LEVEL_WORD_1);
    I2S_CLR_TX_FIFO(_i2s_base);
    I2S_CLR_RX_FIFO(_i2s_base);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    //I2S_WRITE_TX_FIFO(_i2s_base, 0x00);
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(_i2s_base, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(_i2s_base, m_samplingRate * 256);
    }
    //_i2s_base->CTL0 |= I2S_CTL0_ORDER_Msk;
    
    NVIC_SetVector(_i2s_modinit->irq_n, m_i2s_irq_thunk.entry());
    
    NVIC_EnableIRQ(_i2s_modinit->irq_n);
    
    //I2S_EnableInt(_i2s_base, I2S_IEN_TXTHIEN_Msk);
    
    //I2S_ENABLE_TX(_i2s_base);
    
    I2S_EnableInt(_i2s_base, I2S_IEN_RXTHIEN_Msk);
    
    I2S_ENABLE_RX(_i2s_base);
    
    while ( I2S_GET_TX_FIFO_LEVEL(_i2s_base) < 1 );
    I2S_ENABLE_TX(_i2s_base);
#endif
}
