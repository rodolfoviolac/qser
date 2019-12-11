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
 * @file userInterface.c
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Header File for The User Interface.
 */

#include "userInterface.h"

/**
 * @brief Function For Print Users Options
 * Funcao para imprimir no Terminal os Comandos Possiveis para o usuario
 */
void printUserOptions(){
    printf("########### QSER OPTIONS ##############\n\n");
    printf("--> speed [0 - 100] \n");
    printf("--> goforv [-V - +V] \n");
    printf("--> shiftrad [π - 2π] (double value) \n");
    printf("--> cleardec \n");
    printf("--> getdec \n");
    printf("--> getdecrad \n");
    printf("--> jpl \n");
    printf("--> break \n");
    printf("--> help \n");
    printf("--> exit \n\n");
    printf("######################################\n\n");
}

/**
 * @brief Function For Print Members Name
 * Funcao para Imprimir no Terminal os Nomes dos Integrantes do Grupo
 */
void printUserGroupsName(){
    printf("########### QSER 2019/2 ##############\n");
    printf("> Rodolfo Viola Carvalho\n");
    printf("> Gabriel Alexandre Zillmer\n");
    printf("> Felipe Fuhr Dos Reis\n");
    printf("######################################\n\n");
}

/**
 * @brief Function For Handling User Input Options
 * Funcao para retornar a opcao escolhida pelo usuario no menu de opcoes.
 * @param Valor digitado pelo usuario
 * @return Retorna o ID do do Comando Digitado Pelo Usuario
 */
int resolveOption(char* cmd) {
    if (strncmp(cmd, "speed", 5) == 0) { return OPTION_SPEED; }
    else if (strcmp(cmd, "jpl\n") == 0) { return OPTION_JPL; }
    else if (strncmp(cmd, "goforv", 6) == 0) { return OPTION_GO_FOR_V; }
    else if (strcmp(cmd, "break\n") == 0) { return OPTION_QSER_BREAK; }
    else if (strcmp(cmd, "help\n") == 0) { return OPTION_HELP; }
    else if (strcmp(cmd, "exit\n") == 0) { return OPTION_EXIT; }
    else if (strncmp(cmd, "shiftrad", 8) == 0) { return OPTION_SHIFT_RAD; }
    else if (strncmp(cmd, "setkp", 5) == 0) { return OPTION_SET_KP; }
    else if (strncmp(cmd, "setkd", 5) == 0) { return OPTION_SET_KD; }
    else if (strncmp(cmd, "setki", 5) == 0) { return OPTION_SET_KI; }
    else if (strncmp(cmd, "setccu", 6) == 0) { return OPTION_SET_CCU; }
    else if (strcmp(cmd, "cleardec\n") == 0) { return OPTION_CLEAR_DEC; }
    else if (strcmp(cmd, "getdec\n") == 0) { return OPTION_READ_DEC; }
    else if (strcmp(cmd, "getdecrad\n") == 0) { return OPTION_READ_DEC_RAD; }
    else return OPTION_INVALID;
}