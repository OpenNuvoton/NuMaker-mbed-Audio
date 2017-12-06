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

#include "NAU88L25.h"

NAU88L25::NAU88L25(PinName i2c_sda, PinName i2c_scl, int i2c_addr, PinName i2s_do, PinName i2s_di, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrck)
                         : m_addr(i2c_addr), m_I2C(i2c_sda, i2c_scl), m_I2S(i2s_do, i2s_di, i2s_bclk, i2s_mclk, i2s_lrck) {
    m_I2C.frequency(100000);
    m_masterMode = 1;    // codec is master mode and i2s is slave mode
    power();
    format(16000, 2, 16);
    rxBuffer = &m_I2S.rxBuffer[0];
}

NAU88L25::NAU88L25(PinName i2c_sda, PinName i2c_scl, int i2c_addr, PinName i2s_tx, PinName i2s_rx, PinName i2s_bclk, PinName i2s_mclk, PinName i2s_lrclk, char i2s_master_enable, char codec_master_enable)
                         : m_addr(i2c_addr), m_I2C(i2c_sda, i2c_scl), m_I2S(i2s_tx, i2s_rx, i2s_bclk, i2s_mclk, i2s_lrclk, i2s_master_enable) {
    m_I2C.frequency(100000);
    m_masterMode = codec_master_enable;
    power();
    format(16000, 2, 16);
    rxBuffer = &m_I2S.rxBuffer[0];
}

void NAU88L25::I2C_WriteNAU88L25(uint16_t u16addr, uint16_t u16data)
{
    char g_au8TxData[4];
    
    g_au8TxData[0] = (uint8_t)((u16addr >> 8) & 0x00FF);   //addr [15:8]
    g_au8TxData[1] = (uint8_t)(u16addr & 0x00FF);          //addr [ 7:0]
    g_au8TxData[2] = (uint8_t)((u16data >> 8) & 0x00FF);   //data [15:8]
    g_au8TxData[3] = (uint8_t)(u16data & 0x00FF);          //data [ 7:0]
    m_I2C.write((m_addr << 1), g_au8TxData, 4);
#if 0
    if ( m_I2C.write((m_addr << 1), g_au8TxData, 4, true) )
    {
        printf("%d fail\n", u16addr);
    }
    else
    {
        printf("%d done\n", u16addr);
    }
#endif
}

void NAU88L25::power(void) {
    //char au8RxData[2];
    //char au8TxData[2];
//    printf("\nConfigure NAU88L25 ...\n");
    
    I2C_WriteNAU88L25( 0x0000, 0x0000 );   /* Reset all registers */
    Thread::wait(10);
    //I2C_WriteNAU88L25( 0x0000, 0x0000 );   /* Reset all registers */
    //Thread::wait(500);
    
    I2C_WriteNAU88L25( 0x0066, 0x0060 );
    
    I2C_WriteNAU88L25( 0x0003, 0x8053 );    /* CLK_DIVIDER */
    // FLL Setting
    I2C_WriteNAU88L25( 0x0004, 0x0001 );    /* FLL1 FLL_RATIO */
    I2C_WriteNAU88L25( 0x0005, 0x3126 );    /* FLL2 FLL_FRAC */
    I2C_WriteNAU88L25( 0x0006, 0x0008 );    /* FLL3 FLL_CLK_REF_SRC and FLL_INTEGER */
    I2C_WriteNAU88L25( 0x0007, 0x0010 );    /* FLL4 */
    I2C_WriteNAU88L25( 0x0008, 0xC000 );    /* FLL5 */
    I2C_WriteNAU88L25( 0x000C, 0x0048 );
    // Digital Audio Bus Format
    I2C_WriteNAU88L25( 0x001C, 0x0002 );    /* I2S_PCM_CTRL1 16-bit I2S */
    if (m_masterMode) {
        I2C_WriteNAU88L25( 0x001D, 0x301A ); //301A:Master 3012:Slave
    } else {
        I2C_WriteNAU88L25( 0x001D, 0x3012 ); //301A:Master 3012:Slave
        I2C_WriteNAU88L25( 0x001E, 0x2000 );
    }
    I2C_WriteNAU88L25( 0x002B, 0x0012 );
    I2C_WriteNAU88L25( 0x002C, 0x0084 );
    I2C_WriteNAU88L25( 0x0030, 0x00CF );    // ADC gain
    I2C_WriteNAU88L25( 0x0031, 0x1000 );
    I2C_WriteNAU88L25( 0x0033, 0x00CF );    // DAC gain
    I2C_WriteNAU88L25( 0x0034, 0x02CF );    // DAC gain
    I2C_WriteNAU88L25( 0x0050, 0x2007 );
    I2C_WriteNAU88L25( 0x0066, 0x0060 );
    I2C_WriteNAU88L25( 0x0068, 0xC300 );
    I2C_WriteNAU88L25( 0x006A, 0x0083 );
    I2C_WriteNAU88L25( 0x0072, 0x0260 );
    I2C_WriteNAU88L25( 0x0073, 0x332C );
    I2C_WriteNAU88L25( 0x0074, 0x4502 );
    I2C_WriteNAU88L25( 0x0076, 0x3140 );
    I2C_WriteNAU88L25( 0x007F, 0x553F );
    I2C_WriteNAU88L25( 0x0080, 0x0820 );
    I2C_WriteNAU88L25( 0x0001, 0x07D4 );

//    printf("[OK]\n");
    #if 0
    for (int i = 0; i <= 0x80; i++) {
        au8TxData[0] = 0x00;
        au8TxData[1] = i;
        m_I2C.write((m_addr << 1), au8TxData, 2);
        m_I2C.read((m_addr << 1), au8RxData, 2);
        printf("0x%04X 0x%02X%02X\r\n", i, au8RxData[0], au8RxData[1]);
    }
    #endif
}

