/*
 * Utils_main.h
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */

#ifndef UTILS_MAIN_H_
#define UTILS_MAIN_H_

// Header della libreria
#include "SchedulerFCFS.h"
#include "SchedulerRR.h"
#include "SchedulerPS.h"
#include "SchedulerSPN.h"
#include "SchedulerSRT.h"

// Nome del file
#define FILE_NAME "my_processes.txt"

// Modalita' disponibili nel menu.
#define FCFS_MODE 1
#define RR_MODE 2
#define PS_MODE 3
#define SPN_MODE 4
#define SRT_MODE 5

// Dimensione dell'area allocata di default.
#define DEFAULT_SIZE 1000
// Modalita' di default.
#define DEFAULT_MODE FCFS_MODE

// Numero di possibili modalita', e il codice per modalita' invalida.
#define MODE_LENGTH SRT_MODE
#define INVALID_MODE EOF
//TODO: Specifiche
unsigned short int selectMode(unsigned short int debugMode);
//TODO: Specifiche
int countProcesses(char* buffer, unsigned short int debugMode);
//TODO: Specifiche
int preProcess(char* buffer, unsigned int debugMode);
//TODO: Specifiche
int importProcesses(char* buffer, unsigned int length, char* processes[length], unsigned int arrivals[length], unsigned int durations[length]);
//TODO: Specifiche
void freeArray(unsigned int length, char* processes[length], unsigned short int debugMode);

#endif /* UTILS_MAIN_H_ */
