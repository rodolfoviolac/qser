#include "helpers.h"

int writeHandler(const char filePath[], const char data[]){
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
    return returnHandler;
}