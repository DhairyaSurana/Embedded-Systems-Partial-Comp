#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


/* POSIX Header files */
#include <pthread.h>

/* Driver Header files */
#include <ti/drivers/ADC.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/GPIO.h>

#include "Board.h"
#include "timerone.h"
#include "timertwo.h"
#include "sensor_state.h"
#include "sensor_queue.h"
#include "debug.h"
#include "pwm_ultrasonic.h"

#include "FreeRTOS.h"
#include "task.h"

#include <strings.h>

// include all of our header files


/* ADC sample count */
#define ADC_SAMPLE_COUNT  (10)

#define THREADSTACKSIZE   (768)


/*
 *  ======== mainThread ========
 */


void vTask1 (void *pvParameters){

    for(;;){

        ADC_init();
        GPIO_init();
        UART_init();
        Timer_init();

        MQ_init();
        DebugGPIO_init();
        initUART();
        IRSensor_init();
        init_pwm();

        TimerOne_init();
        TimerTwo_init();

        status_t status;
        status_init(&status);

        message msg;
        message_init(&msg);

        dbgOutputLoc(DLOC_BEFORE_WHILE);

        int fail = 0;//set fail to value 1 or greater to activate fail

        while(1){

            dbgOutputLoc(DLOC_BEFORE_QUEUE_READ);
            msg = readMsgFromQ1();
            dbgOutputLoc(DLOC_AFTER_QUEUE_READ);

            if(msg.type != no_type)
                StateMachine(&status, msg.value.time_val, msg.value.sensor_val);

            if(fail > 0) {

                if(fail < 50)//fails after specified loops
                    fail++;
                else
                    dbgHaltAll(DLOC_FATAL_ERROR);

            }
        }
    }


}

void *mainThread(void *arg0)
{

    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    vTaskStartScheduler();

    return(NULL);
}
