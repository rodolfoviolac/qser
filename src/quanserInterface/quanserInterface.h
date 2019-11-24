#ifndef QSER_QUANSERINTERFACE_H
#define QSER_QUANSERINTERFACE_H
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include "../helpers/helpers.h"
#define PWM_PERIOD "1000000"
#define QSER_VOLTAGE 27.0
#define JPL_REACHED '0'
#define JPL_UNREACHED "1"

int handlePwm(int dcAmount);
int qserInitializer(int dcAmount);
int qserBreak();
int qserVoltage(float voltage);
void* jointPositionLimitOneHandler();
void* jointPositionLimitTwoHandler();

#endif //QSER_QUANSERINTERFACE_H
