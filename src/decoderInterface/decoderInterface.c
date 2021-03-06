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
 * @file decoderInterface.c
 * @author Rodolfo Viola Carvalho, Gabriel Alexandre Zillmer, Felipe Fuhr Dos Reis
 * @date 11 Dec 2019
 * @brief  Funções para fazer a interface com o decoder
 */

#include "decoderInterface.h"
/** @brief Variavel Global De Inicializacao Do Decoder Com Finalidade De Fluxo De Codigo */
int decoderInitialized = FALSE;
/** @brief Descritor de Arquivo do SPI */
int fileDescriptor = -1;
/** @brief Variavel Global Com Finalidade De Controlar Frequencia de Comunicacao do SPI */
uint32_t frequencyRate = 0;

/**
 * @brief Leitura do Registrador CNTR do Decoder com SPI IOC TRANSFER
 * Funcao para Fazer a Leitura do Decoder CNTR e Retornar Valor do Contador Lido.
 * @return Int Retorna o Status da Inicializacao Sendo, 1 feita com Sucesso.
 */
int readDecoderCounter(){
    if(DEBUG) printf("[DEBUG] - Starting readDecoderCounter Function \n");
#if IS_RUNNING_LOCAL == FALSE
    if(decoderInitialized == FALSE) {
        fprintf(stderr, "[ERROR] - SPI Device Not Initialized. Cant Read Decoder \n");
        exit(1);
    }

    struct spi_ioc_transfer message;
    if(DEBUG) printf("[DEBUG] - readDecoderCounter Before Setting txBuf and rxBuff \n");
    uint8_t rxbuf[5] = { 0xF0, 0xF1, 0xF2, 0xF3, 0xF4 };
    uint8_t txbuf[5] = { READ_CNTR, 0x00, 0x00, 0x00, 0x00 };

    if(DEBUG) printf("[DEBUG] - readDecoderCounter Setting message \n");
    message.tx_buf = (unsigned long) &txbuf;
    message.rx_buf = (unsigned long) &rxbuf;
    message.bits_per_word = BITS_PER_WORD;
    message.speed_hz = frequencyRate;
    message.len = sizeof(txbuf);

    if(DEBUG) printf("[DEBUG] - readDecoderCounter Before SPI_IOC_MESSAGE \n");
    if(ioctl(fileDescriptor, SPI_IOC_MESSAGE(1), &message) < 0){
        fprintf(stderr, "[ERROR] - While Trying to Read SPI Decoder \n");
    }

    if(DEBUG) printf("[DEBUG] - readDecoderCounter assign rxBuffer \n");
    uint32_t byte1 = rxbuf[4];
    uint32_t byte2 = rxbuf[3] << 8;
    uint32_t byte3 = rxbuf[2] << 16;
    uint32_t byte4 = rxbuf[1] << 24;

    uint32_t readOut = byte1 | byte2 | byte3 | byte4;

    if(DEBUG) printf("[DEBUG] - readDecoderCounter readOut: %d \n", readOut);
    return readOut;
#endif
}

/**
 * @brief Inicialização do Decoder com Tokens pré definidor para fazer a contagem
 * Funcao para Fazer a Inicializacao dos Tokens Necessarios para Funcionamento do Decoder Juntamente Com o SPI
 * Sao as Seguintes Configuracoes Para o MDR0: WRITE_MDR0, QUADRX1 | FREE_RUN | DISABLE_INDX | FILTER_2
 * Sao as Seguintes Configuracoes Para o MDR1: WRITE_MDR1, NO_FLAGS | BYTE_4 | EN_CNTR
 *
 * @param spiSpeed Frequencia (Hz) Para Comunicacao SPI
 * @return Void
 */
