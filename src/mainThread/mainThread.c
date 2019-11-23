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
                printf("SPEEEEEEEEED\n");
                break;
            }
            case OPTION_HELP: {
                printf("HELPEEEEEE\n");
                break;
            }
            case OPTION_QUIT: {
                printf("QUIIIT\n");
                exit(0);
                break;
            }
            case OPTION_INVALID: {
                printf("INVALID\n");
                break;
            }
            default: {
                printf("Valor invalido!\n");
            }
        }
    }
}