void NAU88L25::start(void) {
    m_I2S.start();
}

void NAU88L25::record(void) {
    m_I2S.record();
}

void NAU88L25::stop(void) {
    m_I2S.stop();
}

void NAU88L25::write(int *buffer, int from, int length) {
    m_I2S.write(buffer, from, length);
}

void NAU88L25::read(void) {
    m_I2S.read();
}

void NAU88L25::attach(void(*fptr)(void)) {
    m_I2S.attach(fptr);
}

void NAU88L25::attach(Callback<void()> func) {
    m_I2S.attach(func);
}

void NAU88L25::format(int rate, char count, char length) {
    int  clkDivider;
    int  i2sPcmCtrl2;
    int  lrClkDiv;
    char bClkDiv;
    char mClkDiv;
    
    if (count > 1) {
        /* FIXME */
        count = 2;
    } else {
        count = 1;
    }
    
    if (length > 16) {
        /* FIXME */
        length = 32;
    } else {
        length = 16;
    }
    
    if (m_masterMode == 0) {
        m_I2S.format(rate, count, length);
        
        return;
    }
    
    if (rate % 11025) {
        /* 48000 series 12.288Mhz */
        I2C_WriteNAU88L25( 0x0005, 0x3126 );    /* FLL2 FLL_FRAC */
        I2C_WriteNAU88L25( 0x0006, 0x0008 );    /* FLL3 FLL_INTEGER */
        
        /* FIXME */
        if (rate > 48000)
            rate = 8000;
        
        mClkDiv = 49152000 / (rate * 256);
    } else {
        /* 44100 series 11.2896Mhz */
        I2C_WriteNAU88L25( 0x0005, 0x86C2 );    /* FLL2 FLL_FRAC */
        I2C_WriteNAU88L25( 0x0006, 0x0007 );    /* FLL3 FLL_INTEGER */
        
        /* FIXME */
        if (rate > 44100)
            rate = 11025;
        
        mClkDiv = 45158400 / (rate * 256);
    }
    
    bClkDiv  = (rate * 256) / (rate * count * length);
    lrClkDiv = (rate * count * length) / rate;
    
    switch (mClkDiv) {
        case 1:
            mClkDiv = 0;
            break;
        case 2:
            mClkDiv = 2;
            break;
        case 4:
            mClkDiv = 3;
            break;
        case 8:
            mClkDiv = 4;
            break;
        case 16:
            mClkDiv = 5;
            break;
        case 32:
            mClkDiv = 6;
            break;
        case 3:
            mClkDiv = 7;
            break;
        case 6:
            mClkDiv = 10;
            break;
        case 12:
            mClkDiv = 11;
            break;
        case 24:
            mClkDiv = 12;
            break;
        case 48:
            mClkDiv = 13;
            break;
        case 96:
            mClkDiv = 14;
            break;
        case 5:
            mClkDiv = 15;
            break;
        default:
            printf("mclk divider not match!\n");
            mClkDiv = 0;
            break;
    }
    
    clkDivider = 0x8050 | mClkDiv;
    I2C_WriteNAU88L25( 0x0003, clkDivider );    /* CLK_DIVIDER */
    
    switch (bClkDiv) {
        case 2:
            bClkDiv = 0;
            break;
        case 4:
            bClkDiv = 1;
            break;
        case 8:
            bClkDiv = 2;
            break;
        case 16:
            bClkDiv = 3;
            break;
        case 32:
            bClkDiv = 4;
            break;
        case 64:
            bClkDiv = 5;
            break;
        default:
            printf("bclk divider not match!\n");
            bClkDiv = 0;
            break;
    }
    
    switch (lrClkDiv) {
        case 256:
            lrClkDiv = 0;
            break;
        case 128:
            lrClkDiv = 1;
            break;
        case 64:
            lrClkDiv = 2;
            break;
        case 32:
            lrClkDiv = 3;
            break;
        default:
            printf("lrclk divider not match!\n");
            lrClkDiv = 0;
            break;
    }
    
    if (length == 16) {
        I2C_WriteNAU88L25( 0x001C, 0x0002 );    /* I2S_PCM_CTRL1 16-bit I2S */
    } else {
        /* FIXME */
        I2C_WriteNAU88L25( 0x001C, 0x000E );    /* I2S_PCM_CTRL1 32-bit I2S */
    }
    
    i2sPcmCtrl2 = 0x0018 | (lrClkDiv << 12) | bClkDiv;

    I2C_WriteNAU88L25( 0x001D, i2sPcmCtrl2 );
    
    m_I2S.format(rate, count, length);
}

void NAU88L25::lock(void) {
    m_I2S.lock();
}

void NAU88L25::unlock(void) {
    m_I2S.unlock();
}

void NAU88L25::loopback(void) {
    m_I2S.loopback();
}

void NAU88L25::readwrite(void) {
    m_I2S.readwrite();
}
