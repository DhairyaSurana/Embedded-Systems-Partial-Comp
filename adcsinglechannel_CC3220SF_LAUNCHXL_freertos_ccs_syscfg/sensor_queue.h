#ifndef SENSOR_QUEUE_H_
#define SENSOR_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>

#define QUEUE_LEN       120
#define QUEUE_ITEM_SIZE 8
#define ZERO            0

typedef enum data_t {no_type, time_val, sensor_val} data_t;

typedef struct data{
                    unsigned int time_val;
                    int sensor_val;
        } data;

typedef struct message {
                    data_t type;
                    data value;
         } message;

QueueHandle_t sensor;

void message_init(message *msg);

void MQ_init();

int sendToQueue(message m);

int sendTimeMsgToQ1(unsigned int timeVal);

int sendSensorMsgToQ1(int mmDist);

message readMsgFromQ1();

#endif /* SENSOR_QUEUE_H_ */
