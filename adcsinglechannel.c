/*
 *  ======== adcsinglechannel.c ========
 */
// Test 1 2 3
#include <stdint.h>
#include <stddef.h>

/* POSIX Header files */
#include <pthread.h>

/* Example/Board Header files */
#include "Board.h"

#include "debug.h"

#include "sensor_queue.h"
#include "sensor_state.h"

#include "timerone.h"
#include "timertwo.h"


/*
 *  ======== mainThread ========
 */

void recieveDataTask (void *vParameters) {

    sensor_struct curr_sens_data;
    sensorStructInit(&curr_sens_data);  // holds the current sensor data

    while (1){

           data_struct new_sens_msg = readMsgFromQ1(); // reads message from queue (non-blocking)

           if (new_sens_msg.type != no_data)
               printSensorInfo(&curr_sens_data, &new_sens_msg);    // updates the current data with the new data from the message and prints out values
    }
}


void *mainThread(void *arg0){

    initGPIO();
    initUART();

    initMessageQueue(); // sets up queue
    initUSSensor();     // sends sensor data (nonblocking) to queue via callback within this function


    /* Initialize timers */
    Timer_init();
    initTimerOne();
    initTimerTwo();

    xTaskCreate(recieveDataTask, "recieveDataTask", 1000, NULL, 1, NULL);
    vTaskStartScheduler();

    return(NULL);
}
