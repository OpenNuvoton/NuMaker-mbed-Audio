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

extern "C" void I2S1_IRQHandler(void) {
    testCallback.call();
}

I2S::I2S(PinName i2s_tx, PinName i2s_rx, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrclk) {
    /* Set multi function pin for I2S1 */
    /* GPG7, GPG8, GPG9, GPI11, GPI12 */
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~SYS_GPG_MFPL_PG7MFP_Msk) | SYS_GPG_MFPL_PG7MFP_I2S1_MCLK;
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~(SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG4MFP_Msk)) | (SYS_GPG_MFPL_PG3MFP_I2S1_DO | SYS_GPG_MFPL_PG4MFP_I2S1_DI);
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~(SYS_GPG_MFPL_PG5MFP_Msk | SYS_GPG_MFPL_PG6MFP_Msk)) | (SYS_GPG_MFPL_PG5MFP_I2S1_BCLK | SYS_GPG_MFPL_PG6MFP_I2S1_LRCK);
    
    /* Enable IP clock */
    CLK_EnableModuleClock(I2S1_MODULE);
    
//    #ifdef INPUT_IS_AUXIN
    I2S_Open(I2S1, I2S_MODE_SLAVE, 16000, I2S_DATABIT_16, I2S_STEREO, I2S_FORMAT_I2S, I2S_I2S);
//#else
//		I2S_Open(I2S1, I2S_MODE_SLAVE, 16000, I2S_DATABIT_16, I2S_MONO, I2S_FORMAT_I2S, I2S_I2S);
//#endif

    // select source from HXT(12MHz)
    CLK_SetModuleClock(I2S1_MODULE, CLK_CLKSEL3_I2S1SEL_HXT, 0);
    
    /* Set MCLK and enable MCLK */
    I2S_EnableMCLK(I2S1, 12000000);

//#ifndef INPUT_IS_AUXIN
//		I2S_SET_MONO_RX_CHANNEL(I2S1, I2S_MONO_LEFT);       //WAU8822 will store data in left channel
//#endif
}

void I2S::start(void) {
    NVIC_SetVector(I2S1_IRQn, (uint32_t)I2S1_IRQHandler);
    NVIC_EnableIRQ(I2S1_IRQn);
    
    /* Enable Tx threshold level interrupt */
    I2S_EnableInt(I2S1, I2S_IEN_TXTHIEN_Msk);

    /* Enable I2S Tx function to send data */
    I2S_ENABLE_TX(I2S1);
}

void I2S::stop(void) {
    NVIC_DisableIRQ(I2S1_IRQn);
}

void I2S::write(int* buffer, int from, int length) {
    int to = from + length;
    for (int i = from; i < to; i++) {
        I2S_WRITE_TX_FIFO(I2S1, buffer[i]);
    }
}

void I2S::read(void) {
    rxBuffer[0] = I2S_READ_RX_FIFO(I2S1);
    rxBuffer[1] = I2S_READ_RX_FIFO(I2S1);
    rxBuffer[2] = I2S_READ_RX_FIFO(I2S1);
    rxBuffer[3] = I2S_READ_RX_FIFO(I2S1);
}

void I2S::attach(void(*fptr)(void)) {
    testCallback.attach(fptr);
}

int I2S::status(void) {
    return I2S1->STATUS;
}
