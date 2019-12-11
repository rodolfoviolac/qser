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
 * @file pidController.h
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Cabeçalho das funções da interface do PID
 */
#ifndef QSER_PIDCONTROLLER_H
#define QSER_PIDCONTROLLER_H
#include "../helpers/helpers.h"
#include "../quanserInterface/quanserInterface.h"

int setTarget(int newTarget);
void turnOnPid();
void turnOffPid();
void setControlKp(double newKp);
void setControlKd(double newKd);
void setControlKi(double newKi);
void setConversionCoefficientUnit(double newConversionCoefficientUnit);
double pidHandler(int currentPosition);

#endif //QSER_PIDCONTROLLER_H
