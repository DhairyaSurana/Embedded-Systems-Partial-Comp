
#include "pwm_ultrasonic.h"
#include "Board.h"

void init_pwm()
{
    //Capture_init();
    PWM_init();

    uint32_t pwmPeriod = PWM_PERIOD;

    //pwm init
    PWM_Params_init(&pwmParams);
    pwmParams.dutyUnits = PWM_DUTY_US;
    pwmParams.dutyValue = DUTY_VALUE;
    pwmParams.periodUnits = PWM_PERIOD_US;
    pwmParams.periodValue = pwmPeriod;

    pwm0 = PWM_open(0, &pwmParams); //open pwm

    PWM_start(pwm0);

}

