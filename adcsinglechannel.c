/*
 *
 * MODIFIED FROM:
 * adcsinglechannel.c
 *
 *  Created on: Feb 5, 2020
 *  Author: Brandon
 */
#include <stdint.h>
#include <stddef.h>

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

#include "FreeRTOS.h"
#include "task.h"

// include all of our header files


/* ADC sample count */
#define ADC_SAMPLE_COUNT  (10)

#define THREADSTACKSIZE   (768)


/*
 *  ======== mainThread ========
 */



//========================================================================================
// IMPORTANT DEBUG INFO
//
//  dbgOutputLoc relies on GPIO_init and DebugGPIO_init
//
//  dbgUARTStr relies on Timer_init, TimerOne_init, and TimerTwo_init
//========================================================================================


void vTask1 (void *pvParameters){

 const char *pcTaskName = "Task 1";
    volatile uint32_t u1;

    for(;;){
       //everything that was in the main goes here

        MQ_init();
           ADC_init();
          GPIO_init();
          DebugGPIO_init();
          UART_init();
          initUART();
          IRSensor_init();
          Timer_init();
          TimerOne_init();
          TimerTwo_init();

          status_t status;
          status_init(&status);

          message msg;
          message_init(&msg);

          dbgOutputLoc(DLOC_BEFORE_WHILE);


          while(1)
          {

              dbgOutputLoc(DLOC_WHILE_BEFORE_QUEUE_RECEIVE);
              msg = readMsgFromQ1();
              dbgOutputLoc(DLOC_WHILE_AFTER_QUEUE_RECEIVE);

              if(msg.type != no_type)
              {
                  StateMachine(&status, msg.value.time_val, msg.value.sensor_val);
              }
          }
    }
}

void *mainThread(void *arg0)
{

    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);

    vTaskStartScheduler();
//      MQ_init();
//     ADC_init();
//    GPIO_init();
//    DebugGPIO_init();
//    UART_init();
//    initUART();
//    IRSensor_init();
//    Timer_init();
//    TimerOne_init();
//    TimerTwo_init();
//
//    status_t status;
//    status_init(&status);
//
//    message msg;
//    message_init(&msg);
//
//    dbgOutputLoc(DLOC_BEFORE_WHILE);
//
//
//    while(1)
//    {
//
//        dbgOutputLoc(DLOC_WHILE_BEFORE_QUEUE_RECEIVE);
//        msg = readMsgFromQ1();
//        dbgOutputLoc(DLOC_WHILE_AFTER_QUEUE_RECEIVE);
//
//        if(msg.type != no_type)
//        {
//            StateMachine(&status, msg.value.time_val, msg.value.sensor_val);
//        }
//    }



}
