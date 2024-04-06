/*
 * App.h
 *
 *  Created on: Apr 6, 2024
 *      Author: Amir
 */

#ifndef APP_APP_H_
#define APP_APP_H_


typedef enum
{
    timer_mode,
    power_cdh,
    idle,
    temp_reading
} appStatus;


void init_App();

void run();


#endif /* APP_APP_H_ */
