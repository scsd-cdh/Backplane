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
    system_status,
    health_check,
    temp_reading,
    telecom_acknowledge,
} appStatus;

enum Command
{
    SystemStatus = 0x01,
    HealthCheck = 0x02,
    Temperature = 0x03,
    TelecomAcknowledge = 0x06,
};

void init_App();

void startCountdownCounter();
void startCountdownAlarm();

void initializeI2C();
void suspendI2CInterrupts();
void resumeI2CInterrupts();
void commandHandler();

void run();


#endif /* APP_APP_H_ */
