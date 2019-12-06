#include "pidControler.h"

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
double allErrorsSummation = 0.0;
double conversionCoefficientUnit = 294.0;
int pidStatus = 0;

int setTarget(int newTarget) {
    if(DEBUG) printf("[DEBUG] - Starting setTarget pidControler \n");
    targetLocation = newTarget;
    errorDeviation = 0.0;
    allErrorsSummation = 0.0;
    printf("[INFO] - new Target Location set to %d \n", targetLocation);
    if(DEBUG) printf("[DEBUG] - Set targetLocation to %d \n", targetLocation);
    return TRUE;
}

void turnOnPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOnPidStatus pidControler \n");
    if(pidStatus == FALSE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus TRUE \n");
        pidStatus = TRUE;
    }
}

void turnOffPid(){
    if(DEBUG) printf("[DEBUG] - Starting turnOffPidStatus pidControler \n");
    if(pidStatus == TRUE){
        if(DEBUG) printf("[DEBUG] - Setting pidStatus FALSE \n");
        pidStatus = FALSE;
    }
}


void setControlKp(double newKp){
    if(DEBUG) printf("[DEBUG] - Starting setControlKp pidControler \n");
    controlKp = newKp;
    printf("[INFO] - controlKp Value: %f \n", controlKp);
}

void setControlKd(double newKd){
    if(DEBUG) printf("[DEBUG] - Starting setControlKd pidControler \n");
    controlKd = newKd;
    printf("[INFO] - controlKd Value: %f \n", controlKd);
}

void setControlKi(double newKi){
    if(DEBUG) printf("[DEBUG] - Starting setControlKi pidControler \n");
    controlKi = newKi;
    printf("[INFO] - controlKi Value: %f \n", controlKi);
}

void setConversionCoefficientUnit(double newConversionCoefficientUnit){
    if(DEBUG) printf("[DEBUG] - Starting setConversionCoefficientUnit pidControler \n");
    conversionCoefficientUnit = newConversionCoefficientUnit;
    printf("[INFO] - conversionCoefficientUnit Value: %f \n", conversionCoefficientUnit);
}

double pidHandler(int currentPosition){
    if(DEBUG) printf("[DEBUG] - Starting pidHandler pidControler \n");
    double pidUnitVoltage;
    double pPart;
    double iPart;
    double dPart;
    double deviation;
    double tempErrorDeviation = targetLocation - currentPosition;

    allErrorsSummation += tempErrorDeviation;
    deviation = tempErrorDeviation - errorDeviation;
    errorDeviation = tempErrorDeviation;
    pPart = controlKp * tempErrorDeviation;
    iPart = controlKi * allErrorsSummation;
    dPart = controlKd * deviation;

    pidUnitVoltage = pPart + iPart + dPart;

    if(pidUnitVoltage > QSER_VOLTAGE) pidUnitVoltage = QSER_VOLTAGE;
    if(pidUnitVoltage < -QSER_VOLTAGE) pidUnitVoltage = -QSER_VOLTAGE;

    printf("[INFO] - PID Voltage Result %f \n", pidUnitVoltage);
    return pidUnitVoltage;
}