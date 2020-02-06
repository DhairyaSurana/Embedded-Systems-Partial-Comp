/*
 *
 *  sensor_queue.h
 *
 *  Created on: Feb 5, 2020
 *  Author: Dhairya Surana
 */

#include <FreeRTOS.h>
#include <queue.h>

#define QUEUE_LEN 120
#define QUEUE_ITEM_SIZE 8

typedef enum data_t {time, sensor} data_t; /*If there is an error the data type will be error*/

typedef struct data{
                    unsigned int time_val;
                    int sensor_val;
        } data;

typedef struct message {
                    data_t type; // First 4 bytes
                    data value; // Second 4 bytes
         } message;

/* Global Handle for the sensor queue */
QueueHandle_t sensor_queue_handle;

/* Creates a new queue */
void initMessageQueue();

/* Writes message to queue */
int sendToQueue(message m);

/* Sends a time value to a queue. */
int sendTimeMsgToQ1(unsigned int timeVal);

/* Sends a sensor value to a queue. */
int sendSensorMsgToQ1(int mmDist);

/* Reads a message from a queue */
message readMsgFromQ1();
