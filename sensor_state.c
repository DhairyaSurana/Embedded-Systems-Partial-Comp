#include "sensor_state.h"
#include "debug.h"

//static sensor_state getNextState(sensor_struct *externalState) {
//    return (externalState->curState+1)%5
//}

int StateMachine(sensor_struct *externalState, timeVal_t timeInc, sensorVal_t sensorVal, char direction)
{ /* This is where we get the value of the sensor. */

    switch (externalState->curState){

        case init:
        case waiting_for_time1:
        case waiting_for_time2:
        case waiting_for_time3:

            if (timeInc == 0)
            {
                externalState->sensorTotal += sensorVal;
                externalState->sensorCount++;
            }

            if (timeInc > 0){

                externalState->curTime += timeInc;
                int sensorAvg = externalState->sensorTotal/externalState->sensorCount;

                char sensorInfoPrintToUART[50] = "";
                sprintf(sensorInfoPrintToUART, " Distance: %d cm\r\n", sensorAvg);

                int i;
                for (i = 0; i < sizeof(sensorInfoPrintToUART) / sizeof(char); i++)
                    dbgUARTVal(sensorInfoPrintToUART[i]);

                externalState->sensorTotal = 0;
                externalState->sensorCount = 0;

            }

            // Finds the next state
            sensor_state curState = externalState->curState;
            externalState->curState = (curState == waiting_for_time3) ? init : curState++;

            break;

        default:
            return -1;  // Fail
        }
        return 1;   // Success
}

void sensorStructInit(sensor_struct *state){

    state->curTime = 0;
    state->curState = waiting_for_time1;
    state->sensorTotal = 0;
    state->sensorCount = 0;

}
