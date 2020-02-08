
#include "Board.h"
#include "timerone.h"
#include "timertwo.h"
#include "debug.h"



#include <ti/drivers/GPIO.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/driverlib/gpio.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_gpio.h>

//#include "string.h"


void initUART()
{

    UART_Params uartParams;
    UART_Params_init(&uartParams);

    uartParams.writeMode = UART_DATA_BINARY;
    uartParams.readMode = UART_DATA_BINARY;
    uartParams.writeDataMode = UART_DATA_BINARY;
        uartParams.readDataMode = UART_DATA_BINARY;
        uartParams.baudRate = 115200;
        uartParams.readEcho = UART_ECHO_OFF;
    uartParams.readReturnMode = UART_RETURN_FULL;

    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL)
         printf("Uaasd");


}


// receives a value and outputs to UART
void dbgUARTVal(unsigned char outVal)
{
    UART_write(uart, &outVal, sizeof(outVal));
}


void dbgUARTStr(char outVal[])
{

    size_t length = strlen(outVal);
    size_t i;
    for(i = 0; i < length; i++) {
        UART_write(uart, &outVal[i], sizeof(outVal[i]));
    }
}

static void int_to_bin_digit(unsigned int in, int count, int* out)
{
    /* assert: count <= sizeof(int)*CHAR_BIT */
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}

void dbgOutputLoc(unsigned int outLoc){
    if(outLoc>127){
        //fail
        dbgUARTStr("ERROR WITH DEBUG");
    }

    int binLoc[8] = {0};

    GPIO_write(Board_GPIO0, 1); // toggle
    int_to_bin_digit(outLoc, 8, binLoc);

v
    //if(binLoc[0] == 1) {
        GPIO_write(Board_GPIO1, binLoc[8]);
        GPIO_write(Board_GPIO2, binLoc[7]);
        GPIO_write(Board_GPIO3, binLoc[6]);
        GPIO_write(Board_GPIO4, binLoc[5]);
        GPIO_write(Board_GPIO5, binLoc[4]);
        GPIO_write(Board_GPIO6, binLoc[3]);
        GPIO_write(Board_GPIO7, binLoc[2]);
        GPIO_write(Board_GPIO8, binLoc[1]);

        GPIO_write(Board_GPIO0, 0);
    //}



}

void HALT(unsigned int outLoc){
    dbgOutputLoc(DLOC_FATAL_ERROR);

    //SYS_INT_Disable();
    //stop all tasks
    vTaskSuspendAll();
    //output that all tasks have been stopped (disable all iterrupts)
    Timer_stop(TimerOne);
    Timer_stop(TimerTwo);

    HwiP_disable();


}

void DebugGPIO_init() {

    GPIO_setConfig(Board_GPIO1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO3, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO4, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO7, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO8, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

}
