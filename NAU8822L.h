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

#ifndef MBED_NAU8822L_H
#define MBED_NAU8822L_H

#include "mbed.h"

#include "I2S.h"

class NAU8822L
{        
    public:
        NAU8822L(PinName i2c_sda, PinName i2c_scl, int i2c_addr, PinName i2s_tx, PinName i2s_rx, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrclk);
        void power(void);
        void start(void);
        void stop(void);
        void write(int *buffer, int from, int length);
        void read(void);
        void attach(void(*fptr)(void));
        
    private:
        int m_addr;

        I2C m_I2C;
        I2S m_I2S;
        
        void I2C_WriteNAU8822(uint8_t u8addr, uint16_t u16data);

};

#endif
