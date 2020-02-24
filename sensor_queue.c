#include "sensor_queue.h"


void message_init(message *msg)
{
    msg->type = no_type;
    msg->value.sensor_val = ZERO;
    msg->value.time_val = ZERO;
}

void MQ_init()
{
    sensor = xQueueCreate(QUEUE_LEN, sizeof(message));
}

bool sendToQueue(message m)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(sensor,
                                                &m, &xHigherPriorityTaskWoken);
    bool success =  (pdPASS == result);
    if(!success)
    {
        dbgHaltAll(DLOC_QUEUE_SEND_FAIL);
    }
    dbgOutputLoc(DLOC_QUEUE_SEND_SUCCESS);
    return true;
}

bool sendTimeMsgToQ1(unsigned int timeVal)
{
    dbgOutputLoc(DLOC_BEFORE_QUEUE_TIME);
    message m = {
           .type=time_val,
           .value.sensor_val=0,
           .value.time_val=timeVal
    };

    dbgOutputLoc(DLOC_QUEUE_SENDING_MSG);

    return sendToQueue(m);
}

bool sendSensorMsgToQ1(int mmDist)
{
    dbgOutputLoc(DLOC_BEFORE_QUEUE_SENSOR);
    message m = {
         .type=sensor_val,
         .value.sensor_val=mmDist,
         .value.time_val=0
    };

    dbgOutputLoc(DLOC_QUEUE_SENDING_MSG);
    return sendToQueue(m);
}


message readMsgFromQ1()
{
    message m = {
          .type=no_type,
          .value.sensor_val=0,
          .value.time_val=0
    };

    dbgOutputLoc(DLOC_BEFORE_QUEUE_READ);
    xQueueReceive(sensor, &m, portMAX_DELAY);
    dbgOutputLoc(DLOC_AFTER_QUEUE_READ);
    return m;
}
