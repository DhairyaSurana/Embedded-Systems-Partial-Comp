#include "debug.h"
#include "timerone.h"
#include "timertwo.h"
#include "Board.h"
#include <ti/drivers/GPIO.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/driverlib/gpio.h>
// #include <ti/devices/cc32xx/driverlib/gpio.c> <- This contains the API to deal with writing to GPIO properly. un comment and ctl click to see source.
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_gpio.h> //ADDED TO INCLUDE GPIO_O_GPIO_DIR
#include <ti/drivers/dpl/HwiP.h>
#include <stddef.h>

void initUART()
{
    UART_Params uartParams;
    UART_Params_init(&uartParams);

    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;
}


// receives a value and outputs to UART
void dbgUARTVal(unsigned char outVal)
{
    UART_write(uart, &outVal, sizeof(outVal));
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
	}
	
	int binLoc[8];
	int_to_bin_digit(outLoc, 8, binLoc);

    GPIO_write(Board_GPIO1, binLoc[7]);
    GPIO_write(Board_GPIO2, binLoc[6]);
    GPIO_write(Board_GPIO3, binLoc[5]);
    GPIO_write(Board_GPIO4, binLoc[4]);
    GPIO_write(Board_GPIO5, binLoc[3]);
    GPIO_write(Board_GPIO6, binLoc[2]);
    GPIO_write(Board_GPIO7, binLoc[1]);
    GPIO_write(Board_GPIO8, binLoc[0]);


}

void SensorHalt(unsigned int outLoc){
    dbgOutputLoc(DLOC_Fatal_Error);
    //stop all tasks
    vTaskSuspendAll();
	//output that all tasks have been stopped (disable all iterrupts)
    Timer_stop(TimerOne);
    Timer_stop(TimerTwo);

    HwiP_disable();

}

void DebugGPIO_init() {

    printf('h');
    GPIO_setConfig(Board_GPIO1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO3, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO4, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO7, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO8, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

}
