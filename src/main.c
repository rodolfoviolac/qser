#include <stdio.h>
#include "pthread.h"
#include "math.h"
#include "mainThread/mainThread.h"

int main() {
    if(DEBUG) printf("[DEBUG] - Starting Application");
    pthread_t userThread;
    pthread_t positionHandlerOneThread;
    pthread_t positionHandlerTwoThread;

    if(DEBUG) printf("[DEBUG] - Calling JPL Thread");
    pthread_create(&positionHandlerOneThread, NULL, jointPositionLimitOneHandler, NULL);
    pthread_create(&positionHandlerTwoThread, NULL, jointPositionLimitTwoHandler, NULL);
    if(DEBUG) printf("[DEBUG] - Calling User Thread");
    pthread_create(&userThread, NULL, handlerMainThread, NULL);

    pthread_join(positionHandlerOneThread, NULL);
    pthread_join(positionHandlerTwoThread, NULL);
    pthread_join(userThread, NULL);
    return 0;
}