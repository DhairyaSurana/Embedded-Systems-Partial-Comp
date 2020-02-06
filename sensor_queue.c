/*
 *
 *  sensor_queue.c
 *
 *  Created on: Feb 5, 2020
 *  Author: Dhairya Surana
 */

#include "sensor_queue.h"

void initMessageQueue(){
    sensor_queue_handle = xQueueCreate(QUEUE_LEN, sizeof(message));
}


int sendToQueue(message m){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(sensor_queue_handle,
                                                &m, &xHigherPriorityTaskWoken);
    return  (pdPASS == result);
}

int sendTimeMsgToQ1(unsigned int timeVal){

    message m = {
           .type=time,
           .value.sensor_val=0,
           .value.time_val=timeVal
    };

    return sendToQueue(m);
}

/* Might be blocking based on the Project Specifications.*/
int sendSensorMsgToQ1(int mmDist){

    message m = {
         .type=sensor,
         .value.sensor_val=mmDist,
         .value.time_val=0
    };

    return sendToQueue(m);
}


message readMsgFromQ1(){

    message m = {
          .type=NULL,
          .value.sensor_val=0,
          .value.time_val=0
    };

    xQueueReceive(sensor_queue_handle, &m, portMAX_DELAY);

    return m;
}
