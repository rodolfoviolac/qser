//
// Created by Rodolfo Carvalho on 11/23/19.
//
#include <stdio.h>
#include <string.h>
#include "userInterface.h"

void printUserOptions(){
    printf("########### QSER OPTIONS ##############\n\n");
    printf("-> speed \n");
    printf("-> help \n");
    printf("-> quit \n\n");
    printf("######################################\n\n");
}

void printUserGroupsName(){
    printf("########### QSER 2019/2 ##############\n");
    printf("> Rodolfo Viola Carvalho\n");
    printf("> Gabriel Alexandre Zillmer\n");
    printf("> Felipe Fuhr Dos Reis\n");
    printf("######################################\n\n");
}

int resolveOption(char* cmd) {
    if (strcmp(cmd, "speed\n") == 0) { return OPTION_SPEED; }
    else if (strcmp(cmd, "help\n") == 0) { return OPTION_HELP; }
    else if (strcmp(cmd, "quit\n") == 0) { return OPTION_QUIT; }
    else return OPTION_INVALID;
}