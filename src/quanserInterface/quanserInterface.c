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
 * @file quanserInterface.c
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Funções para funcionamento do Motor, PWM e Ponte H.
 */

#include "quanserInterface.h"

/**
 * @brief Função para setar PWM e habilitar PWM e ponte H.
 * Rotina responsável por setar o valor do duty cycle em função do valor de tensão passado por parâmetro
 *
 * Também é papel desta função de habilitar o pino de enable ponte h e setar o período do PWM,
 *
 * @param dcAmount Valor em nano segundos do Duty Cycle a ser aplicado
 * @return Retorna Positivo Caso Consiga Setar um novo Duty Cycle.
 */
int handlePwm(int dcAmount) {
    if(DEBUG) printf("[DEBUG] - Starting handlePwm\n");
    if(IS_RUNNING_LOCAL) return TRUE;
    char dataFull[20];
    snprintf(dataFull, sizeof(dataFull), "%d\n", dcAmount);
    if(writeHandler("/sys/class/gpio/gpio38/value", "1") < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/enable", "1") < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/device/pwm_period", PWM_PERIOD) < 0) return FALSE;
    if(writeHandler("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", dataFull) < 0) return FALSE;
    if(DEBUG) printf("[DEBUG] - Finishing handlePwm");
    return TRUE;
}

/**
 * @brief Função para inicialização do decoder e motor.
 * Rotina responsável pela inicialização do motor e também do decoder.
 *
 * A princípal função é garantir que os PWM, Ponte H, Decoder estão aptos a funcionarem.
 *
 * @return Retorna Positivo Caso Consiga inicializar.
 */
int qserInitializer() {
    if(DEBUG) printf("[INFO] - Initializing Qser \n");
    int initialPwaValue = 0;
    if(handlePwm(initialPwaValue) ==  FALSE){
        fprintf(stderr, "[ERROR] - Error While Trying To Set PWM Initialization\n");
        exit(0);
    }
    qserBreak();
    decoderInitializer(SPI_DEFAULT_SPEED);
    clearDecoder();
    return TRUE;
}

/**
 * @brief Função responsável por desabilitar a ponte h.
 * Rotina responsável por desabilitar a Ponte H
 * @return Retorna Positivo Caso Consiga Desabilitar.
 */
int qserBreak() {
    if(DEBUG) printf("[DEBUG] - Starting qserBreak\n");
    if(IS_RUNNING_LOCAL) return TRUE;
    if(writeHandler("/sys/class/gpio/gpio38/value", "0") < 0) {
        printf("[INFO] - Error Writing qserBreak File Value to Zero");
        return FALSE;
    }
    if(DEBUG) printf("[DEBUG] - Finishing qserBreak\n");
    return TRUE;
}

/**
 * @brief Função para converter voltagem em duty cycle.
 * Rotina responsável por transformar os valores de tensão em Duty Cycle.
 *
 * Esse função tem como objetivo transformar um valor de tensão em um valor correspondente ao percentual de 0 a 100% do duty cycle
 *
 * @param voltage Valor da voltagem a ser aplicada no Motor
 * @return Retorna o Status 1 Caso Consiga Fazer A Alteracao do Duty Cycle
 */
int qserVoltage(float voltage) {
    if(DEBUG) printf("[DEBUG] - Starting qserVoltage\n");
    float dcAmount = (( voltage + QSER_VOLTAGE ) / ( 2 * QSER_VOLTAGE )) * atof(PWM_PERIOD);
    if(DEBUG) printf("[DEBUG] - Finishing qserVoltage\n");
    return handlePwm((int)dcAmount);
}

/**
 * @brief Thread Um de interrupções de fim de curso.
 * Thread responsável por escutar interrupções de fim de curso assim como fazer a pausa do motor e o desligamento do PID.
 *
 * Interrupções sensíveis aos níveis de borda de subida e descida
 *
 * @return Retorna um Ponteiro Para Null
 */
