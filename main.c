#include<msp430.h>
#include<msp430fr5969.h>
#include "Drivers/driverlib.h"

void main(){

    WDT_A_hold(WDT_A_BASE);     // Stop watchdog
    PMM_unlockLPM5();           // Disable the GPIO power-on default high-impedance mode
    
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN6);

    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN6);

}