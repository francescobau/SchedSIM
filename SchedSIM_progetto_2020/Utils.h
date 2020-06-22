/*
 * Utils.h
 *
 *      @author		Francesco Bau' 1136850
 *  	@since		16 giu 2020
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

// Importazione condizionata di <string.h> .
#ifndef STRING_H_
#include <string.h>
#endif /* STRING_H_ */

/**
 * La struttura contenente le proprieta' dei processi, e le liste di gestione dei processi.
 *
 * @param debugMode		0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @param length		Il numero di processi.
 * @param lenRL			Puntatore al numero di processi in Ready List.
 * @param lenURL		Puntatore al numero di processi in unReadyList
 * @param processes 	Puntatore alla lista di nomi dei vari processi.
 * @param arrivals		Puntatore alla lista contenente i tempi di arrivo dei vari processi.
 * @param durations		Puntatore alla lista contenente le durate dei vari processi.
 * @param readyList		Puntatore alla Ready List.
 * @param unReadyList	Puntatore alla unReady List (lista di processi non ancora in Ready List).
 * @param leftovers		Puntatore alla lista contenente i tempi rimanenti dei vari processi.
 * @param priorities	Puntatore alla lista contenente le priorita' dei vari processi.
 */
struct processesData {
	unsigned short int debugMode;
	unsigned int length;
	unsigned int *lenRL;
	unsigned int *lenURL;
	char **processes;
	unsigned int *arrivals;
	unsigned int *durations;
	unsigned int *readyList;
	unsigned int *unReadyList;
	unsigned int *leftovers;
	unsigned int *priorities;
};

/**
 * enum che specifica se si vuole effettuare una certa operazione
 * dalla Ready List o dalla unReady List.
 *
 * TODO: Estendere enum.
 */
enum listType {
	readyList, unReadyList
};

// Funzione che controlla quali processi entrano in RL ad un certo istante time.
unsigned int checkArrivals(unsigned int time, struct processesData processes);
// Funzione che ripristina RL e uRL allo stato iniziale.
void restoreLists(struct processesData processes);
// Funzione che inserisce un processo in RL ad un certo indice.
int addProcessAt(unsigned int processIndex, unsigned int targetIndex,
		struct processesData processes);
// Funzione che rimuove un processo da RL o da uRL ad un certo indice.
int removeProcessAt(unsigned int targetIndex, struct processesData processes,
		enum listType lt);
// Funzione che mette un processo in coda a RL.
int enqueue(unsigned int processIndex, struct processesData processes);
// Funzione che rimuove il primo processo in RL o uRL.
int dequeue(struct processesData processes, enum listType lt);
// Funzione che sposta in testa un processo da uRL.
int putOnHead(unsigned int targetIndex, struct processesData processes);
// Funzione che stampa in stderr che l'indice cercato non e' valido.
void nonValidIndexError(unsigned int targetIndex);
// Funzione che riordina la unReady list. Viene usato un Bubble Sort ottimizzato.
// TODO: Implementare algoritmo migliore.
void sortPerArrival(struct processesData processes);
// Funzione per stampare il contenuto di RL o di uRL.
int printArray(struct processesData processes, enum listType lt);
#endif /* UTILS_H_ */
