#include "sensor_state.h"
#include "debug.h"
#include <stdio.h>
#include <strings.h>

static void printTimeInfo(char * uart, int time) {

    sprintf(uart, "CurTime = %d ", time);

    int i;
    for (i = 0; i < strlen(uart); i++)
        dbgUARTVal(uart[i]);
}

static void printSensorInfo(char * uart, int avg, int count) {

    sprintf(uart, "(Sensor = %d, Count = %d) ", avg, count);

    int i;
    for (i = 0; i < strlen(uart); i++)
        dbgUARTVal(uart[i]);

}

int StateMachine(status_t *curStatus, int timeInc, int sensorVal)
{
    int sensorAvg;
    char uartOut[33] = "";
    switch (curStatus->curState) {

            case Init:

                dbgOutputLoc(DLOC_STATE_INIT);
                curStatus->curTime = 0;
                curStatus->curState = WaitingForTime1;
                break;

            case WaitingForTime1:

                dbgOutputLoc(DLOC_STATE_ONE);

                if(timeInc == 0)
                {
                    curStatus->sensorTotal += sensorVal;
                    curStatus->sensorCount++;
                }

                if(timeInc>0){

                    curStatus->curTime+=timeInc;
                    sensorAvg = curStatus->sensorTotal/curStatus->sensorCount;

                    printSensorInfo(uartOut, sensorAvg, curStatus->sensorCount);

                    curStatus->sensorTotal = 0;
                    curStatus->sensorCount = 0;
                    curStatus->curState = WaitingForTime2;
                }

                break;

            case WaitingForTime2:

                dbgOutputLoc(DLOC_STATE_TWO);

                if(timeInc == 0) {

                    curStatus->sensorTotal += sensorVal;
                    curStatus->sensorCount++;
                }

                if(timeInc>0){

                    curStatus->curTime+=timeInc;
                    sensorAvg = curStatus->sensorTotal/curStatus->sensorCount;

                    printSensorInfo(uartOut, sensorAvg, curStatus->sensorCount);

                    curStatus->sensorTotal = 0;
                    curStatus->sensorCount = 0;
                    curStatus->curState = WaitingForTime3;
                }

                break;

            case WaitingForTime3:

                dbgOutputLoc(DLOC_STATE_THREE);

                if(timeInc == 0){
                    curStatus->sensorTotal += sensorVal;
                    curStatus->sensorCount++;
                }

                if(timeInc>0){

                    curStatus->curTime+=timeInc;
                    sensorAvg = curStatus->sensorTotal/curStatus->sensorCount;

                    printSensorInfo(uartOut, sensorAvg, curStatus->sensorCount);
                    printTimeInfo(uartOut, curStatus->curTime/1000);

                    curStatus->sensorTotal = 0;
                    curStatus->sensorCount = 0;
                    curStatus->curState = WaitingForTime1;
                }

                break;

            default:
                return 0;//fail
    }


    dbgOutputLoc(DLOC_STATE_DONE);

    return 1;
}

void status_init(status_t *state)
{
     state->curState = Init;
     state->curTime = 0;
     state->sensorCount = 0;
     state->sensorTotal = 0;
}
