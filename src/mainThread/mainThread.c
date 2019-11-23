#include "mainThread.h"

void handlerMainThread() {
    printUserGroupsName();
    printUserOptions();

    char command[100];
    while (fgets(command, sizeof(command), stdin)) {
        switch (resolveOption(command)) {
            case OPTION_SPEED: {
                float commandAmount = atof(&command[6]);
                if(commandAmount > 100 || commandAmount < 0) {
                    printf("[ERROR] - Speed Amount Must Be [0-100]\n");
                } else {
                    float dcAmount = (commandAmount/100)*atof(PWM_PERIOD);
                    if(handlePwm((int)dcAmount) == 1) {
                        fprintf(stdout, "[INFO] - Motor Duty Cycle %d\n\n", (int)dcAmount);
                    } else {
                        printf("[ERROR] - Error Turning On Motor\n\n");
                    }
                }
                break;
            }
            case OPTION_HELP: {
                printUserOptions();
                break;
            }
            case OPTION_EXIT: {
                printf("Finishing Application...\n");
                exit(0);
            }
            case OPTION_INVALID: {
                printf("[ERROR] - Command Invalid Type Help For The Command List\n");
                break;
            }
            default: {
                printf("[ERROR] - Command Invalid Type Help For The Command List\n");
            }
        }
    }
}