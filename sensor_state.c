#include "sensor_state.h"
#include "debug.h"

int FSM(sensor_struct *externalState, timeVal_t timeInc, sensorVal_t sensorVal, char direction)
{ /* This is where we get the value of the sensor. */

    switch ((*externalState).curState)
    {
    case waiting_for_time1:
    case waiting_for_time2:
    case waiting_for_time3:
    case waiting_for_time4:
        if (timeInc == 0)
        {
            (*externalState).sensorTotal += sensorVal;
            (*externalState).sensorCount++;
        }
        if (timeInc > 0)
        {
            (*externalState).curTime += timeInc;
            (*externalState).sensorAvg = (*externalState).sensorTotal
                    / (*externalState).sensorCount;
            char sensorInfoPrintToUART[50] = "";
            int sensoravg = (*externalState).sensorAvg;
            int sensorcount = (*externalState).sensorCount;
            sprintf(sensorInfoPrintToUART, "%c Sensor= %d \r\n", direction, sensoravg);//, sensorcount);
            //sensorInfoPrintToUART = "";
            //sprintf(sensorInfoPrintToUART, "Right Sensor= %d \r\n", sensoravg);
            int i; /* Print to UART  */
            for (i = 0; i < sizeof(sensorInfoPrintToUART) / sizeof(sensorInfoPrintToUART[0]); i++)
            {
                dbgUARTVal(sensorInfoPrintToUART[i]);
            }
            (*externalState).sensorTotal = 0;
            (*externalState).sensorCount = 0;
            if((*externalState).curState == waiting_for_time4)
            {
                char sensorInfoPrintToUART[50] = "";
                int curtime = ((*externalState).curTime/100000);
                //sprintf(sensorInfoPrintToUART, "CurTime= %d\r\n", curtime);

                int i;
                for (i = 0;i< sizeof(sensorInfoPrintToUART)/ sizeof(sensorInfoPrintToUART[0]); i++)
                {
                    dbgUARTVal(sensorInfoPrintToUART[i]);
                }
            }
        }
        /* Takes the current state and finds the value of the next state */
        (*externalState).curState = (((*externalState).curState+1)%5);
        if((*externalState).curState == init)
        {
            (*externalState).curState += 1;
        }
        break;

    default:
        return -1;
    }
    return 1;
}

sensor_struct sensorStructInit(sensor_struct *state)
{

    (*state).curTime = 0;
    (*state).curState = waiting_for_time1;
    (*state).sensorTotal = 0;
    (*state).sensorCount = 0;

    return *state;
} /* Takes care of the Init state.  */
