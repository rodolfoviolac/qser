//
// Created by Rodolfo Carvalho on 11/23/19.
//

#ifndef QSER_HELPERS_H
#define QSER_HELPERS_H
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int writeHandler(const char filePath[], const char data[]);

#endif //QSER_HELPERS_H