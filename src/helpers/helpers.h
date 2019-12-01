//
// Created by Rodolfo Carvalho on 11/23/19.
//

#ifndef QSER_HELPERS_H
#define QSER_HELPERS_H
#define IS_RUNNING_LOCAL 1
#define DEBUG 0
#define TRUE 1
#define FALSE 0
#define PI 3.141592653589793238462643383279
#define MAX_RANGE 180.00
#define RAD2G MAX_RANGE/PI
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int writeHandler(const char filePath[], const char data[]);
char *readHandler(char *data, int size, const char filePath[]);

#endif //QSER_HELPERS_H
