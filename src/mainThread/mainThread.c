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
 * @file mainThread.c
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Thread Principal para controlar fluxo do usuário e comandos.
 */

#include "mainThread.h"
/** @brief Status do final de curso um */
int JPL_REACHED_STATUS_ONE = 0;
/** @brief Status do final de curso dois */
int JPL_REACHED_STATUS_TWO = 0;


/**
 * @brief Main Thread para interface com usuário e controle de fluxo.
 * Thread responsável por esperar comando do usuário e fazer a chamad necessária da API para executar a ação.
 *
 * É nessa thread que é feita excutada as funções da biblioteca, repetidamente espera em um loop infito um comando de um usuário
 * para sair e encerrar o programa é necessario um comando Exit.
 *
 * @return Retorna um Ponteiro para Null
 */
void* handlerMainThread() {
    if(DEBUG) printf("[DEBUG] - Starting handlerMainThread \n");
    printUserGroupsName();
    printUserOptions();

    char command[100];
    while (fgets(command, sizeof(command), stdin)) {
        if(DEBUG) printf("[DEBUG] - Inside Command While MainThread \n");
        switch (resolveOption(command)) {
            case OPTION_SPEED: {
                if(DEBUG) printf("[DEBUG] - Got SPEED Option MainThread \n");
                float commandAmount = atof(&command[6]);
                if(commandAmount > 100 || commandAmount < 0) {
                    printf("[ERROR] - Speed Amount Must Be [0-100]\n");
                } else {
                    if(DEBUG) printf("[DEBUG] - Got Valid Speed Number MainThread \n");
                    float dcAmount = (commandAmount/100)*atof(PWM_PERIOD);
                    if(handlePwm((int)dcAmount) == 1) {
                        fprintf(stdout, "[INFO] MT - Motor Duty Cycle %d%%\n\n", (int)dcAmount/10000);
                    } else {
                        printf("[ERROR] MT - Error Turning On Motor\n\n");
                    }
                }
                break;
            }
            case OPTION_JPL: {
                if(DEBUG) printf("[DEBUG] - Got JPL Option MainThread \n");
                if(JPL_REACHED_STATUS_ONE == JPL_REACHED){
                    printf("[INFO] MT - JPL ONE Reached The End. State: Active [ %d ]\n", JPL_REACHED_STATUS_ONE);
                } else printf("[INFO] MT - READ JPL ONE. State: Inactive [ %d ]\n", JPL_REACHED_STATUS_ONE);
                if(JPL_REACHED_STATUS_TWO == JPL_REACHED){
                    printf("[INFO] MT - JPL TWO Reached The End. State: Active [ %d ]\n\n", JPL_REACHED_STATUS_TWO);
                } else printf("[INFO] MT - READ JPL TWO. State: Inactive [ %d ]\n\n", JPL_REACHED_STATUS_TWO);
                break;
            }
            case OPTION_GO_FOR_V: {
                if(DEBUG) printf("[DEBUG] - Got GO FOR V Option MainThread \n");
                float commandAmount = atof(&command[7]);
                if(commandAmount < -QSER_VOLTAGE || commandAmount > QSER_VOLTAGE) {
                    fprintf(stderr, "[ERROR] - Voltage Must Be On The Interval [%+d,%+d]\n", (int) -QSER_VOLTAGE, (int) QSER_VOLTAGE);
                } else {
                    if(DEBUG) printf("[DEBUG] MT - Got Accepted Voltage \n");
                    if(qserVoltage(commandAmount) == 1)	{
                        fprintf(stdout, "[INFO] - Motor Triggered With Voltage  %+.1fV\n\n", commandAmount);
                    } else {
                        fprintf(stdout, "[ERROR] - Something Went Wrong Trying To Turn On Motor\n\n");
                    }
                }
                break;
            }
            case OPTION_QSER_BREAK: {
                if(DEBUG) printf("[DEBUG] - Got QSER BREAK Option MainThread\n");
                if(qserBreak() == TRUE){
                    turnOffPid();
                    printf("[INFO] - Breaking Motor\n");
                } else {
                    fprintf(stdout, "[ERROR] - Something Went Wrong Trying To Break Motor\n\n");
                }
                break;
            }
                /** @brief  Função para Setar Posição de Target em Radianos.
                 *
                 * Essa Rotina é responsável por fazer o cálculo de conversão de Radianos para uma posição do motor;
                 * Do datasheet do motor temos que 1 revolução é igual a 4096 counts.
                 * (4096 / 360) = 1 grau ou 0.0174533 rad
                 *
                 */
            case OPTION_SHIFT_RAD: {
                if(DEBUG) printf("[DEBUG] - Got OPTION_SHIFT_RAD Option MainThread\n");
                double commandAmount = (double)strtof(&command[9], NULL);
                if(commandAmount < 0 || commandAmount > PI){
                    printf("[Error] - Radian Must Be On The Interval [0, %f] \n", PI);
                    break;
                }
                int targetMotorPosition = commandAmount * (MAX_RANGE / PI) * MOTOR_REVOLUTIONS;
                setTarget(targetMotorPosition);
                turnOnPid();
                break;
            }
            case OPTION_SET_KD: {
                if(DEBUG) printf("[DEBUG] - Got OPTION_SET_KD Option MainThread \n");
                double commandAmount = (double)strtof(&command[6], NULL);
                setControlKd(commandAmount);
                break;
            }
            case OPTION_SET_KP: {
                if(DEBUG) printf("[DEBUG] - Got OPTION_SET_KP Option MainThread \n");
                double commandAmount = (double)strtof(&command[6], NULL);
                setControlKp(commandAmount);
                break;
            }
            case OPTION_SET_KI: {
                if(DEBUG) printf("[DEBUG] - Got OPTION_SET_KI Option MainThread \n");
                double commandAmount = (double)strtof(&command[6], NULL);
                setControlKi(commandAmount);
                break;
            }
            case OPTION_CLEAR_DEC: {
                if(DEBUG) printf("[DEBUG] - Got OPTION_CLEAR_DEC Option MainThread\n");
                clearDecoder();
                printf("[INFO] - Cleaning Decoder\n\n");
                break;
            }
            case OPTION_READ_DEC: {
                if(DEBUG) printf("[DEBUG] - Got OPTION_READ_DEC Option MainThread\n");
                int counterDecoder = readDecoderCounter();
                printf("[INFO] - Decoder Reading: %d \n\n", counterDecoder);
                break;
            }
            /** @brief  Leitura do decoder e transformação para Radianos.
             *
             * Essa Rotina é responsável por fazer o cálculo de conversão da leitura do decoder para posição em radianos;
             * Do datasheet do motor temos que 1 revolução é igual a 4096 counts.
             * (4096 / 360) = 1 grau ou 0.0174533 rad
             *
             * */
            case OPTION_READ_DEC_RAD: {
                if(DEBUG) printf("[DEBUG] - Got OPTION_READ_DEC_RAD Option MainThread\n");
                int counterDecoder = readDecoderCounter();
                double revCount = (float)counterDecoder / MOTOR_REVOLUTIONS;
                double radDec = revCount * PI / MAX_RANGE;
                printf("[INFO] - Decoder Reading: %f \n\n", radDec);
                break;
            }
            case OPTION_HELP: {
                if(DEBUG) printf("[DEBUG] - Got HELP Option MainThread\n");
                printUserOptions();
                break;
            }
            case OPTION_EXIT: {
                if(DEBUG) printf("[DEBUG] - Got EXIT Option MainThread\n");
                qserBreak();
                turnOffPid();
                wrapUpDecoder();
                printf("[INFO] - Finishing Application...\n");
                exit(0);
            }
            case OPTION_INVALID: {
                if(DEBUG) printf("[DEBUG] - Got INVALID Option MainThread\n");
                printf("[ERROR] - Command Invalid Type Help For The Command List\n");
                break;
            }
            default: {
                if(DEBUG) printf("[DEBUG] - Got DEFAULT Option MainThread\n");
                printf("[ERROR] - Command Invalid Type Help For The Command List\n");
            }
        }
    }
    return NULL;
}