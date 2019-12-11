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
 * @file main.c
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Initial File
 */

#include <stdio.h>
#include "pthread.h"
#include "math.h"
#include "mainThread/mainThread.h"

/**
 * @brief Main File For Entrance Of The Qser
 * Funcao main responsavel pela criacao das thread do usuario.
 */
int main() {
    if(DEBUG) printf("[DEBUG] - Starting Application \n");
    pthread_t userThread;
    pthread_t positionHandlerOneThread;
    pthread_t positionHandlerTwoThread;
    pthread_t PIDThread;


    if(qserInitializer() == TRUE){
        printf("\n\n---------------------------------\n");
        printf("[INFO] - Qser Is Booming! \n");
        printf("---------------------------------\n\n");
    } else {
        printf("[ERROR] - Not Possible To Initializer Qser! \n");
        exit(1);
    }

    if(DEBUG) printf("[DEBUG] - Calling JPL Thread \n");
    pthread_create(&positionHandlerOneThread, NULL, jointPositionLimitOneHandler, NULL);
    pthread_create(&positionHandlerTwoThread, NULL, jointPositionLimitTwoHandler, NULL);
    if(DEBUG) printf("[DEBUG] - Calling User Thread \n");
    pthread_create(&userThread, NULL, handlerMainThread, NULL);
    if(DEBUG) printf("[DEBUG] - Calling PID Thread \n");
    pthread_create(&PIDThread, NULL, goToTargetPositionHandler, NULL);

    pthread_join(positionHandlerOneThread, NULL);
    pthread_join(positionHandlerTwoThread, NULL);
    pthread_join(userThread, NULL);
    pthread_join(PIDThread, NULL);
    return 0;
}