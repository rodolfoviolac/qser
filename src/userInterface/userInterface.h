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
#define OPTION_SHIFT_RAD 7
#define OPTION_SET_KP 8
#define OPTION_SET_KD 9
#define OPTION_SET_KI 10
#define OPTION_SET_CCU 11
#define OPTION_CLEAR_DEC 12
#define OPTION_READ_DEC 13
#define OPTION_READ_DEC_RAD 14


void printUserOptions();
void printUserGroupsName();
int resolveOption(char* input);

#endif //QSER_USERINTERFACE_H
