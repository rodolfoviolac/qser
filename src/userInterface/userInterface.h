// Qser Aplication
// Copyright (C) 2019 Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/**
 * @file userInterface.h
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Header File for The User Interface.
 */

#ifndef QSER_USERINTERFACE_H
#define QSER_USERINTERFACE_H
#include <stdio.h>
#include <string.h>
/** @brief Define os Ids para as opções para o menu */
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
