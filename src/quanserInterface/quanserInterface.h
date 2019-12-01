#ifndef QSER_QUANSERINTERFACE_H
#define QSER_QUANSERINTERFACE_H
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include "../helpers/helpers.h"
#include "../pidControler/pidControler.h"
#include "../decoderInterface/decoderInterface.h"
#define PWM_PERIOD "1000000"
#define QSER_VOLTAGE 27.0
#define JPL_REACHED '0'
#define JPL_UNREACHED '1'
extern int JPL_REACHED_STATUS_ONE;
extern int JPL_REACHED_STATUS_TWO;
extern int pidStatus;

int handlePwm(int dcAmount);
int qserInitializer();
int qserBreak();
int qserVoltage(float voltage);
void* jointPositionLimitOneHandler();
void* jointPositionLimitTwoHandler();
void* goToTargetPositionHandler();

#endif //QSER_QUANSERINTERFACE_H
