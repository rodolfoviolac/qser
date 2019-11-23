#include <stdio.h>
#include "pthread.h"
#include "math.h"
#include "mainThread/mainThread.h"

int main() {
    pthread_t userThread;
    pthread_t positionHandlerThread;

    pthread_create(&positionHandlerThread, NULL, jointPositionLimitHandler, NULL);
    pthread_create(&userThread, NULL, handlerMainThread, NULL);

    pthread_join(positionHandlerThread, NULL);
    pthread_join(userThread, NULL);
    return 0;
}