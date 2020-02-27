#include "pwm_ultrasonic.h"
#include "Board.h"
#include "debug.h"

void init_pwm() {

    PWM_init();

    PWM_Params_init(&pwmParams);
    pwmParams.dutyUnits = PWM_DUTY_US;
    pwmParams.dutyValue = DUTY_VALUE;
    pwmParams.periodUnits = PWM_PERIOD_US;
    pwmParams.periodValue = PWM_PERIOD;

    pwm0 = PWM_open(0, &pwmParams);
    PWM_start(pwm0);

}


