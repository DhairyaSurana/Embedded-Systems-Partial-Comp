#include "debug.h"
#include "timerone.h"
#include "timertwo.h"
//#include "pwm_ultrasonic.h"
#include "Board.h"
#include <ti/drivers/GPIO.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/driverlib/gpio.h>
// #include <ti/devices/cc32xx/driverlib/gpio.c> <- This contains the API to deal with writing to GPIO properly. un comment and ctl click to see source.
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_gpio.h> //ADDED TO INCLUDE GPIO_O_GPIO_DIR
#include <ti/drivers/dpl/HwiP.h>
#include <stddef.h>

void dbgUARTVal(unsigned char outVal){

    UART_write(uart, &outVal, sizeof(outVal));
}

void dbgOutputLoc(unsigned int outLoc){

    if (outLoc > 127)
        fatalError(MAIN_TASK_DLOC_PARAM_OUT_OF_BOUNDS);


    unsigned char first_half = (outLoc & 0x01)|((outLoc & 0x0e)<<4);
    unsigned char second_half = ((outLoc & 0x10)>>4)|((outLoc & 0x20)>>1)|(outLoc & 0xc0);

    GPIOPinWrite(GPIOA0_BASE, 0b11100001, first_half);      // GPIO 0-3
    GPIOPinWrite(GPIOA1_BASE, 0b11010001, second_half);     // GPIO 4-7

    unsigned char test = GPIOPinRead(GPIOA0_BASE, 0b11100001);
}

void fatalError(unsigned int outLoc){

    dbgOutputLoc(outLoc);

    //temp code for now
    Timer_close(timer1);
    Timer_close(timer2);

    //need the ISR stop call here
    HwiP_disable();
    vTaskSuspendAll();
}

void initUART(){

    UART_init();

    UART_Params uartParams;

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL)   // Error checking for UART
        fatalError(MAIN_TASK_DLOC_FAILED_UART_OPEN);

}

void initGPIO()
{

    GPIO_init();

    GPIO_setConfig(Board_GPIO0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO3, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO4, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO7, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    GPIO_setConfig(Board_GPIO9_Echo, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_BOTH_EDGES);

    GPIO_write(Board_GPIO0, 0);
    GPIO_write(Board_GPIO1, 0);
    GPIO_write(Board_GPIO2, 0);
    GPIO_write(Board_GPIO3, 0);
    GPIO_write(Board_GPIO4, 0);
    GPIO_write(Board_GPIO5, 0);
    GPIO_write(Board_GPIO6, 0);
    GPIO_write(Board_GPIO7, 0);
}
