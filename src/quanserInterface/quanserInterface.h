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
 * @file quanserInterface.h
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Header File for The Quanser Interface.
 */

#ifndef QSER_QUANSERINTERFACE_H
#define QSER_QUANSERINTERFACE_H
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include "../helpers/helpers.h"
#include "../pidController/pidController.h"
#include "../decoderInterface/decoderInterface.h"
/** @brief Define o Período do PWM */
#define PWM_PERIOD "1000000"
/** @brief Define Valor de Tensão Máxima */
#define QSER_VOLTAGE 27.0
#define JPL_REACHED '0'
#define JPL_UNREACHED '1'
extern int JPL_REACHED_STATUS_ONE;
extern int JPL_REACHED_STATUS_TWO;
extern int pidStatus;

int handlePwm(int dcAmount);
int qserInitializer();
int qserBreak();
int qserVoltage(float voltage);
void* jointPositionLimitOneHandler();
void* jointPositionLimitTwoHandler();
void* goToTargetPositionHandler();

#endif //QSER_QUANSERINTERFACE_H
