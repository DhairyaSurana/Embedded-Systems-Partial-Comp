/*
 * timertwo.h
 *
 *  Created on: Feb 5, 2020
 *      Author: Brandon
 */

#ifndef TIMERTWO_H_
#define TIMERTWO_H_

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#include <ti/drivers/Timer.h>
#include <ti/drivers/ADC.h>

#include "Board.h"
#include "debug.h"
#include "sensor_queue.h"
// include debug and queue headers

// Define constants
#define TIMERTWO_PERIOD     75000

#define ZERO                0
#define INVALID_MEASUREMENT -1
#define MV_V_FACTOR         1000000
#define RANGE_NUMERATOR     2914
#define RANGE_V_OFFSET      5
#define RANGE_OFFSET        1


Timer_Handle TimerTwo;
void TimerTwo_init();

ADC_Handle adc;
uint16_t adcValue0;
uint32_t adcValue0MicroVolt;
void IRSensor_init();

void timer75Callback(Timer_Handle myHandle);

int convertToMM();

#endif /* TIMERTWO_H_ */
