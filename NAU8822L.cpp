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

#include "NAU8822L.h"

NAU8822L::NAU8822L(PinName i2c_sda, PinName i2c_scl, int i2c_addr, PinName i2s_tx, PinName i2s_rx, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrclk)
                         : m_addr(i2c_addr), m_I2C(i2c_sda, i2c_scl), m_I2S(i2s_tx, i2s_rx, i2s_bclk, i2s_mclk, i2s_lrclk) {
    m_I2C.frequency(100000);
    power();
}

void NAU8822L::I2C_WriteNAU8822(uint8_t u8addr, uint16_t u16data)
{
    char g_au8TxData[2];

    g_au8TxData[0] = ((u8addr << 1)  | (u16data >> 8));  //addr(7bit) + data(first bit)
    g_au8TxData[1] = (char)(u16data & 0x00FF);         //data(8bit)
    m_I2C.write((m_addr << 1), g_au8TxData, 2, true);
#if 0
    if ( m_I2C.write((m_addr << 1), g_au8TxData, 2, true) )
    {
        printf("%d fail\n", u8addr);
    }
    else
    {
        printf("%d done\n", u8addr);
    }
#endif
}

void NAU8822L::power(void) {
//    printf("\nConfigure NAU8822 ...\n");

    I2C_WriteNAU8822(0,  0x000);   /* Reset all registers */
    Thread::wait(500);
    I2C_WriteNAU8822(0,  0x000);   /* Reset all registers */
    Thread::wait(500);

//#ifdef INPUT_IS_AUXIN //input source is AUXIN
    I2C_WriteNAU8822(1,  0x02F);
    I2C_WriteNAU8822(2,  0x1B3);   /* Enable L/R Headphone, ADC Mix/Boost, ADC */
    I2C_WriteNAU8822(3,  0x07F);   /* Enable L/R main mixer, DAC */
    I2C_WriteNAU8822(4,  0x010);   /* 16-bit word length, I2S format, Stereo */
    I2C_WriteNAU8822(5,  0x000);   /* Companding control and loop back mode (all disable) */
    I2C_WriteNAU8822(6,  0x1AD);   /* Divide by 6, 16K */
    I2C_WriteNAU8822(7,  0x006);   /* 16K for internal filter coefficients */
    I2C_WriteNAU8822(10, 0x008);   /* DAC soft mute is disabled, DAC oversampling rate is 128x */
    I2C_WriteNAU8822(14, 0x108);   /* ADC HP filter is disabled, ADC oversampling rate is 128x */
    I2C_WriteNAU8822(15, 0x1EF);   /* ADC left digital volume control */
    I2C_WriteNAU8822(16, 0x1EF);   /* ADC right digital volume control */

    I2C_WriteNAU8822(44, 0x000);   /* LLIN/RLIN is not connected to PGA */
    I2C_WriteNAU8822(47, 0x107);   /* LAUXIN connected, and its Gain value */
    I2C_WriteNAU8822(48, 0x107);   /* RAUXIN connected, and its Gain value */
    I2C_WriteNAU8822(50, 0x001);   /* Left DAC connected to LMIX */
    I2C_WriteNAU8822(51, 0x001);   /* Right DAC connected to RMIX */

    I2C_WriteNAU8822(0x34, 0x129);
    I2C_WriteNAU8822(0x35, 0x129);
#if 0   //input source is MIC
    I2C_WriteNAU8822(1,  0x03F);
    I2C_WriteNAU8822(2,  0x1BF);   /* Enable L/R Headphone, ADC Mix/Boost, ADC */
    I2C_WriteNAU8822(3,  0x07F);   /* Enable L/R main mixer, DAC */
    I2C_WriteNAU8822(4,  0x010);   /* 16-bit word length, I2S format, Stereo */
    I2C_WriteNAU8822(5,  0x000);   /* Companding control and loop back mode (all disable) */
    I2C_WriteNAU8822(6,  0x1AD);   /* Divide by 6, 16K */
    I2C_WriteNAU8822(7,  0x006);   /* 16K for internal filter coefficients */
    I2C_WriteNAU8822(10, 0x008);   /* DAC soft mute is disabled, DAC oversampling rate is 128x */
    I2C_WriteNAU8822(14, 0x108);   /* ADC HP filter is disabled, ADC oversampling rate is 128x */
    I2C_WriteNAU8822(15, 0x1EF);   /* ADC left digital volume control */
    I2C_WriteNAU8822(16, 0x1EF);   /* ADC right digital volume control */

    I2C_WriteNAU8822(44, 0x033);   /* LMICN/LMICP is connected to PGA */
    I2C_WriteNAU8822(47, 0x100);   /* Gain value */
    I2C_WriteNAU8822(48, 0x100);   /* Gain value */
    I2C_WriteNAU8822(50, 0x001);   /* Left DAC connected to LMIX */
    I2C_WriteNAU8822(51, 0x001);   /* Right DAC connected to RMIX */

    I2C_WriteNAU8822(0x34, 0x13F);
    I2C_WriteNAU8822(0x35, 0x13F);
#endif

//    printf("[OK]\n");
}

void NAU8822L::start(void) {
    m_I2S.start();
}

void NAU8822L::stop(void) {
    m_I2S.stop();
}

void NAU8822L::write(int *buffer, int from, int length) {
    m_I2S.write(buffer, from, length);
}

void NAU8822L::read(void) {
    m_I2S.read();
}

void NAU8822L::attach(void(*fptr)(void)) {
    m_I2S.attach(fptr);
}
