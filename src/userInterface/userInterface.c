#include "userInterface.h"

void printUserOptions(){
    printf("########### QSER OPTIONS ##############\n\n");
    printf("--> speed [0 - 100] \n");
    printf("--> goforv [-V - +V] \n");
    printf("--> shiftrad [π - 2π] (double value) \n");
    printf("--> jpl \n");
    printf("--> break \n");
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
    else if (strcmp(cmd, "jpl\n") == 0) { return OPTION_JPL; }
    else if (strncmp(cmd, "goforv", 6) == 0) { return OPTION_GO_FOR_V; }
    else if (strcmp(cmd, "break\n") == 0) { return OPTION_QSER_BREAK; }
    else if (strcmp(cmd, "help\n") == 0) { return OPTION_HELP; }
    else if (strcmp(cmd, "exit\n") == 0) { return OPTION_EXIT; }
    else if (strncmp(cmd, "shiftrad", 8) == 0) { return OPTION_SHIFT_RAD; }
    else if (strncmp(cmd, "setkp", 5) == 0) { return OPTION_SET_KP; }
    else if (strncmp(cmd, "setkd", 5) == 0) { return OPTION_SET_KD; }
    else if (strncmp(cmd, "setki", 5) == 0) { return OPTION_SET_KI; }
    else if (strncmp(cmd, "setccu", 6) == 0) { return OPTION_SET_CCU; }
    else return OPTION_INVALID;
}