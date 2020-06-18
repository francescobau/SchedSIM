/*
 * Utils.h
 *
 *  Created on: 16 giu 2020
 *      Author: francesco
 */

#ifndef UTILS_H_
#define UTILS_H_

// Importazione condizionata di <stdio.h> .
#ifndef STDIO_H_
#include <stdio.h>
#endif /* STDIO_H_ */

// Importazione condizionata di <stdlib.h> .
#ifndef STDLIB_H_
#include <stdlib.h>
#endif /* STDLIB_H_ */

struct processesData{
	unsigned int length;
	unsigned int* lenRL;
	unsigned int* lenURL;
	char** processes;
	unsigned int* arrivals;
	unsigned int* durations;
	unsigned int* readyList;
	unsigned int* unReadyList;
};

// enum per specificare se si vuole effettuare l'operazione
// dalla Ready List o dalla unReady List.
enum listType {readyList,unReadyList};

// Funzione per controllare quali processi entrano in RL ad un certo istante time.
unsigned int checkArrivals(unsigned int time, struct processesData processes, unsigned short int debugMode);
// Funzione che ripristina lo stato della RL e della uRL allo stato iniziale.
void restoreQueues(struct processesData processes, unsigned short int debugMode);
// Funzione che inserisce un processo in RL ad un certo indice.
int addProcessAt(unsigned int processIndex, unsigned int targetIndex, struct processesData processes, unsigned short int debugMode);
// Funzione che rimuove un processo da RL o da uRL ad un certo indice.
int removeProcessAt(unsigned int targetIndex, struct processesData processes, enum listType lt, unsigned short int debugMode);
// Funzione che mette un processo in coda a RL.
int enqueue(unsigned int processIndex, struct processesData processes, unsigned short int debugMode);
// Funzione che rimuove il primo processo in RL o uRL.
int dequeue(struct processesData processes, enum listType lt, unsigned short int debugMode);
// Funzione che sposta in testa un processo da uRL.
int putOnHead(unsigned int targetIndex, struct processesData processes, unsigned short int debugMode);
// Funzione che stampa in stderr che l'indice cercato non e' valido.
void nonValidIndexError(unsigned int targetIndex);
// Funzione che riordina la unReady list. Viene usato Bubble Sort.
// TODO: Implementare algoritmo migliore.
void sortPerArrival(struct processesData processes, unsigned short int debugMode);
// Funzione per stampare il contenuto di RL o di uRL.
int printArray(struct processesData processes, enum listType lt, unsigned short int debugMode);
#endif /* UTILS_H_ */
