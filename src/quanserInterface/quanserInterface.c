#include "quanserInterface.h"

int handlePwm(int dcAmount) {
    if(DEBUG) printf("[DEBUG] - Starting handlePwm");
    if(IS_RUNNING_LOCAL) return TRUE;
    char data[20];
    snprintf(data, sizeof(data), "%d\n", dcAmount);
    if(writeHandler("/sys/class/gpio/gpio1/value", "1") < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/enable", "1") < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/device/pwm_period", PWM_PERIOD) < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", data) < 0) return FALSE;
    if(DEBUG) printf("[DEBUG] - Finishing handlePwm");
    return TRUE;
}

int qserInitializer(int dcAmount) {
    printf("[INFO] - Initializing Quanser");

}

int qserBreak() {
    if(DEBUG) printf("[DEBUG] - Starting qserBreak");
    if(IS_RUNNING_LOCAL) return TRUE;
    if(writeHandler("/sys/class/gpio/gpio1/value", "0") < 0) {
        printf("[INFO] - Error Writing qserBreak File Value to Zero");
        return FALSE;
    }
    if(DEBUG) printf("[DEBUG] - Finishing qserBreak");
    return TRUE;
}

int qserVoltage(float voltage) {
    if(DEBUG) printf("[DEBUG] - Starting qserVoltage");
    float dcAmount = (( voltage + QSER_VOLTAGE ) / ( 2 * QSER_VOLTAGE )) * atof(PWM_PERIOD);
    if(DEBUG) printf("[DEBUG] - Finishing qserVoltage");
    return handlePwm((int)dcAmount);
}

void* jointPositionLimitOneHandler() {
    if(IS_RUNNING_LOCAL) return 0;
    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler Thread \n");
    char rootPathLimiterOneValue[100] = "/sys/class/gpio/gpio6/value";
    char rootPathLimiterOneEdge[100] = "/sys/class/gpio/gpio6/edge";

    unsigned char dataOne;
    struct pollfd pollFileHandlerOne;

    if(DEBUG) printf("[DEBUG] - JPL Opening First File GPIO 6\n");
    if((pollFileHandlerOne.fd = open(rootPathLimiterOneValue, O_RDONLY)) < 0) {
        fprintf(stderr, "[ERROR] - Joint Position Limiter One Open File Descriptor Error %s.\n", rootPathLimiterOneValue);
        exit(11);
    }

    read(pollFileHandlerOne.fd,&dataOne,1);

    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler While \n");
    int shouldNeverStop = TRUE;
    while(shouldNeverStop) {
        if(DEBUG) printf("[DEBUG] - Checking Joint Position Limiter \n");
        pollFileHandlerOne.events = POLLPRI;
        writeHandler(rootPathLimiterOneEdge,"both");
        poll(&pollFileHandlerOne,1,-1);
        lseek(pollFileHandlerOne.fd,0,SEEK_SET);
        if(DEBUG) printf("[DEBUG] - JPL Reading First File GPIO 0\n");
        if(read(pollFileHandlerOne.fd, &dataOne, 1) < 0) {
            fprintf(stderr, "[ERROR] - JPL One Reading Error %s\n\n", rootPathLimiterOneValue);
            exit(2);
        }
        if(DEBUG) printf("[DEBUG] - JPL Testing For End\n");
        if(dataOne == JPL_REACHED) {
            printf("[INFO] - JPL ONE Reached End \n\n");
            qserBreak();
//            pid_joined = 0; //TODO NEEDS IMPLEMENTATION
        }
    }
    return NULL;
}
void* jointPositionLimitTwoHandler() {
    if(IS_RUNNING_LOCAL) return 0;
    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler Thread \n");
    char rootPathLimiterTwoValue[100] = "/sys/class/gpio/gpio0/value";
    char rootPathLimiterTwoEdge[100] = "/sys/class/gpio/gpio0/edge";

    unsigned char dataTwo;
    struct pollfd pollFileHandlerTwo;

    if(DEBUG) printf("[DEBUG] - JPL Opening First File GPIO 6\n");
    if((pollFileHandlerTwo.fd = open(rootPathLimiterTwoValue, O_RDONLY)) < 0) {
        fprintf(stderr, "[ERROR] - Joint Position Limiter Two Open File Descriptor Error %s.\n", rootPathLimiterTwoValue);
        exit(11);
    }

    read(pollFileHandlerTwo.fd, &dataTwo, 1);

    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler While \n");
    int shouldNeverStop = TRUE;
    while(shouldNeverStop) {
        if(DEBUG) printf("[DEBUG] - Checking Joint Position Limiter \n");
        pollFileHandlerTwo.events = POLLPRI;
        writeHandler(rootPathLimiterTwoEdge,"both");
        poll(&pollFileHandlerTwo, 1, -1);
        lseek(pollFileHandlerTwo.fd, 0, SEEK_SET);
        if(DEBUG) printf("[DEBUG] - JPL Reading First File GPIO 0\n");
        if(read(pollFileHandlerTwo.fd, &dataTwo, 1) < 0) {
            fprintf(stderr, "[ERROR] - JPL Two Reading Error %s\n\n", rootPathLimiterTwoValue);
            exit(2);
        }
        if(DEBUG) printf("[DEBUG] - JPL Testing For End\n");
        if(dataTwo == JPL_REACHED) {
            printf("[INFO] - JPL TWO Reached End \n\n");
            qserBreak();
//            pid_joined = 0; //TODO NEEDS IMPLEMENTATION
        }
    }
    return NULL;
}