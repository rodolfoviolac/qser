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
 * @file mainThread.h
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Header File for The Main Thread.
 */


#ifndef QSER_MAINTHREAD_H
#define QSER_MAINTHREAD_H
#include "../userInterface/userInterface.h"
#include "../quanserInterface/quanserInterface.h"
#include "../pidController/pidController.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern double conversionCoefficientUnit;
extern int pidStatus;
void* handlerMainThread();

#endif //QSER_MAINTHREAD_H