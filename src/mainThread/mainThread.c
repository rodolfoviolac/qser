#include "mainThread.h"

void* handlerMainThread() {
    if(DEBUG) printf("[DEBUG] - Starting handlerMainThread");
    printUserGroupsName();
    printUserOptions();

    char command[100];
    while (fgets(command, sizeof(command), stdin)) {
        if(DEBUG) printf("[DEBUG] - Inside Command While MainThread");
        switch (resolveOption(command)) {
            case OPTION_SPEED: {
                if(DEBUG) printf("[DEBUG] - Got SPEED Option MainThread");
                float commandAmount = atof(&command[6]);
                if(commandAmount > 100 || commandAmount < 0) {
                    printf("[ERROR] - Speed Amount Must Be [0-100]\n");
                } else {
                    if(DEBUG) printf("[DEBUG] - Got Valid Speed Number MainThread");
                    float dcAmount = (commandAmount/100)*atof(PWM_PERIOD);
                    if(handlePwm((int)dcAmount) == 1) {
                        fprintf(stdout, "[INFO] MT - Motor Duty Cycle %d\n\n", (int)dcAmount);
                    } else {
                        printf("[ERROR] MT - Error Turning On Motor\n\n");
                    }
                }
                break;
            }
            case OPTION_HELP: {
                if(DEBUG) printf("[DEBUG] - Got HELP Option MainThread");
                printUserOptions();
                break;
            }
            case OPTION_EXIT: {
                if(DEBUG) printf("[DEBUG] - Got EXIT Option MainThread");
                printf("Finishing Application...\n");
                exit(0);
            }
            case OPTION_INVALID: {
                if(DEBUG) printf("[DEBUG] - Got INVALID Option MainThread");
                printf("[ERROR] - Command Invalid Type Help For The Command List\n");
                break;
            }
            default: {
                if(DEBUG) printf("[DEBUG] - Got DEFAULT Option MainThread");
                printf("[ERROR] - Command Invalid Type Help For The Command List\n");
            }
        }
    }
    return NULL;
}