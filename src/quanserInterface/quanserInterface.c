#include "quanserInterface.h"

int handlePwm(int dcAmount) {
    if(IS_RUNNING_LOCAL) return 0;
    char data[20];
    snprintf(data, sizeof(data), "%d\n", dcAmount);
    if(writeHandler("/sys/class/gpio/gpio1/value", "1") < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/enable", "1") < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/device/pwm_period", PWM_PERIOD) < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", data) < 0) return FALSE;
    return TRUE;
}

int qserInitializer(int dcAmount) {
    printf("[INFO] - Initializing Quanser");

}

int qserBreak() {
    if(IS_RUNNING_LOCAL) return 0;
    if(writeHandler("/sys/class/gpio/gpio1/value", "0") < 0) {
        return FALSE;
    }
    return TRUE;
}

int qserVoltage(float voltage) {
    float dcAmount = ((voltage+QSER_VOLTAGE)/(2*QSER_VOLTAGE))*atof(PWM_PERIOD);
    return handlePwm((int)dcAmount);
}

void* jointPositionLimitHandler() {
    if(IS_RUNNING_LOCAL) return 0;
    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler Thread \n");
    char rootPathLimiterOneValue[100] = "/sys/class/gpio/gpio6/value";
    char rootPathLimiterTwoValue[100] = "/sys/class/gpio/gpio0/value";
    char rootPathLimiterOneEdge[100] = "/sys/class/gpio/gpio6/edge";
    char rootPathLimiterTwoEdge[100] = "/sys/class/gpio/gpio0/edge";

    unsigned char dataOne;
    unsigned char dataTwo;
    struct pollfd pollFileHandlerOne;
    struct pollfd pollFileHandlerTwo;

    if((pollFileHandlerOne.fd = open(rootPathLimiterOneValue, O_RDONLY)) < 0) {
        fprintf(stderr, "[ERROR] - Joint Position Limiter One Open File Descriptor Error %s.\n", rootPathLimiterOneValue);
        exit(11);
    }

    if((pollFileHandlerTwo.fd = open(rootPathLimiterTwoValue, O_RDONLY)) < 0) {
        fprintf(stderr, "ERROR] - Joint Position Limiter Two Open File Descriptor Error %s.\n", rootPathLimiterTwoValue);
        exit(11);
    }

    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler While \n");
    int shouldNeverStop = TRUE;
    while(shouldNeverStop) {
        if(DEBUG) printf("[DEBUG] - Checking Joint Position Limiter \n");
        pollFileHandlerOne.events = POLLPRI;
        pollFileHandlerTwo.events = POLLPRI;
        writeHandler(rootPathLimiterOneEdge,"both");
        writeHandler(rootPathLimiterTwoEdge,"both");
        poll(&pollFileHandlerOne,1,-1);
        poll(&pollFileHandlerTwo,1,-1);
        lseek(pollFileHandlerOne.fd,0,SEEK_SET);
        lseek(pollFileHandlerTwo.fd,0,SEEK_SET);
        if(read(pollFileHandlerOne.fd, &dataOne, 1) < 0) {
            fprintf(stderr, "[ERROR] - Joint Position Limiter One Reading Error %s.\n\n", rootPathLimiterOneValue);
            exit(12);
        }
        if(read(pollFileHandlerTwo.fd, &dataTwo, 1) < 0) {
            fprintf(stderr, "[ERROR] - Joint Position Limiter Two Reading Error %s.\n\n", rootPathLimiterTwoValue);
            exit(12);
        }
        if(dataOne == JPL_REACHED || dataTwo == JPL_REACHED) {
            qserBreak();
//            pid_joined = 0;
//            fprintf(stderr, ">>> O braco chegou ao sensor de fim de curso %d.\n\n", sensor->num);
        }
        sleep(1);
    }
}