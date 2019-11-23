#include "quanserInterface.h"

int handlePwm(int dcAmount) {
    char buf[20];
    snprintf(buf, sizeof(buf), "%d\n", dcAmount);

    if(writeHandler("/sys/class/gpio/gpio1/value", "1") < 0) return 0;
    if(writeHandler("/sys/class/pwm/pwmchip0/device/pwm_period", PWM_PERIOD) < 0) return 0;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/enable", "1") < 0) return 0;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", buf) < 0) return 0;

    return 1;
}