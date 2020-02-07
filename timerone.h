/*
 * timerone.h
 *
 *  Created on: Feb 5, 2020
 *      Author: Brandon
 */

#ifndef TIMERONE_H_
#define TIMERONE_H_

#include <stddef.h>

#include <ti/drivers/Timer.h>

#include "Board.h"
#include "debug.h"
#include "sensor_queue.h"
// include debug and queue headers

#define TIMERONE_PERIOD     1000000

void TimerOne_init();

Timer_Handle TimerOne;
void timerSecondCallback(Timer_Handle myHandle);


#endif /* TIMERONE_H_ */
