//
// Created by Rodolfo Carvalho on 12/1/19.
//

#ifndef QSER_PIDCONTROLLER_H
#define QSER_PIDCONTROLLER_H
#include "../helpers/helpers.h"
#include "../quanserInterface/quanserInterface.h"

int setTarget(int newTarget);
void turnOnPid();
void turnOffPid();
void setControlKp(double newKp);
void setControlKd(double newKd);
void setControlKi(double newKi);
void setConversionCoefficientUnit(double newConversionCoefficientUnit);

#endif //QSER_PIDCONTROLLER_H
