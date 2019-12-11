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
 * @file helpers.c
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Helpers Functions For Handling General Purpose
 */

#include "helpers.h"

/**
 * @brief Write Handler For Helping Writing To Files
 * Funcao para facilitar a escrita em arquivos.
 * @param filePath Caminho do Arquivo a ser escrito
 * @param data Dados a serem escritos
 * @return Retorna o Status da Escrita
 */
int writeHandler(const char filePath[], const char data[]){
    if(DEBUG) printf("[DEBUG] - Starting Writing File");
    int fileHandler = open(filePath, O_WRONLY);
    if(fileHandler == -1) {
        fprintf(stderr, "[ERROR] - Not Possible To Open File %s.\n", filePath);
        return -1;
    }
    int returnHandler = write(fileHandler, data, strlen(data));
    if(returnHandler == -1) {
        fprintf(stderr, "[ERROR] - Not Possible to Write [ %s ] on %s.\n", data, filePath);
        return -1;
    }
    close(fileHandler);
    if(DEBUG) printf("[DEBUG] - Successful Writing File");
    return returnHandler;
}

/**
 * @brief Read Handler For Helping Reading From Files
 * Funcao Para Facilitar a Leitra de Arquivos.
 * @param filePath Caminho Do Arquivo a ser lido
 * @param data Ponteiro para onde será lido
 * @param size Quantidade em Bits de informacoes a serem lida
 * @return Retorna a Informacao Lida
 */
char *readHandler(char *data, int size, const char filePath[]){
    if(DEBUG) printf("[DEBUG] - Starting Reading File");
    int fileHandler;
    if(( fileHandler = open(filePath,O_RDONLY)) == -1) {
        fprintf(stderr, "[ERROR] - Not Possible To Read File %s.\n", filePath);
        return NULL;
    }
    read(fileHandler,data,size);
    close(fileHandler);
    if(DEBUG) printf("[DEBUG] - Reading File: %s", data);
    if(DEBUG) printf("[DEBUG] - Successful Reading File");
    return data;
}