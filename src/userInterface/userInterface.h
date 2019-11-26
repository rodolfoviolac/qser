#ifndef QSER_USERINTERFACE_H
#define QSER_USERINTERFACE_H
#include <stdio.h>
#include <string.h>
#define OPTION_INVALID 0
#define OPTION_EXIT 1
#define OPTION_HELP 2
#define OPTION_SPEED 3
#define OPTION_JPL 4
#define OPTION_GO_FOR_V 5
#define OPTION_QSER_BREAK 6


void printUserOptions();
void printUserGroupsName();
int resolveOption(char* input);

#endif //QSER_USERINTERFACE_H