void decoderInitializer(int spiSpeed){
    if(DEBUG) printf("[DEBUG] - Starting decoderInitializer Function \n");
#if IS_RUNNING_LOCAL == FALSE
    if(decoderInitialized == TRUE) return;

    frequencyRate = spiSpeed;
    uint8_t bpw = BITS_PER_WORD;
    uint8_t mode = SPI_MODE_0;
    uint8_t lsb = 0;

    if(DEBUG) printf("[DEBUG] - Before Opening SPI Device \n");
    if((fileDescriptor = open("/dev/spidev1.0", O_RDWR)) == -1) {
        fprintf(stderr, "[ERROR] - Trying To Open SPI Device /dev/spidev1.0 \n");
        exit(1);
    }
    if(DEBUG) printf("[DEBUG] - Before Writing SPI_IOC_WR_MODE on SPI Device \n");
    if(ioctl(fileDescriptor, SPI_IOC_WR_MODE, &mode)) {
        fprintf(stderr, "[ERROR] - Not Possible To Write Clock On SPI device \n");
        exit(1);
    }
    if(DEBUG) printf("[DEBUG] - Before Writing SPI_IOC_WR_LSB_FIRST on SPI Device \n");
    if(ioctl(fileDescriptor, SPI_IOC_WR_LSB_FIRST, &lsb)) {
        fprintf(stderr, "[ERROR] - Not Possible To Write Justify Bits On SPI device \n");
        exit(1);
    }
    if(DEBUG) printf("[DEBUG] - Before Writing SPI_IOC_WR_BITS_PER_WORD on SPI Device \n");
    if(ioctl(fileDescriptor, SPI_IOC_WR_BITS_PER_WORD, &bpw)) {
        fprintf(stderr, "[ERROR] - Not Possible To Write Quantity Bits per Word On SPI device \n");
        exit(1);
    }
    if(DEBUG) printf("[DEBUG] - Before Writing SPI_IOC_WR_MAX_SPEED_HZ on SPI Device \n");
    if(ioctl(fileDescriptor, SPI_IOC_WR_MAX_SPEED_HZ, &frequencyRate)) {
        fprintf(stderr, "[ERROR] - Not Possible To Write Frequency Rate On SPI device \n");
        exit(1);
    }

    if(DEBUG) printf("[DEBUG] - decoderInitializer Setting Up Message \n");
    struct spi_ioc_transfer message;
    uint8_t rxBuffer1[2] = { 0xFF, 0xFF };
    uint8_t txBuffer1[2] = { WRITE_MDR0, QUADRX1 | FREE_RUN | DISABLE_INDX | FILTER_2 };

    if(DEBUG) printf("[DEBUG] - decoderInitializer Before Tx and Rx Buff \n");
    message.rx_buf = (unsigned long) &rxBuffer1;
    message.tx_buf = (unsigned long) &txBuffer1;
    message.bits_per_word = BITS_PER_WORD;
    message.speed_hz = spiSpeed;
    message.len = sizeof(txBuffer1);

    if(DEBUG) printf("[DEBUG] - Before Setting MDR0 Register \n");
    if(ioctl(fileDescriptor, SPI_IOC_MESSAGE(1), &message) < 0){
        fprintf(stderr, "[ERROR] - While Trying to Set MDR0 Register \n");
    }

    uint8_t rxBuffer2[2] = { 0xFF, 0xFF };
    uint8_t txBuffer2[2] = { WRITE_MDR1, NO_FLAGS | BYTE_4 | EN_CNTR };
    message.tx_buf = (unsigned long) &txBuffer2;
    message.rx_buf = (unsigned long) &rxBuffer2;
    message.len = sizeof(txBuffer2);

    if(DEBUG) printf("[DEBUG] - Before Setting MDR1 Register \n");
    if(ioctl(fileDescriptor, SPI_IOC_MESSAGE(1), &message) < 0) {
        fprintf(stderr, "[ERROR] - While Trying to Set MDR1 Register \n");
    }

    uint8_t txBuffer3[1] = { CLR_CNTR };
    uint8_t rxBuffer3[1] = { 0xFF };
    message.tx_buf = (unsigned long) &txBuffer3;
    message.rx_buf = (unsigned long) &rxBuffer3;
    message.len = sizeof(txBuffer3);

    if(DEBUG) printf("[DEBUG] - Before First Cleaning Decoder \n");
    if(ioctl(fileDescriptor, SPI_IOC_MESSAGE(1), &message) < 0){
        printf("[ERROR] - While Cleaning Decoder\n");
    }

    uint8_t rxBuffer4[5] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t txBuffer4[5] = { WRITE_DTR, 0x00, 0x00, 0x00, 0x00 };
    message.tx_buf = (unsigned long) &txBuffer4;
    message.rx_buf = (unsigned long) &rxBuffer4;
    message.len = sizeof(txBuffer4);

    if(DEBUG) printf("[DEBUG] - Before Setting DTR \n");
    if(ioctl(fileDescriptor, SPI_IOC_MESSAGE(1), &message) < 0) {
        printf("[ERROR] - While Setting DTR \n");
    }

    uint8_t txBuffer5[1] = { LOAD_CNTR };
    uint8_t rxBuffer5[1] = { 0xFF };
    message.tx_buf = (unsigned long) &txBuffer5;
    message.rx_buf = (unsigned long) &rxBuffer5;
    message.len = sizeof(txBuffer5);

    if(DEBUG) printf("[DEBUG] - Before Setting LOAD_CNTR \n");
    if(ioctl(fileDescriptor, SPI_IOC_MESSAGE(1), &message) < 0){
        printf("[ERROR] - While Setting CNTR\n");
    }

    decoderInitialized = TRUE;
#endif
}


