/*
 *  ======== adcsinglechannel.c ========
 */
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

    initMessageQueue();
    initUSSensor();

    sensor_struct state;
    sensorStructInit(&state);

    data_struct sens_msg;


    Timer_init();
    initTimerOne();
    initTimerTwo();


    while (1){

        sens_msg = readMsgFromQ1();

        if (sens_msg.type != no_data)
            printSensorInfo(&state, &sens_msg);
    }
}


void *mainThread(void *arg0){

    xTaskCreate(vMainTask, "MainTask", 1000, NULL, 1, NULL);
    vTaskStartScheduler();

    return(NULL);
}
