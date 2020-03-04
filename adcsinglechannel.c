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

    data_struct sens_msg = {.type=no_data, .value.sensor_val=0,
                            .value.time_val=0, .direction=""};


    Timer_init();
    initTimerOne();
    initTimerTwo();


    while (1){

        sens_msg = readMsgFromQ1();

        if (sens_msg.type != no_data)
            StateMachine(&state, sens_msg.value.time_val, sens_msg.value.sensor_val, sens_msg.direction);

    }
}


void *mainThread(void *arg0){

    xTaskCreate(vMainTask, "MainTask", 1000, NULL, 1, NULL);
    vTaskStartScheduler();

    return(NULL);
}
