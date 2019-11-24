#include "helpers.h"

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