
#include "timertwo.h"
#include "timerone.h"
#include "debug.h"
//#include "sensor_state.h"




void sensorLeftCallback(Timer_Handle timerHandle)
{
    if (GPIO_read(Board_GPIO9_LeftEcho) == 1)
    {
        timerLeftCountPrev = Timer_getCount(timer1);
    }
    else
    {
        timerLeftCountNow = Timer_getCount(timer1);
        int duration = timerLeftCountNow - timerLeftCountPrev;

        sendSensorMsgToQ1(getDistInCM(duration), 'L');
    }
}

void sensorRightCallback(Timer_Handle timerHandle)
{
    if (GPIO_read(Board_GPIO10_RightEcho) == 1)
    {
        timerRightCountPrev = Timer_getCount(timer1);
    }
    else
    {
        timerRightCountNow = Timer_getCount(timer1);
        int duration = timerRightCountNow - timerRightCountPrev;

        sendSensorMsgToQ1(getDistInCM(duration), "R");
    }
}


void timer10Callback(Timer_Handle timerHandle)
{
    //do Nothing
    GPIO_write(Board_GPIO8_TRIG, 1);

    GPIO_write(Board_GPIO8_TRIG, 0);
}

int getDistInCM(uint32_t duration) {
    return duration/(TWO * CONVERSION_FACTOR * 100);
}

void initTimerTwo()
{
    Timer_Params params2;
    Timer_Params_init(&params2);
    params2.period = TIMER2_PERIOD;
    params2.periodUnits = Timer_PERIOD_US;
    params2.timerMode = Timer_CONTINUOUS_CALLBACK;
    params2.timerCallback = timer10Callback;

    timer2 = Timer_open(Board_TIMER1, &params2);

    if (timer2 == NULL)
        fatalError(MAIN_TASK_DLOC_FAILED_TIMERTWO_OPEN);

    if (Timer_start(timer2) == Timer_STATUS_ERROR)
        fatalError(MAIN_TASK_DLOC_FAILED_TIMERTWO_START);

}

void initUSSensor()
{
    GPIO_setConfig(Board_GPIO9_LeftEcho, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_BOTH_EDGES);
    GPIO_setCallback(Board_GPIO9_LeftEcho, sensorLeftCallback);
    GPIO_enableInt(Board_GPIO9_LeftEcho);

    GPIO_setConfig(Board_GPIO10_RightEcho, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_BOTH_EDGES);
    GPIO_setCallback(Board_GPIO10_RightEcho, sensorRightCallback);
    GPIO_enableInt(Board_GPIO10_RightEcho);
}
