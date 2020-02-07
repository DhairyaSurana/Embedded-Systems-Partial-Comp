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
        dbgOutputLoc(DLOC_TIMETWO_FAILED_INIT);
    }

    if (Timer_start(TimerTwo) == Timer_STATUS_ERROR)
    {
        dbgOutputLoc(DLOC_TIMERTWO_FAILED_START);

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
    int reading = ADC_convert(adc, &adcValue0);

    if(reading == ADC_STATUS_SUCCESS)
    {
        adcValue0MicroVolt = ADC_convertToMicroVolts(adc, adcValue0);
    }
    else
    {
        // debug error
    }

    int convertedValue = convertToMM();
    sendSensorMsgToQ1(convertedValue);
}

int convertToMM()
{
    double range;
    range = ((double)adcValue0MicroVolt)/MV_V_FACTOR;
    range = RANGE_NUMERATOR/(range+RANGE_V_OFFSET)-RANGE_OFFSET;
    if(range < ZERO)
    {
        return INVALID_MEASUREMENT;
    }
    else
    {
        return (int)range;
    }
}
