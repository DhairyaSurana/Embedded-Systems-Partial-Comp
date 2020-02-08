#include "sensor_queue.h"

// testing 1 2 3

void message_init(message *msg)
{
    (*msg).type = no_type;
    (*msg).value.sensor_val = ZERO;
    (*msg).value.time_val = ZERO;

}
void MQ_init()
{
    sensor = xQueueCreate(QUEUE_LEN, sizeof(message));
}


int sendToQueue(message m)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(sensor,
                                                &m, &xHigherPriorityTaskWoken);
    return  (pdPASS == result);
}

int sendTimeMsgToQ1(unsigned int timeVal)
{

    message m = {
           .type=time_val,
           .value.sensor_val=0,
           .value.time_val=timeVal
    };

    int check = sendToQueue(m);
    return check;
}

int sendSensorMsgToQ1(int mmDist)
{

    message m = {
         .type=sensor_val,
         .value.sensor_val=mmDist,
         .value.time_val=0
    };

    int check = sendToQueue(m);
    return check;
}


message readMsgFromQ1()
{

    message m = {
          .type=no_type,
          .value.sensor_val=0,
          .value.time_val=0
    };

    xQueueReceive(sensor, &m, portMAX_DELAY);

    return m;
}
