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
 * @file helpers.h
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Header Files for the Helpers Functions and Universal Variables
 */

#ifndef QSER_HELPERS_H
#define QSER_HELPERS_H
/** @brief Modulo Para Execucao Do Qser Local */
#define IS_RUNNING_LOCAL 0
/** @brief Modulo Para Depuracao */
#define DEBUG 0
#define TRUE 1
#define FALSE 0
/** @brief Define Valor de Pi */
#define PI 3.141592653589793238462643383279
#define MAX_RANGE 180.00
#define CONST_UNIT_RAD_MATH 0.01745329251
#define RAD2G MAX_RANGE/PI
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int writeHandler(const char filePath[], const char data[]);
char *readHandler(char *data, int size, const char filePath[]);

#endif //QSER_HELPERS_H
