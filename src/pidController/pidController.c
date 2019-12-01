#include "pidController.h"

/** @brief Ganho integral */
double controlKi = 0.0;
/** @brief Ganho proporcional */
double controlKp = 0.005;
/** @brief Ganho derivativo */
double controlKd = 0.0;
/** @brief A posição alvo (uma posição angular convertida em contagem do decoder) */
int targetLocation = 0;
/** @brief Armazena o último erro calculado pelo controle PID. Necessário para calcular a derivada do erro */
double errorDeviation = 0.00;
/** @brief Somatório de todos os erros já calculados */
double allErrorsIntegral = 0.0;
double conversionCoefficientUnit = 294.0;
int pidStatus = 0;

int setTarget(int newTarget) {
    if(DEBUG) printf("[DEBUG] - Starting setTarget pidController");
    targetLocation = newTarget;
    errorDeviation = 0.0;
    allErrorsIntegral = 0.0;
    printf("[INFO] - new Target Location set to %d", targetLocation);
    if(DEBUG) printf("[DEBUG] - Set targetLocation to %d", targetLocation);
    return TRUE;
}

void turnOnPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOnPidStatus pidController \n");
    if(pidStatus == FALSE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus TRUE \n");
        pidStatus = TRUE;
    }
}

void turnOffPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOffPidStatus pidController \n");
    if(pidStatus == TRUE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus FALSE \n");
        pidStatus = FALSE;
    }
}


void setControlKp(double newKp){
    if(DEBUG) printf("[DEBUG] - Starting setControlKp pidController \n");
    controlKp = newKp;
    printf("[INFO] - controlKp Value: %f \n", controlKp);
}

void setControlKd(double newKd){
    if(DEBUG) printf("[DEBUG] - Starting setControlKd pidController \n");
    controlKd = newKd;
    printf("[INFO] - controlKd Value: %f \n", controlKd);
}

void setControlKi(double newKi){
    if(DEBUG) printf("[DEBUG] - Starting setControlKi pidController \n");
    controlKi = newKi;
    printf("[INFO] - controlKi Value: %f \n", controlKi);
}

void setConversionCoefficientUnit(double newConversionCoefficientUnit){
    if(DEBUG) printf("[DEBUG] - Starting setConversionCoefficientUnit pidController \n");
    conversionCoefficientUnit = newConversionCoefficientUnit;
    printf("[INFO] - conversionCoefficientUnit Value: %f \n", conversionCoefficientUnit);
}