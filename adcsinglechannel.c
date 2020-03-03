/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== adcsinglechannel.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* POSIX Header files */
#include <pthread.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/PWM.h>

/* Example/Board Header files */
#include "Board.h"

#include "sensor_queue.h"
#include "sensor_state.h"

#include "timerone.h"
#include "timertwo.h"


/*
 *  ======== mainThread ========
 */
void vMainTask (void *pvParameters){

    initMessageQueue();

    GPIO_init();
    UART_init();
    initSharpIRSensor();
    initUART();

    sensor_struct state;
    sensorStructInit(&state);

    data_struct sens_msg = {.type=no_data, .value.sensor_val=0,
                            .value.time_val=0, .direction=""};


    Timer_init();
    initTimerOne();
    initTimerTwo();


    while (1)
    {

        sens_msg = readMsgFromQ1();

        if (sens_msg.type != no_data)
            FSM(&state, sens_msg.value.time_val, sens_msg.value.sensor_val, sens_msg.direction);

    }
}


void *mainThread(void *arg0){

    xTaskCreate(vMainTask, "MainTask", 1000, NULL, 1, NULL);
    vTaskStartScheduler();

    return(NULL);
}
