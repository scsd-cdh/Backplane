/*
 * App.c
 *
 *  Created on: Apr 6, 2024
 *      Author: Amir
 */

#include <app/App.h>
#include <driverlib.h>

static volatile appStatus app;

void init_App(){

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

    app = timer_mode;

}

void run(){

    switch(app){
        case timer_mode:
            break;
        case idle:
            break;
        case power_cdh:
            break;
        case temp_reading:
            break;

    }
}
