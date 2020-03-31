
#include "timertwo.h"
#include "timerone.h"
#include "debug.h"

int getDistInCM(uint32_t duration) {
    return duration/(TWO * CONVERSION_FACTOR * 100);
}


/* Calculates distance and sends that data to the queue */
// timerHandle is the interrupt
void sensorCallback(Timer_Handle timerHandle) {

    static uint32_t prev_count, curr_count;

    if (GPIO_read(Board_GPIO9_Echo) == 1)
        prev_count = Timer_getCount(timer1);

    else {

        curr_count = Timer_getCount(timer1);
        int dist = getDistInCM(curr_count - prev_count); // Calculates distance

        sendSensorMsgToQ1(dist);  // sends message to queue
    }
}

void trigCallback(Timer_Handle timerHandle){

    GPIO_write(Board_GPIO8_TRIG, 1);
    GPIO_write(Board_GPIO8_TRIG, 0);
}

void initTimerTwo() {

    Timer_Params params2;
    Timer_Params_init(&params2);

    params2.period = TIMER2_PERIOD;
    params2.periodUnits = Timer_PERIOD_US;
    params2.timerMode = Timer_CONTINUOUS_CALLBACK;
    params2.timerCallback = trigCallback;       // activates the sensor trigger

    timer2 = Timer_open(Board_TIMER1, &params2);

    if (timer2 == NULL)
        fatalError(MAIN_TASK_DLOC_FAILED_TIMERTWO_OPEN);

    if (Timer_start(timer2) == Timer_STATUS_ERROR)
        fatalError(MAIN_TASK_DLOC_FAILED_TIMERTWO_START);
}

/* Assigns the sensorCallback function to GPIO 9*/
void initUSSensor() {

    GPIO_setCallback(Board_GPIO9_Echo, sensorCallback); // bind left sensor callback to echo (GPIO 9) pin interrupt
    GPIO_enableInt(Board_GPIO9_Echo);   // enable echo interrupt
}
