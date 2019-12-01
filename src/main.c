#include <stdio.h>
#include "pthread.h"
#include "math.h"
#include "mainThread/mainThread.h"

int main() {
    if(DEBUG) printf("[DEBUG] - Starting Application \n");
    pthread_t userThread;
    pthread_t positionHandlerOneThread;
    pthread_t positionHandlerTwoThread;
    pthread_t PIDThread;


    if(qserInitializer() == TRUE){
        printf("\n\n---------------------------------\n");
        printf("[INFO] - Qser Is Booming! \n");
        printf("---------------------------------\n\n");
    } else {
        printf("[ERROR] - Not Possible To Initializer Qser! \n");
        exit(1);
    }

    if(DEBUG) printf("[DEBUG] - Calling JPL Thread \n");
    pthread_create(&positionHandlerOneThread, NULL, jointPositionLimitOneHandler, NULL);
    pthread_create(&positionHandlerTwoThread, NULL, jointPositionLimitTwoHandler, NULL);
    if(DEBUG) printf("[DEBUG] - Calling User Thread \n");
    pthread_create(&userThread, NULL, handlerMainThread, NULL);
    if(DEBUG) printf("[DEBUG] - Calling PID Thread \n");
    pthread_create(&PIDThread, NULL, goToTargetPositionHandler, NULL);

    pthread_join(positionHandlerOneThread, NULL);
    pthread_join(positionHandlerTwoThread, NULL);
    pthread_join(userThread, NULL);
    pthread_join(PIDThread, NULL);
    return 0;
}