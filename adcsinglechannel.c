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
void vMainTask (void *pvParameters){

    initGPIO();
    initUART();

    initMessageQueue(); // sets up queue
    initUSSensor();     // sends sensor data (nonblocking) to queue via callback within this function

    sensor_struct curr_sens_data;
    sensorStructInit(&curr_sens_data);  // holds the current sensor data

    /* Initialize timers */
    Timer_init();
    initTimerOne();
    initTimerTwo();

    while (1){

        data_struct new_sens_msg = readMsgFromQ1(); // reads message from queue (non-blocking)

        if (new_sens_msg.type != no_data)
            printSensorInfo(&curr_sens_data, &new_sens_msg);    // updates the current data with the new data from the message and prints out values
    }
}


void *mainThread(void *arg0){

    xTaskCreate(vMainTask, "MainTask", 1000, NULL, 1, NULL);
    vTaskStartScheduler();

    return(NULL);
}
