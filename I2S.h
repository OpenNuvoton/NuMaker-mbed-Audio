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

#ifndef __MBED_I2S_H__
#define __MBED_I2S_H__

#include "mbed.h"

struct nu_modinit_s;

class NuI2SDevice
{
    public:
        NuI2SDevice(PinName i2s_do, PinName i2s_di, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrck);
        NuI2SDevice(PinName i2s_do, PinName i2s_di, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrck, char i2s_master_enable);
        void start(void);
        void record(void);
        void stop(void);
        void write(int* buffer, int from,  int length);
        void read(void);
        void attach(void(*fptr)(void));
        void attach(Callback<void()> func);
        int  status(void);
        int  status1(void);
        void format(int rate, char count, char length);
        void lock(void);
        void unlock(void);
        void loopback(void);
        void readwrite(void);
        
        int  rxBuffer[8];
        
    private:
        void m_i2s_irq(void);
        
        Callback<void()>        m_i2s_callback;
        CThunk<NuI2SDevice>     m_i2s_irq_thunk;
        
        int  m_samplingRate;
        char m_channelCount;
        char m_sampleBitLength;
        char m_masterMode;
        
        const struct nu_modinit_s * _i2s_modinit;
        /* TODO M487 SPI for I2S */
        #if defined(TARGET_NUMAKER_PFM_NUC472) || defined(TARGET_NUMAKER_PFM_M487) || defined(TARGET_NUMAKER_PFM_NANO130) || defined(TARGET_NUMAKER_IOT_M487)
        I2S_T * _i2s_base;
        #elif defined(TARGET_NUMAKER_PFM_M453)
        SPI_T * _i2s_base;
        #endif
        
};

#endif /*__MBED_I2S_H__*/