/**
 * @brief Função Para Limpar o Contador do Decoder.
 * Rotina para Zerar o Contador do Decoder, faz isso por meio da instrução CLR_CNTR
 * @return Void
 */
void clearDecoder(){
    if(DEBUG) printf("[DEBUG] - Starting clearDecoder Function \n");
#if IS_RUNNING_LOCAL == FALSE
    if(decoderInitialized == FALSE){
        fprintf(stderr, "[ERROR] - SPI Device Not Initialized. Cant Clear Decoder \n");
        exit(1);
    }

    if(DEBUG) printf("[DEBUG] - clearDecoder Setting Message Clear Content \n");
    struct spi_ioc_transfer message;
    uint8_t txBuffer[1] = { CLR_CNTR };
    uint8_t rxBuffer[1] = { 0xFF };
    message.tx_buf = (unsigned long) &txBuffer;
    message.rx_buf = (unsigned long) &rxBuffer;
    message.bits_per_word = BITS_PER_WORD;
    message.speed_hz = frequencyRate;
    message.len = sizeof(txBuffer);

    if(DEBUG) printf("[DEBUG] - clearDecoder Before SPI_IOC_MESSAGE \n");
    if(ioctl(fileDescriptor, SPI_IOC_MESSAGE(1), &message) < 0){
        fprintf(stderr, "[ERROR] - While Trying To Clear Decoder \n");
    };
    return;
#endif
}

/**
 * @brief Função para desligamento e reset das variáveis do decoder.
 * Funcao para fazer a limpeza das variaveis, setar decoder como nao inicializado e fechar a comunicacao SPI
 * @return Void
 */
void wrapUpDecoder(){
    if(DEBUG) printf("[DEBUG] - Starting wrapUpDecoder Function \n");
    if(decoderInitialized == FALSE){
        fprintf(stderr, "[ERROR] - SPI Device Not Initialized. Cant Wrap Up Decoder \n");
        exit(1);
    }
    decoderInitialized = FALSE;
    frequencyRate = 0;
    close(fileDescriptor);
    fileDescriptor = -1;
    if(DEBUG) printf("[DEBUG] - Done wrapUpDecoder Function \n");
}