/*
 * MyScheduler.c
 *
 *  Created on:		1 giu 2020
 *      Author:		Francesco Bau'
 *      Matricola:	1136850
 *
 * Questo programma simula uno scheduler, considerando il computer a singolo core.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Utils_main.h"

void notAvailable(unsigned int mode){
	fprintf(stderr,"La modalita' scelta (%u) non e' attualmente disponibile.\n",mode);
}

int main(int argc, char * argv[]){
	FILE *file;
	file = fopen(FILE_NAME,"r");
	// Controllo del file. Se non si riesce ad aprire, termina il programma.
	if (file == NULL) {
		fprintf(stderr, "Can't open %s\n",FILE_NAME);
		exit(EXIT_FAILURE);
	}
	// I puntatori ai dati verranno memorizzati in questa struct.
	struct processesData structure;
	int numberOfProcesses = 0;
	short int mode = DEFAULT_MODE;
	unsigned short int dynamicAllocations = 0;
	unsigned short int debugMode = 0;

	/** DEBUG MODE (passato per argomento):
	 * 0) [DEFAULT] DISATTIVATO (Modalita' essenziale - release)
	 * != 0) ATTIVATO (Modalita' debug)
	*/
	if(argc>1)
		sscanf(argv[1],"%hu",&debugMode);
	printf("DEBUG_MODE: %d\n",debugMode);

	// Buffer per la lettura dei dati in input.
	// Nella calloc si aggiunge un byte per il carattere \0 nel buffer.
	char* buffer = (char*) calloc(DEFAULT_SIZE+1,1);

	// Memorizzo il file nel buffer.
	fread(buffer,sizeof(char),DEFAULT_SIZE+1,file);

	// Conto il numero di processsi.
	numberOfProcesses = countProcesses(buffer,debugMode);
	// Gestione di errori in countProcesses...
	if(numberOfProcesses == EOF){
		fprintf(stderr,"Gestione incorretta del buffer in metodo countProcesses.\n"
				"Il programma verra' chiuso.");
		mode = EOF;
		numberOfProcesses = 0;
	}
	// Gestione overflow...
	else if(numberOfProcesses < EOF){
		fprintf(stderr,"Overflow rilevato (%d). Il programma verra' chiuso.\n",numberOfProcesses);
		mode = EOF;
		numberOfProcesses = 0;
	}
	// Gestione del caso in cui ci siano 0 processi...
	else if(!numberOfProcesses){
		fprintf(stderr,"Nessun processo disponibile. Controllare il file %s .\n",FILE_NAME);
		mode = EOF;
	}
	// Se non ci sono problemi, inizia la fase di preProcess.
	else if(preProcess(buffer,debugMode) == EOF){
		fprintf(stderr,"ERRORE. Sono stati rilevati piu' di %1$d token separatori in una sola riga di testo.\n"
			"Accertarsi che i nomi dei processi non contengano i caratteri \',\' , \';\' , \'.\' o \':\' .\n"
			"Tali caratteri sono usati come separatori.\n"
			"I token separatori devono essere al massimo %1$d per riga (%2$d elementi per riga).\n"
			"Il programma verra' chiuso.\n",MAX_TOKENS,MAX_TOKENS+1);
		mode = EOF;
	}
	// Lista dei processi.
	char* processes[numberOfProcesses];
	// Lista degli arrivi.
	unsigned int arrivals[numberOfProcesses];
	// Lista delle durate.
	unsigned int durations[numberOfProcesses];
	// Ready List, che conterra' gli indici dei processi.
	unsigned int readyList[numberOfProcesses];
	// Lista degli indici di processi che non sono ancora arrivati in Ready List.
	unsigned int unReadyList[numberOfProcesses];
	// Salvo i puntatori nella struct.
	structure.length = numberOfProcesses;
	structure.processes = processes;
	structure.arrivals = arrivals;
	structure.durations = durations;
	structure.readyList = readyList;
	structure.unReadyList = unReadyList;

	if(mode != EOF)
		dynamicAllocations = importProcesses(buffer, structure, debugMode);
	// Continua ad eseguire, fino a quando viene inserito 0.
	while(mode>0 && dynamicAllocations==numberOfProcesses){
		// Selezione della modalita'.
		mode = selectMode(debugMode);
		// Reimposto la Ready List e la Unready List
		// (e, quindi, anche le loro lunghezze).
		restoreQueues(structure, debugMode);
		switch(mode){
		case FCFS_MODE:{
			// FCFS (First Come, First Served)
			printf("Algoritmo scelto: FCFS\n");
			if(debugMode)
				printf("EXPECTED PARAMETERS:\nprocesses = %p\narrivals = %p\ndurations = %p\nreadyList = %p\n",processes, arrivals, durations, readyList);
			emulateFCFS(structure, debugMode);
			break;
		}
		case RR_MODE:{
			// RR (Round Robin)
			printf("Algoritmo scelto: RR\n");
			emulateRR(structure, debugMode);
			notAvailable(mode);
			break;
		}
		case PS_MODE:{
			// PS (Priority Scheduling)
			printf("Algoritmo scelto: PS\n");
			emulatePS(structure, debugMode);
			notAvailable(mode);
			break;
		}
		case SPN_MODE:{
			// SPN (Shortest Process Next)
			printf("Algoritmo scelto: SPN\n");
			emulateSPN(structure, debugMode);
			notAvailable(mode);
			break;
		}
		case SRT_MODE:{
			// SRT (Shortest Remaining Time)
			printf("Algoritmo scelto: SRT\n");
			emulateSRT(structure, debugMode);
			notAvailable(mode);
			break;
		}
		default:{
			// Se la modalita' scelta non e' valida, significa che il selettore
			// della modalita' non e' gestito bene, o c'e' stata una violazione del programma.
			// quindi si assume un valore invalido, segnalando a stderr.
			// Se mode e' 0, allora questo passaggio viene ignorato.
			if(mode && mode != EOF)
				mode = DEFAULT_MODE;
			break;
		}
		}
	}
	// Libero la memoria allocata.
	free(buffer);
	// Chiudo il file.
	fclose(file);
	// Libero la memoria allocata dinamicamente nell'array di processi.
	freeArray(structure, dynamicAllocations, debugMode);

	printf("Chiusura del programma in corso...\n");

	// Controllo che il file non abbia subito errori.
	if(mode)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
