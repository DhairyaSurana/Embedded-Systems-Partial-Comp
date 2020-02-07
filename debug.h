#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>


#define DLOC_ENTER_TASK                 0x01
#define DLOC_BEFORE_WHILE               0X02
#define DLOC_WHILE_BEFORE_QUEUE_RECEIVE 0X03
#define DLOC_WHILE_AFTER_QUEUE_RECEIVE  0X04
#define DLOC_WHILE_BEFORE_QUEUE_SEND    0X05
#define DLOC_WHILE_AFTER_QUEUE_SEND     0x06

#define DLOC_ENTER_TIMERONE_ISR         0x07
#define DLOC_LEAVE_TIMERONE_ISR         0x08
#define DLOC_TIMERONE_BEFORE_QUEUE      0x09
#define DLOC_TIMERONE_AFTER_QUEUE       0x0a

// Timer 1 errors
#define DLOC_TIMERONE_FAILED_INIT       0x0b
#define DLOC_TIMERONE_FAILED_START      0x0c

#define DLOC_ENTER_TIMERTWO_ISR         0x0d
#define DLOC_LEAVE_TIMERTWO_ISR         0x0e
#define DLOC_TIMERTWO_BEFORE_QUEUE      0x0f
#define DLOC_TIMERTWO_AFTER_QUEUE       0x10

// Timer 2 errors
#define DLOC_TIMETWO_FAILED_INIT        0x11
#define DLOC_TIMERTWO_FAILED_START      0x12
#define DLOC_TIMERTWO_ADC_FAILED        0x13

#define DLOC_ENTER_FSM                  0x14
#define DLOC_LEAVE_FSM                  0x15

#define DLOC_FATAL_ERROR                0x16



UART_Handle uart;

void initUART();
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outLoc);
void DebugGPIO_init();

void dbgUARTStr(char outVal[]);
