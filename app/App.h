/*
 * App.h
 *
 *  Created on: Aug 10, 2024
 *      Author: Rowan
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

void startCountdownCounter();
void startCountdownAlarm();

void run();


#endif /* APP_APP_H_ */
