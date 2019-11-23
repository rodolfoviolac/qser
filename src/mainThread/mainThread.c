//
// Created by Rodolfo Carvalho on 11/23/19.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mainThread.h"
#include "../userInterface/userInterface.h"


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
                    float dc = (commandAmount/100)*atof(PWM_PERIOD);
                    printf("%f", dc);
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
                printf("Command Invalid Type Help For The Command List\n");
                break;
            }
            default: {
                printf("Command Invalid Type Help For The Command List\n");
            }
        }
    }
}