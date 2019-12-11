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
 * @file decoderInterface.h
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Header Files for the decoder Interface
 */


#ifndef QSER_DECODERINTERFACE_H
#define QSER_DECODERINTERFACE_H
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "./../helpers/helpers.h"
#if IS_RUNNING_LOCAL == FALSE
#include <linux/spi/spidev.h>
#endif

/** @brief Define A Velocidade Do SPI. */
#define SPI_DEFAULT_SPEED 10000
/** @brief Define Quantidade de Bits por Palavra do Decoder. */
#define BITS_PER_WORD 8


/** @brief Tokens Para Codificacao de Contagem de Quadratura. */
#define NQUAD 0x00
#define QUADRX1 0x01
#define QUADRX2 0x02
#define QUADRX4 0x03

/** @brief Tokens de Modo de Contagem. */
#define FREE_RUN 0x00
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C

/** @brief Tokens de Pino de Indice. */
#define DISABLE_INDX 0x00
#define INDX_LOADC 0x10
#define INDX_RESETC 0x20
#define INDX_LOADO 0x30
#define ASYNCH_INDX 0x00
#define SYNCH_INDX 0x80

/** @brief Tokens de Para Frequencia. */
#define FILTER_1 0x00
#define FILTER_2 0x80

/** @brief Tokens para Flags. */
#define NO_FLAGS 0x00
#define IDX_FLAG 0x10
#define CMP_FLAG 0x20
#define BW_FLAG 0x40
#define CY_FLAG 0x80

/** @brief Tokens Para Largura Contador. */
#define BYTE_4 0x00
#define BYTE_3 0x01
#define BYTE_2 0x02
#define BYTE_1 0x03

/** @brief Tokens Para Habilitar Contagem. */
#define EN_CNTR 0x00
#define DIS_CNTR 0x04


/** @brief Tokens de Proposito Geral, Read, Zerar, Decoder e Set do Registradores */
#define CLR_MDR0 0x08
#define CLR_MDR1 0x10
#define CLR_CNTR 0x20
#define CLR_STR 0x30
#define READ_MDR0 0x48
#define READ_MDR1 0x50
#define READ_CNTR 0x60
#define READ_OTR 0x68
#define READ_STR 0x70
#define WRITE_MDR1 0x90
#define WRITE_MDR0 0x88
#define WRITE_DTR 0x98
#define LOAD_CNTR 0xE0
#define LOAD_OTR 0xE4

void decoderInitializer(int spiSpeed);
int readDecoderCounter();
void clearDecoder();
void wrapUpDecoder();

#endif //QSER_DECODERINTERFACE_H
