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
/** @brief Define Parte de Controle de Ki */
double controlKi = 0.0;
/** @brief Define Parte de Controle de Kp */
double controlKp = 0.005;
/** @brief Define Parte de Controle de Kd */
double controlKd = 0.0;
/** @brief Define uma posição de destino */
int targetLocation = 0;
/** @brief Define o desvio do erro */
double errorDeviation = 0.00;
/** @brief Define somatório de todos os erros */
double allErrorsSummation = 0.0;
/** @brief Define o Status do PID */
int pidStatus = 0;

/**
 * @brief Função para setar nova posição.
 * Rotina responsável por setar uma nova posição desejada.
 * É nesta função que são zerados os valores de parte de erros e outras variáveis já calculadas.
 * A nova posição é convertida e armazenada em targetLocation.
 * @param newTarget Nova Posicao
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
 * @brief Função para ligar o Pid.
 * Rotina responsável Por Ligar O PID
 * @return Void
 */
void turnOnPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOnPidStatus pidController \n");
    if(pidStatus == FALSE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus TRUE \n");
        pidStatus = TRUE;
    }
}

/**
 * @brief Função para desligar o Pid
 * Rotina responsável por desligar O PID
 *  * @return Void
 */
void turnOffPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOffPidStatus pidController \n");
    if(pidStatus == TRUE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus FALSE \n");
        pidStatus = FALSE;
    }
}

/**
 * @brief Função para setar Kp.
 * Rotina Repsonsavel por Setar Kp, valor parte da integral.
 * @param Novo KP
 */
void setControlKp(double newKp){
    if(DEBUG) printf("[DEBUG] - Starting setControlKp pidController \n");
    controlKp = newKp;
    printf("[INFO] - controlKp Value: %f \n", controlKp);
}

/**
 * @brief Função para setar Kd.
 * Rotina responsável por Setar Kd, valor parte da integral.
 * @param Novo KD
 */
void setControlKd(double newKd){
    if(DEBUG) printf("[DEBUG] - Starting setControlKd pidController \n");
    controlKd = newKd;
    printf("[INFO] - controlKd Value: %f \n", controlKd);
}

/**
 * @brief Função para setar Ki.
 * Rotina responsável por setar Ki, valor parte da integral.
 * @param Novo KI
 */
void setControlKi(double newKi){
    if(DEBUG) printf("[DEBUG] - Starting setControlKi pidController \n");
    controlKi = newKi;
    printf("[INFO] - controlKi Value: %f \n", controlKi);
}

/**
 * @brief Função Principal do PID Para Cálculo de Tensão.
 * Rotina Para fazer os cálculos do PID e suas variáveis tal como desvios e erros, retornando o valor de tensao que deve ser aplicado no motor.
 *
 * O cálculo nesta função basea-se na leitura atual da posição do motor dessa maneira gera um valor de tensão para que atinja o alvo.
 *
 * @param currentPosition Posicao Corrente
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