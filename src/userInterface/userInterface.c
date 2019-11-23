#include "userInterface.h"

void printUserOptions(){
    printf("########### QSER OPTIONS ##############\n\n");
    printf("--> speed \n");
    printf("--> help \n");
    printf("--> exit \n\n");
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
    if (strncmp(cmd, "speed", 5) == 0) { return OPTION_SPEED; }
    else if (strcmp(cmd, "help\n") == 0) { return OPTION_HELP; }
    else if (strcmp(cmd, "exit\n") == 0) { return OPTION_EXIT; }
    else return OPTION_INVALID;
}