#include "sensor_state.h"
#include "debug.h"
#include <stdio.h>
#include <strings.h>


int StateMachine(status_t *curStatus, int timeInc, int sensorVal)
{
    int sensorAvg;
    char uartOut[33];
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


                    sprintf(uartOut,"Sensor= %d Count= %d  ",sensorAvg, curStatus->sensorCount);
                    int i = 0;
                    for (i = 0; i < strlen(uartOut); i++)
                    {
                        dbgUARTVal(uartOut[i]);
                    }
                    curStatus->sensorTotal = 0;
                    curStatus->sensorCount = 0;
                    curStatus->curState = WaitingForTime2;
                }
                break;
            case WaitingForTime2:
                dbgOutputLoc(DLOC_STATE_TWO);
                if(timeInc == 0)
                {
                    curStatus->sensorTotal += sensorVal;
                    curStatus->sensorCount++;
                }

                if(timeInc>0){
                    curStatus->curTime+=timeInc;
                    sensorAvg = curStatus->sensorTotal/curStatus->sensorCount;


                    sprintf(uartOut,"Sensor= %d Count= %d  ",sensorAvg, curStatus->sensorCount);
                    int i = 0;
                    for (i = 0; i < strlen(uartOut); i++)
                    {
                        dbgUARTVal(uartOut[i]);
                    }
                    curStatus->sensorTotal = 0;
                    curStatus->sensorCount = 0;
                    curStatus->curState = WaitingForTime3;
                }
                break;
            case WaitingForTime3:
                dbgOutputLoc(DLOC_STATE_THREE);
                if(timeInc == 0)
                {
                    curStatus->sensorTotal += sensorVal;
                    curStatus->sensorCount++;
                }

                if(timeInc>0){
                    curStatus->curTime+=timeInc;
                    sensorAvg = curStatus->sensorTotal/curStatus->sensorCount;
                    sprintf(uartOut,"Sensor= %d Count= %d  ",sensorAvg, curStatus->sensorCount);
                    int i = 0;
                    for (i = 0; i < strlen(uartOut); i++)
                    {
                        dbgUARTVal(uartOut[i]);

                    }
                    sprintf(uartOut,"CurTime= %d ", curStatus->curTime/1000);
                    i = 0;
                    for (i = 0; i < strlen(uartOut); i++)
                    {
                        dbgUARTVal(uartOut[i]);
                    }
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
