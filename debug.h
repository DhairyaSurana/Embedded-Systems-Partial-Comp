#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

//#include <stdint.h>
//#include <stdbool.h>
//#include <stddef.h>
//#include <stdlib.h>
//
////#include "system_config/default/system_config.h"
//#include "system_config/default/system_definitions.h"

//Initialization
#define DLOC_ENTER_TASK                 0x01
#define DLOC_BEFORE_WHILE               0X02

//Timer 1 activated (starts with 1)
#define DLOC_ENTER_TIMERONE_ISR         0x10
#define DLOC_LEAVE_TIMERONE_ISR         0x11

//Timer 2 activated (starts with 2)
#define DLOC_ENTER_TIMERTWO_ISR         0x20
#define DLOC_TIMERTWO_ADC_CONV_START    0x21
#define DLOC_TIMERTWO_ADC_CONV_END      0x22
#define DLOC_LEAVE_TIMERTWO_ISR         0x23

//Queue (Starts with 3)
#define DLOC_BEFORE_QUEUE_READ          0X30
#define DLOC_AFTER_QUEUE_READ           0X31
#define DLOC_BEFORE_QUEUE_SENSOR        0X32
#define DLOC_AFTER_QUEUE_SENSOR         0X33
#define DLOC_BEFORE_QUEUE_TIME          0X34
#define DLOC_AFTER_QUEUE_TIME           0x35
#define DLOC_QUEUE_SENDING_MSG          0x36
#define DLOC_QUEUE_SEND_SUCCESS         0x37
#define DLOC_QUEUE_SEND_FAIL            0x38


//State Machine (Starts with 4)
#define DLOC_STATE_INIT                 0x40
#define DLOC_STATE_ONE                  0x41
#define DLOC_STATE_TWO                  0x42
#define DLOC_STATE_THREE                0x43
#define DLOC_STATE_DONE                 0x44

//ERRORS (starts with 6)
// Timer 1 errors
#define DLOC_TIMERONE_FAILED_INIT       0x60
#define DLOC_TIMERONE_FAILED_START      0x61

// Timer 2 errors
#define DLOC_TIMETWO_FAILED_INIT        0x63
#define DLOC_TIMERTWO_FAILED_START      0x64
#define DLOC_TIMERTWO_ADC_FAILED        0x65


#define DLOC_FATAL_ERROR                0x66
#define DLOC_UART_FAILED                0x67
#define DLOC_OVER127_ERROR              0x68




UART_Handle uart;

void initUART();
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outLoc);
void DebugGPIO_init();

void dbgClearOut();
void dbgClearIn();

void dbgHaltAll(unsigned int outLoc);
