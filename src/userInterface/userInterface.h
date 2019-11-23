//
// Created by Rodolfo Carvalho on 11/23/19.
//

#ifndef QSER_USERINTERFACE_H
#define QSER_USERINTERFACE_H
#define OPTION_INVALID 0
#define OPTION_EXIT 1
#define OPTION_HELP 2
#define OPTION_SPEED 3


void printUserOptions();
void printUserGroupsName();
int resolveOption(char* input);

#endif //QSER_USERINTERFACE_H
