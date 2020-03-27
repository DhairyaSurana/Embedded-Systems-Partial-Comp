#include "sensor_state.h"
#include "debug.h"


void printSensorInfo(sensor_struct *sensor, data_struct *sens_msg)
{
    /* This is where we get the value of the sensor. */

    timeVal_t timeInc = sens_msg->value.time_val;
    sensorVal_t sensorVal = sens_msg->value.sensor_val;
    char direction = sens_msg->direction;

    if (timeInc == 0) {
         sensor->sensorTotal += sensorVal;
         sensor->sensorCount++;
    }

    else {

         sensor->curTime += timeInc;
         int sensorAvg = sensor->sensorTotal/sensor->sensorCount;

         char sensorInfoPrintToUART[50] = "";
         sprintf(sensorInfoPrintToUART, "%c Distance: %d cm\r\n", direction, sensorAvg);

         int i;
         for (i = 0; i < sizeof(sensorInfoPrintToUART) / sizeof(char); i++)
             dbgUARTVal(sensorInfoPrintToUART[i]);

         sensor->sensorTotal = 0;
         sensor->sensorCount = 0;

     }

}

void sensorStructInit(sensor_struct *state){

    state->curTime = 0;
    state->sensorTotal = 0;
    state->sensorCount = 0;

}
