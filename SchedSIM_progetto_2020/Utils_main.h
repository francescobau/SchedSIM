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
//#define FILE_NAME "my_processes.txt"
#define FILE_NAME "my_processes1.txt"
//#define FILE_NAME "my_processes2.txt"
//#define FILE_NAME "my_processes3.txt"
//#define FILE_NAME "my_wrong_processes.txt"
//#define FILE_NAME "my_wrong_processes1.txt"
//#define FILE_NAME "my_wrong_processes2.txt"
//#define FILE_NAME "my_wrong_processes3.txt"
//#define FILE_NAME "empty_file.txt"

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

// Numero di possibili modalita'.
#define MODE_LENGTH SRT_MODE
// Numero massimo di token estratti da una riga di testo.
// Il numero massimo di token separatori e' MAX_TOKENS-1 .
#define MAX_TOKENS 3
// Funzione che fa scegliere all'utente la modalita'.
short int selectMode(unsigned short int debugMode);
// Funzione che scansiona rapidamente il file, contando quanti processi ci sono.
int countProcesses(char* buffer, unsigned short int debugMode);
// Funzione che preprocessa il buffer, sostituendo i token separatori in spazi.
int preProcess(char* buffer, unsigned int debugMode);
// Funzione che memorizza il contenuto del buffer nei vari array.
int importProcesses(char* buffer, struct processesData processes, unsigned short int debugMode);
// Funzione che libera lo spazio allocato dinamicamente per l'array dei nomi di processo.
void freeArray(struct processesData processes, unsigned short int amount, unsigned short int debugMode);

#endif /* UTILS_MAIN_H_ */
