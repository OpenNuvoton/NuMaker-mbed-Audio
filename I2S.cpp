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

#include "I2S.h"

FunctionPointer testCallback;

#if defined(TARGET_NUMAKER_PFM_NUC472)
extern "C" void I2S1_IRQHandler(void) {
    testCallback.call();
}
#elif defined(TARGET_NUMAKER_PFM_M453)
extern "C" void SPI1_IRQHandler(void) {
    testCallback.call();
}
#endif

I2S::I2S(PinName i2s_tx, PinName i2s_rx, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrclk) {
    m_masterMode = 0; // i2s as slave mode
    
#if defined(TARGET_NUMAKER_PFM_NUC472)
    /* Set multi function pin for I2S1 */
    /* GPG7, GPG8, GPG9, GPI11, GPI12 */
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~SYS_GPG_MFPL_PG7MFP_Msk) | SYS_GPG_MFPL_PG7MFP_I2S1_MCLK;
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~(SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG4MFP_Msk)) | (SYS_GPG_MFPL_PG3MFP_I2S1_DO | SYS_GPG_MFPL_PG4MFP_I2S1_DI);
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~(SYS_GPG_MFPL_PG5MFP_Msk | SYS_GPG_MFPL_PG6MFP_Msk)) | (SYS_GPG_MFPL_PG5MFP_I2S1_BCLK | SYS_GPG_MFPL_PG6MFP_I2S1_LRCK);
    
    /* Enable IP clock */
    CLK_EnableModuleClock(I2S1_MODULE);
    
//    #ifdef INPUT_IS_AUXIN
    
//#else
//		I2S_Open(I2S1, I2S_MODE_SLAVE, 16000, I2S_DATABIT_16, I2S_MONO, I2S_FORMAT_I2S, I2S_I2S);
//#endif
    
    // select source from HXT(12MHz)
    CLK_SetModuleClock(I2S1_MODULE, CLK_CLKSEL3_I2S1SEL_HXT, 0);
    
    
    
//#ifndef INPUT_IS_AUXIN
//		I2S_SET_MONO_RX_CHANNEL(I2S1, I2S_MONO_LEFT);       //WAU8822 will store data in left channel
//#endif
#elif defined(TARGET_NUMAKER_PFM_M453)
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PD multi-function pins for SPI1 I2SMCLK */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD0MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD0MFP_SPI1_I2SMCLK);
    
    /* Configure SPI1 related multi-function pins. */
    /* GPA[7:4] : SPI1_CLK (I2S1_BCLK), SPI1_MISO (I2S1_DI), SPI1_MOSI (I2S1_DO), SPI1_SS (I2S1_LRCLK). */
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA7MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA4MFP_SPI1_SS | SYS_GPA_MFPL_PA5MFP_SPI1_MOSI | SYS_GPA_MFPL_PA6MFP_SPI1_MISO | SYS_GPA_MFPL_PA7MFP_SPI1_CLK);
    
    /* Select PCLK1 as the clock source of SPI1 */
    CLK_SetModuleClock(SPI1_MODULE, CLK_CLKSEL2_SPI1SEL_PCLK1, MODULE_NoMsk);
    
    /* Enable peripheral clock */
    CLK_EnableModuleClock(SPI1_MODULE);
    
    
#endif
}

I2S::I2S(PinName i2s_tx, PinName i2s_rx, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrclk, char i2s_master_enable) {
    /* FIXME */
    m_masterMode = i2s_master_enable;
    
#if defined(TARGET_NUMAKER_PFM_NUC472)
    /* Set multi function pin for I2S1 */
    /* GPG7, GPG8, GPG9, GPI11, GPI12 */
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~SYS_GPG_MFPL_PG7MFP_Msk) | SYS_GPG_MFPL_PG7MFP_I2S1_MCLK;
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~(SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG4MFP_Msk)) | (SYS_GPG_MFPL_PG3MFP_I2S1_DO | SYS_GPG_MFPL_PG4MFP_I2S1_DI);
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~(SYS_GPG_MFPL_PG5MFP_Msk | SYS_GPG_MFPL_PG6MFP_Msk)) | (SYS_GPG_MFPL_PG5MFP_I2S1_BCLK | SYS_GPG_MFPL_PG6MFP_I2S1_LRCK);
    
    /* Enable IP clock */
    CLK_EnableModuleClock(I2S1_MODULE);
    
