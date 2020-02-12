/*
 * timerone.c
 *
 *  Created on: Feb 5, 2020
 *      Author: Brandon
 */

#include "timerone.h"

#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "Board.h"

void TimerOne_init()
{
    Timer_Params params;
    Timer_Params_init(&params);

    params.period = TIMERONE_PERIOD;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerSecondCallback;

   TimerOne = Timer_open(Board_TIMER0, &params);

    if (TimerOne == NULL)
    {
        dbgHaltAll(DLOC_TIMERONE_FAILED_INIT);
    }

    if (Timer_start(TimerOne) == Timer_STATUS_ERROR)
    {
        dbgHaltAll(DLOC_TIMERONE_FAILED_START);
    }


}

void timerSecondCallback(Timer_Handle myHandle)
{

    dbgOutputLoc(DLOC_ENTER_TIMERONE_ISR);
    uint32_t value = Timer_getCount(myHandle);

    //dbgOutputLoc(DLOC_TIMERONE_BEFORE_QUEUE);
    sendTimeMsgToQ1(value);
    ///dbgOutputLoc(DLOC_TIMERONE_AFTER_QUEUE);
    dbgOutputLoc(DLOC_LEAVE_TIMERONE_ISR);

}
