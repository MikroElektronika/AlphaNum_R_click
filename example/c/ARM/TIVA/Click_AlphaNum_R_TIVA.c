/*
Example for AlphaNum_R Click

    Date          : Jun 2018.
    Author        : Nenad Filipovic

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes peripherals and set pins.
- Application Initialization - Initializes SPI driver and performs device configuration.
- Application Task - (code snippet) Write text, special symbols and number on 14-segment display.


*/

#include "Click_AlphaNum_R_types.h"
#include "Click_AlphaNum_R_config.h"

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_OUTPUT );

    mikrobus_spiInit( _MIKROBUS1, &_ALPHANUMR_SPI_CFG[0] );

    Delay_100ms();
}

void applicationInit()
{
    alphanumr_spiDriverInit( (T_ALPHANUMR_P)&_MIKROBUS1_GPIO, (T_ALPHANUMR_P)&_MIKROBUS1_SPI );

}

void applicationTask()
{
    alphanumr_setDisplayTime( 1000 );

    alphanumr_writeCharacter( 'M', 'E' );

    alphanumr_writeCharacter( '@', '?' );

    alphanumr_writeNumber( 0,  1 );
    alphanumr_writeNumber( 1,  2 );
    alphanumr_writeNumber( 2,  3 );
    alphanumr_writeNumber( 3,  4 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}