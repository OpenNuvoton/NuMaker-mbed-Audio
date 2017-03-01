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

class I2S
{
    public:
        I2S(PinName i2s_tx, PinName i2s_rx, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrclk);
        void start(void);
        void stop(void);
        void write(int* buffer, int from,  int length);
        void read(void);
        void attach(void(*fptr)(void));
        int status(void);
        
        int rxBuffer[4];

};

#endif /*__MBED_I2S_H__*/
