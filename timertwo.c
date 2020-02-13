/*
 * timertwo.c
 *
 *  Created on: Feb 5, 2020
 *      Author: Brandon
 */

#include "timertwo.h"

void TimerTwo_init()
{
    Timer_Params params;
    Timer_Params_init(&params);

    params.period = TIMERTWO_PERIOD;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timer75Callback;

    TimerTwo = Timer_open(Board_TIMER1, &params);

    if (TimerTwo == NULL)
    {
        dbgHaltAll(DLOC_TIMETWO_FAILED_INIT);
    }

    if (Timer_start(TimerTwo) == Timer_STATUS_ERROR)
    {
        dbgHaltAll(DLOC_TIMERTWO_FAILED_START);

    }
}

void IRSensor_init()
{
    ADC_Params adcParams;
    ADC_Params_init(&adcParams);
    adc = ADC_open(Board_ADC0, &adcParams);
}

void timer75Callback(Timer_Handle myHandle)
{
    dbgOutputLoc(DLOC_ENTER_TIMERTWO_ISR);
    int_fast16_t res;

    dbgOutputLoc(DLOC_TIMERTWO_ADC_CONV_START);
    res = ADC_convert(adc, &adcValue0);
    dbgOutputLoc(DLOC_TIMERTWO_ADC_CONV_END);

    if(res == ADC_STATUS_SUCCESS)
    {
        adcValue0MicroVolt = ADC_convertToMicroVolts(adc, adcValue0);
    }
    else
    {
        dbgHaltAll(DLOC_TIMERTWO_ADC_FAILED);
    }

    int convertedValue = convertToMM();
    sendSensorMsgToQ1(convertedValue);

    dbgOutputLoc(DLOC_LEAVE_TIMERTWO_ISR);


}

int convertToMM()
{
    double range;
    range = ((double)adcValue0MicroVolt)/1000000;
    range = pow(range, -1.15);
    range = 10.16*range;
    if(range < 0)
    {
        return 0;
    }
    else
    {
        return (int)(range*10);
    }
}