void* jointPositionLimitOneHandler() {
    if(IS_RUNNING_LOCAL) return 0;
    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler Thread \n");
    char rootPathLimiterOneValue[100] = "/sys/class/gpio/gpio6/value";
    char rootPathLimiterOneEdge[100] = "/sys/class/gpio/gpio6/edge";

    unsigned char dataOne;
    struct pollfd pollFileHandlerOne;

    if(DEBUG) printf("[DEBUG] - JPL Opening First File GPIO 6\n");
    if((pollFileHandlerOne.fd = open(rootPathLimiterOneValue, O_RDONLY)) < 0) {
        fprintf(stderr, "[ERROR] - Joint Position Limiter One Open File Descriptor Error %s.\n", rootPathLimiterOneValue);
        exit(11);
    }

    read(pollFileHandlerOne.fd,&dataOne,1);

    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler While \n");
    int shouldNeverStop = TRUE;
    while(shouldNeverStop) {
        if(DEBUG) printf("[DEBUG] - Checking Joint Position Limiter \n");
        pollFileHandlerOne.events = POLLPRI;
        writeHandler(rootPathLimiterOneEdge,"both");
        poll(&pollFileHandlerOne,1,-1);
        lseek(pollFileHandlerOne.fd,0,SEEK_SET);
        if(DEBUG) printf("[DEBUG] - JPL Reading First File GPIO 0\n");
        if(read(pollFileHandlerOne.fd, &dataOne, 1) < 0) {
            fprintf(stderr, "[ERROR] - JPL One Reading Error %s\n\n", rootPathLimiterOneValue);
            exit(2);
        }
        if(DEBUG) printf("[DEBUG] - JPL Testing For End\n");
        if(dataOne == JPL_REACHED) {
            printf("[INFO] - JPL ONE Reached End \n\n");
            qserBreak();
            turnOffPid();
        }
        JPL_REACHED_STATUS_ONE = dataOne;

    }
    return NULL;
}
/**
 * @brief Thread Dois de interrupções de fim de curso.
 * Thread Reponseavel por escutar interrupcoes de fim de curso assim como fazer a pausa do motor e o desligamento do PID
 *
 * Interrupções sensíveis aos níveis de borda de subida e descida
 *
 * @return Retorna um Ponteiro Para Null
 */
void* jointPositionLimitTwoHandler() {
    if(IS_RUNNING_LOCAL) return 0;
    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler Thread \n");
    char rootPathLimiterTwoValue[100] = "/sys/class/gpio/gpio0/value";
    char rootPathLimiterTwoEdge[100] = "/sys/class/gpio/gpio0/edge";

    unsigned char dataTwo;
    struct pollfd pollFileHandlerTwo;

    if(DEBUG) printf("[DEBUG] - JPL Opening First File GPIO 6\n");
    if((pollFileHandlerTwo.fd = open(rootPathLimiterTwoValue, O_RDONLY)) < 0) {
        fprintf(stderr, "[ERROR] - Joint Position Limiter Two Open File Descriptor Error %s.\n", rootPathLimiterTwoValue);
        exit(11);
    }

    read(pollFileHandlerTwo.fd, &dataTwo, 1);

    if(DEBUG) printf("[DEBUG] - Starting Joint Position Limiter Handler While \n");
    int shouldNeverStop = TRUE;
    while(shouldNeverStop) {
        if(DEBUG) printf("[DEBUG] - Checking Joint Position Limiter \n");
        pollFileHandlerTwo.events = POLLPRI;
        writeHandler(rootPathLimiterTwoEdge,"both");
        poll(&pollFileHandlerTwo, 1, -1);
        lseek(pollFileHandlerTwo.fd, 0, SEEK_SET);
        if(DEBUG) printf("[DEBUG] - JPL Reading First File GPIO 0\n");
        if(read(pollFileHandlerTwo.fd, &dataTwo, 1) < 0) {
            fprintf(stderr, "[ERROR] - JPL Two Reading Error %s\n\n", rootPathLimiterTwoValue);
            exit(2);
        }
        if(DEBUG) printf("[DEBUG] - JPL Testing For End\n");
        if(dataTwo == JPL_REACHED) {
            printf("[INFO] - JPL TWO Reached End \n\n");
            qserBreak();
            turnOffPid();
        }
        JPL_REACHED_STATUS_TWO = dataTwo;
    }
    return NULL;
}

/**
 * @brief Thread para assegurar troca de posições
 * Thread Responsável por executar a alteração do braço para uma nova posição.
 *
 *
 *  Loop Infinito que verifica se o PID está ativo para aplicar as tensão necessárias.
 *
 *
 *  * @return Retorna um Ponteiro Para Null
 */
void* goToTargetPositionHandler(){
    if(DEBUG) printf("[DEBUG] - Starting goTo Target Position Handler Thread \n");
    int currentPosition = readDecoderCounter();
    while(TRUE) {
        if(pidStatus == TRUE) {
            float voltage = (float)pidHandler(currentPosition);
            if(qserVoltage(voltage) == 0) {
                fprintf(stderr, "[ERROR] - Error While Trying To Move Motor Position\n");
                return FALSE;
            }
            currentPosition = readDecoderCounter();
        }
        usleep(100);
    }
    printf("[INFO] - Reached The End goToTargetPositionHandler Thread\n");
    return NULL;
}