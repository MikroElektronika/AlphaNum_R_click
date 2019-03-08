/*
    __alphanumr_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__alphanumr_driver.h"
#include "__alphanumr_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __ALPHANUMR_DRV_I2C__
static uint8_t _slaveAddress;
#endif
uint16_t _ALPHANUMR_SPEED;
static uint16_t _ALPHANUMR_COUNTER;

const uint16_t _ALPHANUMR_CHAR_TABLE[ 52 ] =
{
 // 14segment bit order
 // (dp)(h) (i) (m) (k) (g2)(g1)(j)(i)(f)(e)(d)(c)(b)(a)
 // (14)(13)(12)(11)(10)(9) (8) (7)(6)(5)(4)(3)(2)(1)(0)
 // CHARACTERS
 //----------------------------------------------------
 // Hex        Symbol            Binary
 //----------------------------------------------------
    0x0300,    // '-'            0b0000001100000000
    0x4000,    // '.'            0b0100000000000000
    0x0880,    // '/'            0b0000100010000000
    0x003F,    // '0'            0b0000000000111111
    0x0006,    // '1'            0b0000000000000110
    0x031B,    // '2'            0b0000001100011011
    0x030F,    // '3'            0b0000001100001111
    0x0326,    // '4'            0b0000001100100110
    0x032D,    // '5'            0b0000001100101101
    0x033D,    // '6'            0b0000001100111101
    0x0007,    // '7'            0b0000000000000111
    0x033F,    // '8'            0b0000001100111111
    0x032F,    // '9'            0b0000001100101111
    0x1040,    // ':'            0b0001000001000000
    0x0840,    // ';'            0b0000100001000000
    0x0480,    // '<'            0b0000010010000000
    0x0776,    // '='            0b0000001100001000
    0x2800,    // '>'            0b0010100000000000
    0x1223,    // '?'            0b0001001000100011
    0x027B,    // '@'            0b0000001001111011
    0x0337,    // 'A'            0b0000001100110111
    0x124F,    // 'B'            0b0001001001001111
    0x0039,    // 'C'            0b0000001100111001
    0x104F,    // 'D'            0b0001000001001111
    0x0339,    // 'E'            0b0000001100111001
    0x0331,    // 'F'            0b0000001100110001
    0x023D,    // 'G'            0b0000001000111101
    0x0336,    // 'H'            0b0000001100110110
    0x1040,    // 'I'            0b0001000001000000
    0x001E,    // 'J'            0b0000000000011110
    0x05B0,    // 'K'            0b0000010110110000
    0x0038,    // 'L'            0b0000000000111000
    0x20B6,    // 'M'            0b0010000010110110
    0x2436,    // 'N'            0b0010010000110110
    0x003F,    // 'O'            0b0000000000111111
    0x0333,    // 'P'            0b0000001100110011
    0x443F,    // 'Q'            0b0100010000111111
    0x0733,    // 'R'            0b0000011100110011
    0x032D,    // 'S'            0b0000001100101101
    0x1063,    // 'T'            0b0001000001100011
    0x003E,    // 'U'            0b0000000000111110
    0x08B0,    // 'V'            0b0000100010110000
    0x0C36,    // 'W'            0b0000110000110110
    0x2C80,    // 'X'            0b0010110010000000
    0x3080,    // 'Y'            0b0011000010000000
    0x0889,    // 'Z'            0b0000100010001001
    0x0039,    // '['            0b0000000000111001
    0x2400,    // '\'            0b0000100010000000
    0x000F,    // ']'            0b0000000000001111
    0x0081,    // '^'            0b0000000010000001
    0x0008,    // '_'            0b0000000000001000
};

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */


/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __ALPHANUMR_DRV_SPI__

void alphanumr_spiDriverInit(T_ALPHANUMR_P gpioObj, T_ALPHANUMR_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet(0);
    hal_gpio_rstSet(0);
    hal_gpio_intSet(1);
    hal_gpio_pwmSet(1);
}

#endif
#ifdef   __ALPHANUMR_DRV_I2C__

void alphanumr_i2cDriverInit(T_ALPHANUMR_P gpioObj, T_ALPHANUMR_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __ALPHANUMR_DRV_UART__

void alphanumr_uartDriverInit(T_ALPHANUMR_P gpioObj, T_ALPHANUMR_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif


/* ----------------------------------------------------------- IMPLEMENTATION */

/* Set display time */
void alphanumr_setDisplayTime( uint16_t delayDisplayShow )
{
    _ALPHANUMR_SPEED = delayDisplayShow / 20;
}

/* Generic data write function */
void alphanumr_writeDisplay(uint16_t leftDisplay, uint16_t rightDisplay)
{
    for ( _ALPHANUMR_COUNTER = 0; _ALPHANUMR_COUNTER < _ALPHANUMR_SPEED; _ALPHANUMR_COUNTER++ )
    {
        uint8_t buffer[ 4 ];
        buffer[ 0 ] = rightDisplay >> 8;
        buffer[ 1 ] = rightDisplay & 0xFF;
        buffer[ 2 ] = leftDisplay >> 8;
        buffer[ 3 ] = leftDisplay & 0xFF;

        hal_gpio_csSet( 0 );
        
        hal_spiWrite( buffer, 4 );

        hal_gpio_csSet( 1 );
        hal_gpio_pwmSet( 0 );
        Delay_10ms();
        hal_gpio_pwmSet( 1 );

        hal_gpio_rstSet( 0 );
        hal_gpio_rstSet( 1 );
        hal_gpio_intSet( 0 );
        Delay_10ms();
        hal_gpio_intSet( 1 );

        hal_gpio_csSet( 0 );
        hal_gpio_csSet( 1 );
        hal_gpio_pwmSet( 0 );
        hal_gpio_pwmSet( 1 );
    }
}

/* Function write left and right character */
void alphanumr_writeCharacter( uint8_t leftCharacter, uint8_t rightCharacter )
{
    alphanumr_writeDisplay( alphanumr_getChar( leftCharacter ), alphanumr_getChar( rightCharacter ) );
}

/* Function write left and right number */
void alphanumr_writeNumber( uint8_t leftNumber, uint8_t rightNumber )
{
    alphanumr_writeDisplay( alphanumr_getNumber( leftNumber ), alphanumr_getNumber( rightNumber ) );
}

/* Function get char for writing on the display */
uint16_t alphanumr_getChar( uint8_t character )
{
    if ( ( character >= '-' ) && ( character <= '_' ) )
    {
        return _ALPHANUMR_CHAR_TABLE[ character - '-' ];
    }
    else
    {
        return -1;
    }
}

/* Function get number for writing on the display */
uint16_t alphanumr_getNumber( uint8_t number )
{
    if ( ( number >= 0 ) && ( number <= 9 ) )
    {
        return _ALPHANUMR_CHAR_TABLE[ number + 3 ];
    }
    else
    {
        return -1;
    }
}





/* -------------------------------------------------------------------------- */
/*
  __alphanumr_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */