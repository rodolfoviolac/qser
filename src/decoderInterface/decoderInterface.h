//
// Created by Rodolfo Carvalho on 12/1/19.
//

#ifndef QSER_DECODERINTERFACE_H
#define QSER_DECODERINTERFACE_H
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "./../helpers/helpers.h"
#if IS_RUNNING_LOCAL == FALSE
#include <linux/spi/spidev.h>
#endif

#define SPI_DEFAULT_SPEED 10000
#define BITS_PER_WORD 8


// Modo de contagem
#define NQUAD 0x00
/** @brief Codificação para contagem de quadratura X1. Incrementa/decrementa o valor do contador somente nas bordas de subida do canal A. */
#define QUADRX1 0x01
#define QUADRX2 0x02
#define QUADRX4 0x03

// Modo de rodar o contador
/** @brief Modo de contagem free run */
#define FREE_RUN 0x00
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C

// Modo do pino índice
/** @brief Desativa o pino de índice do decoder. */
#define DISABLE_INDX 0x00
#define INDX_LOADC 0x10
#define INDX_RESETC 0x20
#define INDX_LOADO 0x30
#define ASYNCH_INDX 0x00
#define SYNCH_INDX 0x80

// Modo de filtragem do clock
#define FILTER_1 0x00
/** @brief Divide a frequência do clock ligado ao pino fCLKi por 2. */
#define FILTER_2 0x80


// Configuração do registrador MDR1
// Ver manual do L7366R com muita atenção para saber o que isso significa x)


// Modos de flag
/** @brief Desativa os pinos de flag do decoder. */
#define NO_FLAGS 0x00
#define IDX_FLAG 0x10
#define CMP_FLAG 0x20
#define BW_FLAG 0x40
#define CY_FLAG 0x80

// Largura do contador
/** @brief O registrador do contador terá 4 bytes de dados. */
#define BYTE_4 0x00
#define BYTE_3 0x01
#define BYTE_2 0x02
#define BYTE_1 0x03

// Enable/disable counter
/** @brief Habilita a contagem. */
#define EN_CNTR 0x00
#define DIS_CNTR 0x04

// LS7366R op-code list
#define CLR_MDR0 0x08
#define CLR_MDR1 0x10
/** @brief Instrução que zera o contador do decoder. */
#define CLR_CNTR 0x20
#define CLR_STR 0x30
#define READ_MDR0 0x48
#define READ_MDR1 0x50
/** @brief Instrução que lê o contador do decoder. */
#define READ_CNTR 0x60
#define READ_OTR 0x68
#define READ_STR 0x70
/** @brief Instrução que seta o registrado MDR1, habilitando/desabilitando configurações. */
#define WRITE_MDR1 0x90
/** @brief Instrução que seta o registrado MDR0, habilitando/desabilitando configurações. */
#define WRITE_MDR0 0x88
#define WRITE_DTR 0x98
#define LOAD_CNTR 0xE0
#define LOAD_OTR 0xE4

void decoderInitializer(int spiSpeed);
int readDecoderCounter();
void clearDecoder();
void wrapUpDecoder();

#endif //QSER_DECODERINTERFACE_H
