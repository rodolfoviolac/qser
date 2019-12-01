#ifndef QSER_MAINTHREAD_H
#define QSER_MAINTHREAD_H
#include "../userInterface/userInterface.h"
#include "../quanserInterface/quanserInterface.h"
#include "../pidControler/pidControler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern double conversionCoefficientUnit;
extern int pidStatus;
void* handlerMainThread();

#endif //QSER_MAINTHREAD_H