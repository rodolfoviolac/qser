//
// Created by Rodolfo Carvalho on 12/1/19.
//

#ifndef QSER_DECODERINTERFACE_H
#define QSER_DECODERINTERFACE_H
#define SPI_DEFAULT_SPEED 10000

void decoderInitializer(int spiSpeed);
int readDecoderCounter();
void clearDecoder();

#endif //QSER_DECODERINTERFACE_H
