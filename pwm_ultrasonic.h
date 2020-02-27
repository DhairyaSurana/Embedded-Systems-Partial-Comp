#ifndef PWM_ULTRASONIC_H_
#define PWM_ULTRASONIC_H_

/* Driver Header files */
//#include <ti/drivers/Capture.h>
//#include <ti/display/Display.h>
#include <ti/drivers/PWM.h>
//#include <ti/drivers/dpl/SemaphoreP.h>
#include <stddef.h>

#define PWM_PERIOD 10 //10 micro second
#define DUTY_VALUE 0

//SemaphoreP_Params semParams;
//Capture_Params captureParams;
//Capture_Handle capture;
PWM_Params pwmParams;
PWM_Handle pwm0; //pwm1;

void init_pwm();

#endif /* PWM_ULTRASONIC_H_ */
