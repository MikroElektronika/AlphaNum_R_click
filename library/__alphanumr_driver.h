/*
    __alphanumr_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __alphanumr_driver.h
@brief    AlphaNum_R Driver
@mainpage AlphaNum_R Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   ALPHANUMR
@brief      AlphaNum_R Click Driver
@{

| Global Library Prefix | **ALPHANUMR** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jun 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _ALPHANUMR_H_
#define _ALPHANUMR_H_

/** 
 * @macro T_ALPHANUMR_P
 * @brief Driver Abstract type 
 */
#define T_ALPHANUMR_P    const uint8_t*

/** @defgroup ALPHANUMR_COMPILE Compilation Config */              /** @{ */

   #define   __ALPHANUMR_DRV_SPI__                            /**<     @macro __ALPHANUMR_DRV_SPI__  @brief SPI driver selector */
//  #define   __ALPHANUMR_DRV_I2C__                            /**<     @macro __ALPHANUMR_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __ALPHANUMR_DRV_UART__                           /**<     @macro __ALPHANUMR_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup ALPHANUMR_VAR Variables */                           /** @{ */

const uint16_t _ALPHANUMR_CHAR_TABLE[ 52 ];

                                                                       /** @} */
/** @defgroup ALPHANUMR_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup ALPHANUMR_INIT Driver Initialization */              /** @{ */

#ifdef   __ALPHANUMR_DRV_SPI__
void alphanumr_spiDriverInit(T_ALPHANUMR_P gpioObj, T_ALPHANUMR_P spiObj);
#endif
#ifdef   __ALPHANUMR_DRV_I2C__
void alphanumr_i2cDriverInit(T_ALPHANUMR_P gpioObj, T_ALPHANUMR_P i2cObj, uint8_t slave);
#endif
#ifdef   __ALPHANUMR_DRV_UART__
void alphanumr_uartDriverInit(T_ALPHANUMR_P gpioObj, T_ALPHANUMR_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup ALPHANUMR_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Function set display time
 *
 * @param[in] delayDisplayShow Display time [ ms ]
 *
 * Function set display time
 */
void alphanumr_setDisplayTime( uint16_t delayDisplayShow );

/**
 * @brief Generic data write function
 *
 * @param[in] leftDisplay Data to write on left display
 *
 * @param[in] rightDisplay Data to write on right display
 *
 * @note Delay 20 ms
 *
 * Function write left and right data on display
 */
void alphanumr_writeDisplay(uint16_t leftDisplay, uint16_t rightDisplay);

/**
 * @brief Character write function
 *
 * @param[in] leftDisplay Character to write on left display
 *
 * @param[in] rightDisplay Character to write on right display
 *
 * Function write left and right character on display
 */
void alphanumr_writeCharacter( uint8_t leftCharacter, uint8_t rightCharacter );

/**
 * @brief Number write function
 *
 * @param[in] leftDisplay Number to write on left display
 *
 * @param[in] rightDisplay Number to write on right display
 *
 * Function write left and right number on display
 */
void alphanumr_writeNumber( uint8_t leftNumber, uint8_t rightNumber );

/**
 * @brief Function get char
 *
 * @param[in] simbol char to write
 *
 * Function get char for writing on the display
 */
uint16_t alphanumr_getChar( uint8_t character );
 
/**
 * @brief Function get number
 *
 * @param[in] number number to write
 *
 * Function get number for writing on the display
 */
uint16_t alphanumr_getNumber( uint8_t number );







                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_AlphaNum_R_STM.c
    @example Click_AlphaNum_R_TIVA.c
    @example Click_AlphaNum_R_CEC.c
    @example Click_AlphaNum_R_KINETIS.c
    @example Click_AlphaNum_R_MSP.c
    @example Click_AlphaNum_R_PIC.c
    @example Click_AlphaNum_R_PIC32.c
    @example Click_AlphaNum_R_DSPIC.c
    @example Click_AlphaNum_R_AVR.c
    @example Click_AlphaNum_R_FT90x.c
    @example Click_AlphaNum_R_STM.mbas
    @example Click_AlphaNum_R_TIVA.mbas
    @example Click_AlphaNum_R_CEC.mbas
    @example Click_AlphaNum_R_KINETIS.mbas
    @example Click_AlphaNum_R_MSP.mbas
    @example Click_AlphaNum_R_PIC.mbas
    @example Click_AlphaNum_R_PIC32.mbas
    @example Click_AlphaNum_R_DSPIC.mbas
    @example Click_AlphaNum_R_AVR.mbas
    @example Click_AlphaNum_R_FT90x.mbas
    @example Click_AlphaNum_R_STM.mpas
    @example Click_AlphaNum_R_TIVA.mpas
    @example Click_AlphaNum_R_CEC.mpas
    @example Click_AlphaNum_R_KINETIS.mpas
    @example Click_AlphaNum_R_MSP.mpas
    @example Click_AlphaNum_R_PIC.mpas
    @example Click_AlphaNum_R_PIC32.mpas
    @example Click_AlphaNum_R_DSPIC.mpas
    @example Click_AlphaNum_R_AVR.mpas
    @example Click_AlphaNum_R_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __alphanumr_driver.h

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