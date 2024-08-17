/*
 * App.c
 *
 *  Created on: Aug 10, 2024
 *      Author: Rowan
 */

#include <app/App.h>
#include <driverlib.h>

static volatile appStatus app;
static volatile int countdownMinutes;

void init_App(){
    app = timer_mode;       // Start in timer mode

}


void startCountdownAlarm() {

    Calendar currentTime;

    /*
    * Select Port J
    * Set Pin 4, 5 to input Primary Module Function, LFXT.
    */
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_PJ,
        GPIO_PIN4 + GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    //Initialize LFXT1
    CS_turnOnLFXT(
        CS_LFXT_DRIVE_3
        );

    //Setup for Calendar
    currentTime.Seconds    = 0x00;
    currentTime.Minutes    = 0x26;
    currentTime.Hours      = 0x13;
    currentTime.DayOfWeek  = 0x03;
    currentTime.DayOfMonth = 0x20;
    currentTime.Month      = 0x07;
    currentTime.Year       = 0x2011;

    //Initialize Calendar Mode of RTC
    RTC_B_initCalendar(RTC_B_BASE, &currentTime, RTC_B_FORMAT_BCD);

    //Setup Calendar Alarm for 30 minutes after start.
    RTC_B_configureCalendarAlarmParam param = {0};
    param.minutesAlarm      = 0x27;  // Currently set to 1 minute for testing
    param.hoursAlarm        = 0x13;
    param.dayOfWeekAlarm    = 0x03;
    param.dayOfMonthAlarm   = 0x20;
    RTC_B_configureCalendarAlarm(RTC_B_BASE, &param);

    RTC_B_clearInterrupt(RTC_B_BASE,
        RTC_B_CLOCK_READ_READY_INTERRUPT +
        RTC_B_TIME_EVENT_INTERRUPT +
        RTC_B_CLOCK_ALARM_INTERRUPT
        );
    //Enable interrupt for RTC Ready Status, which asserts when the RTC
    //Calendar registers are ready to read.
    //Also, enable interrupts for the Calendar alarm and Calendar event.
    RTC_B_enableInterrupt(RTC_B_BASE,
        RTC_B_CLOCK_READ_READY_INTERRUPT +
        RTC_B_TIME_EVENT_INTERRUPT +
        RTC_B_CLOCK_ALARM_INTERRUPT
        );

    //Start RTC Clock
    RTC_B_startClock(RTC_B_BASE);

    //Enter low power mode with interrupts enabled
    __bis_SR_register(LPM0_bits + GIE);

    __no_operation();

}

/*ISR that maintains LPM until 30 minutes has passed*/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_B_ISR (void)
{
    switch (__even_in_range(RTCIV,16)){
        case 2:     //RTCRDYIFG, triggered every second
            break;
        case 4:     //RTCEVIFG, triggered every minute
            break;
        case 6:     //RTCAIFG, triggers at set alarm
            // Disable and clear interrupts
            RTC_B_disableInterrupt(RTC_B_BASE,
                RTC_B_CLOCK_READ_READY_INTERRUPT +
                RTC_B_TIME_EVENT_INTERRUPT +
                RTC_B_CLOCK_ALARM_INTERRUPT
                );
            RTC_B_clearInterrupt(RTC_B_BASE,
                RTC_B_CLOCK_READ_READY_INTERRUPT +
                RTC_B_TIME_EVENT_INTERRUPT +
                RTC_B_CLOCK_ALARM_INTERRUPT
                );
            // Exit low power mode to resume run()
            __bic_SR_register_on_exit(LPM0_bits);
            // Switch to idle mode
            app = idle;
            break;
        default: break;
    }
}


void run(){

    switch(app){
        /* Mode after power-on when pin is pulled, count-down before switching to idle state */
        case timer_mode:
            /* Ensure LED1 is only on in idle mode */
            GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);

            /* Starts countdown using an alarm set for 30 minutes after power-on */
            startCountdownAlarm();

            break;
        /* Mode after timer_mode is up */
        case idle:
            /* Turn on LED to simulate idle state */
            GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
            break;
        case power_cdh:
            /* Ensure LED1 is only on in idle mode */
            GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
            break;
        case temp_reading:
            /* Ensure LED1 is only on in idle mode */
            GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
            break;

    }

}