//    #ifdef INPUT_IS_AUXIN
    
//#else
//		I2S_Open(I2S1, I2S_MODE_SLAVE, 16000, I2S_DATABIT_16, I2S_MONO, I2S_FORMAT_I2S, I2S_I2S);
//#endif
    
    // select source from HXT(12MHz)
    CLK_SetModuleClock(I2S1_MODULE, CLK_CLKSEL3_I2S1SEL_HXT, 0);
    
    
    
//#ifndef INPUT_IS_AUXIN
//		I2S_SET_MONO_RX_CHANNEL(I2S1, I2S_MONO_LEFT);       //WAU8822 will store data in left channel
//#endif
#elif defined(TARGET_NUMAKER_PFM_M453)
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PD multi-function pins for SPI1 I2SMCLK */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD0MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD0MFP_SPI1_I2SMCLK);
    
    /* Configure SPI1 related multi-function pins. */
    /* GPA[7:4] : SPI1_CLK (I2S1_BCLK), SPI1_MISO (I2S1_DI), SPI1_MOSI (I2S1_DO), SPI1_SS (I2S1_LRCLK). */
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA7MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA4MFP_SPI1_SS | SYS_GPA_MFPL_PA5MFP_SPI1_MOSI | SYS_GPA_MFPL_PA6MFP_SPI1_MISO | SYS_GPA_MFPL_PA7MFP_SPI1_CLK);
    
    /* Select PCLK1 as the clock source of SPI1 */
    CLK_SetModuleClock(SPI1_MODULE, CLK_CLKSEL2_SPI1SEL_PCLK1, MODULE_NoMsk);
    
    /* Enable peripheral clock */
    CLK_EnableModuleClock(SPI1_MODULE);
    
    
#endif
}

