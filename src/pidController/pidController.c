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
 * @file pidController.c
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Interfaces do PID e controle de suas funcionalidades.
 */

#include "pidController.h"
double controlKi = 0.0;
double controlKp = 0.005;
double controlKd = 0.0;
int targetLocation = 0;
double errorDeviation = 0.00;
double allErrorsSummation = 0.0;
double conversionCoefficientUnit = 294.0;
int pidStatus = 0;

/**
 * @brief Function For Setting New Target Position
 * Funcao Repsonsavel por Setar uma nova possicao desejada.
 * @param Nova Posicao
 * @return Retorna Positivo Caso Consiga Setar Nova Posicao.
 */
int setTarget(int newTarget) {
    if(DEBUG) printf("[DEBUG] - Starting setTarget pidController \n");
    targetLocation = newTarget;
    errorDeviation = 0.0;
    allErrorsSummation = 0.0;
    printf("[INFO] - new Target Location set to %d \n", targetLocation);
    if(DEBUG) printf("[DEBUG] - Set targetLocation to %d \n", targetLocation);
    return TRUE;
}

/**
 * @brief Function For Turn On PID
 * Funcao Responsavel Por Ligar O PID
 */
void turnOnPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOnPidStatus pidController \n");
    if(pidStatus == FALSE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus TRUE \n");
        pidStatus = TRUE;
    }
}

/**
 * @brief Function For Turn Off PID
 * Funcao Responsavel Por Desligar O PID
 */
void turnOffPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOffPidStatus pidController \n");
    if(pidStatus == TRUE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus FALSE \n");
        pidStatus = FALSE;
    }
}

/**
 * @brief Function For Setting Kp Integral Value
 * Funcao Repsonsavel por Setar Kp, valor parte da integral.
 * @param Novo KP
 */
void setControlKp(double newKp){
    if(DEBUG) printf("[DEBUG] - Starting setControlKp pidController \n");
    controlKp = newKp;
    printf("[INFO] - controlKp Value: %f \n", controlKp);
}

/**
 * @brief Function For Setting Kd Integral Value
 * Funcao Repsonsavel por Setar Kd, valor parte da integral.
 * @param Novo KD
 */
void setControlKd(double newKd){
    if(DEBUG) printf("[DEBUG] - Starting setControlKd pidController \n");
    controlKd = newKd;
    printf("[INFO] - controlKd Value: %f \n", controlKd);
}

/**
 * @brief Function For Setting Ki Integral Value
 * Funcao Repsonsavel por Setar Ki, valor parte da integral.
 * @param Novo KI
 */
void setControlKi(double newKi){
    if(DEBUG) printf("[DEBUG] - Starting setControlKi pidController \n");
    controlKi = newKi;
    printf("[INFO] - controlKi Value: %f \n", controlKi);
}

/**
 * @brief Function For Setting New Conversion Coefficinet
 * Funcao Responsavel por setar um novo coeficiente de conversao de controle do PID
 * @param Novo Coeficiente de Conversao
 */
void setConversionCoefficientUnit(double newConversionCoefficientUnit){
    if(DEBUG) printf("[DEBUG] - Starting setConversionCoefficientUnit pidController \n");
    conversionCoefficientUnit = newConversionCoefficientUnit;
    printf("[INFO] - conversionCoefficientUnit Value: %f \n", conversionCoefficientUnit);
}

/**
 * @brief Function For Handling PID
 * Funcao Para Fazer os Calculos do PID e suas variaveis tal como Desvio e Erros, retornando o valor de tensao que deve ser aplicado no motor
 * @param Posicao Corrente
 * @return Valor de Tensão que deve ser aplicado no Motor
 */
double pidHandler(int currentPosition){
    if(DEBUG) printf("[DEBUG] - Starting pidHandler pidController \n");
    double pidUnitVoltage;
    double pPart;
    double iPart;
    double dPart;
    double deviation;
    double tempErrorDeviation = targetLocation - currentPosition;

    allErrorsSummation += tempErrorDeviation;
    deviation = tempErrorDeviation - errorDeviation;
    errorDeviation = tempErrorDeviation;
    pPart = controlKp * tempErrorDeviation;
    iPart = controlKi * allErrorsSummation;
    dPart = controlKd * deviation;

    pidUnitVoltage = pPart + iPart + dPart;

    if(pidUnitVoltage > QSER_VOLTAGE) pidUnitVoltage = QSER_VOLTAGE;
    if(pidUnitVoltage < -QSER_VOLTAGE) pidUnitVoltage = -QSER_VOLTAGE;

    printf("[INFO] - PID Voltage Result %f \n", pidUnitVoltage);
    return pidUnitVoltage;
}