void I2S::start(void) {
    int channelCount;
    int sampleBitLength;
    int masterSlave;
    
    if (m_channelCount == 2) {
        channelCount = I2S_STEREO;
    } else {
        channelCount = I2S_MONO;
    }
    
    if (m_sampleBitLength == 16) {
        sampleBitLength = I2S_DATABIT_16;
    } else if (m_sampleBitLength == 32) {
        sampleBitLength = I2S_DATABIT_32;
    } else {
        /* FIXME */
        sampleBitLength = I2S_DATABIT_32;
    }
    
    if (m_masterMode == 0) {
        masterSlave = I2S_MODE_SLAVE;
    } else {
        masterSlave = I2S_MODE_MASTER;
    }
    
#if defined(TARGET_NUMAKER_PFM_NUC472)
    I2S_Open(I2S1, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(I2S1, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(I2S1, m_samplingRate * 256);
    }
    
    NVIC_SetVector(I2S1_IRQn, (uint32_t)I2S1_IRQHandler);
    NVIC_EnableIRQ(I2S1_IRQn);
    
    /* Enable Tx threshold level interrupt */
    I2S_EnableInt(I2S1, I2S_IEN_TXTHIEN_Msk);
    
    /* Enable I2S Tx function to send data */
    I2S_ENABLE_TX(I2S1);
#elif defined(TARGET_NUMAKER_PFM_M453)
    /* Slave mode, 16-bit word width, stereo mode, I2S format. Set TX and RX FIFO threshold to middle value. */
    I2S_Open(SPI1, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(SPI1, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(SPI1, m_samplingRate * 256);
    }
    
    NVIC_SetVector(SPI1_IRQn, (uint32_t)SPI1_IRQHandler);
    
    /* Start I2S play iteration */
    I2S_EnableInt(SPI1, I2S_FIFO_TXTH_INT_MASK);
    NVIC_EnableIRQ(SPI1_IRQn);
#endif
}

void I2S::record(void) {
    int channelCount;
    int sampleBitLength;
    int masterSlave;
    
    if (m_channelCount == 2) {
        channelCount = I2S_STEREO;
    } else {
        /* TODO */
        channelCount = I2S_MONO;
    }
    
    if (m_sampleBitLength == 16) {
        sampleBitLength = I2S_DATABIT_16;
    } else if (m_sampleBitLength == 32) {
        /* TODO */
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
    I2S_Open(I2S1, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S, I2S_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(I2S1, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(I2S1, m_samplingRate * 256);
    }
    
    NVIC_SetVector(I2S1_IRQn, (uint32_t)I2S1_IRQHandler);
    NVIC_EnableIRQ(I2S1_IRQn);
    
    /* Enable Rx threshold level interrupt */
    I2S_EnableInt(I2S1, I2S_IEN_RXTHIEN_Msk);
    
    /* Enable I2S Rx function to receive data */
    I2S_ENABLE_RX(I2S1);
#elif defined(TARGET_NUMAKER_PFM_M453)
    /* Slave mode, 16-bit word width, stereo mode, I2S format. Set TX and RX FIFO threshold to middle value. */
    I2S_Open(SPI1, masterSlave, m_samplingRate, sampleBitLength, channelCount, I2S_FORMAT_I2S);
    
    if (m_masterMode == 0) {
        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(SPI1, 12000000);
    } else {
        /* FIXME */
        I2S_EnableMCLK(SPI1, m_samplingRate * 256);
    }
    
    NVIC_SetVector(SPI1_IRQn, (uint32_t)SPI1_IRQHandler);
    
    /* Start I2S record iteration */
    I2S_EnableInt(SPI1, I2S_FIFO_RXTH_INT_MASK);
    NVIC_EnableIRQ(SPI1_IRQn);
#endif
}

void I2S::stop(void) {
#if defined(TARGET_NUMAKER_PFM_NUC472)
    NVIC_DisableIRQ(I2S1_IRQn);
#elif defined(TARGET_NUMAKER_PFM_M453)
    NVIC_DisableIRQ(SPI1_IRQn);
#endif
}

void I2S::write(int* buffer, int from, int length) {
    int to = from + length;
    for (int i = from; i < to; i++) {
#if defined(TARGET_NUMAKER_PFM_NUC472)
        I2S_WRITE_TX_FIFO(I2S1, buffer[i]);
#elif defined(TARGET_NUMAKER_PFM_M453)
        I2S_WRITE_TX_FIFO(SPI1, buffer[i]);
#endif
    }
}

void I2S::read(void) {
#if defined(TARGET_NUMAKER_PFM_NUC472)
    rxBuffer[0] = I2S_READ_RX_FIFO(I2S1);
    rxBuffer[1] = I2S_READ_RX_FIFO(I2S1);
    rxBuffer[2] = I2S_READ_RX_FIFO(I2S1);
    rxBuffer[3] = I2S_READ_RX_FIFO(I2S1);
#elif defined(TARGET_NUMAKER_PFM_M453)
    rxBuffer[0] = I2S_READ_RX_FIFO(SPI1);
    rxBuffer[1] = I2S_READ_RX_FIFO(SPI1);
#endif
}

void I2S::attach(void(*fptr)(void)) {
    testCallback.attach(fptr);
}

int I2S::status(void) {
#if defined(TARGET_NUMAKER_PFM_NUC472)
    return I2S1->STATUS;
#elif defined(TARGET_NUMAKER_PFM_M453)
    return SPI1->I2SSTS;
#endif
}

void I2S::format(int rate, char count, char length) {
    m_samplingRate    = rate;
    m_channelCount    = count;
    m_sampleBitLength = length;
}
