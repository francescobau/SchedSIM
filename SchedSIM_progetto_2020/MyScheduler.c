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
	unsigned short int debugMode = 0;

	// Buffer per la lettura dei dati in input.
	// Nella calloc si aggiunge un byte per il carattere \0 nel buffer.
	char* buffer = (char*) calloc(DEFAULT_SIZE+1,1);

	// Memorizzo il file nel buffer.
	fread(buffer,sizeof(char),DEFAULT_SIZE+1,file);

	numberOfProcesses = countProcesses(buffer,debugMode);
	if(numberOfProcesses == EOF){
		fprintf(stderr,"Gestione incorretta del buffer in metodo countProcesses.\n"
				"Il programma verra' chiuso.");
		mode = EOF;
		numberOfProcesses = 0;
	}
	else if(numberOfProcesses < EOF){
		fprintf(stderr,"Overflow rilevato (%d). Il programma verra' chiuso.\n",numberOfProcesses);
		mode = EOF;
		numberOfProcesses = 0;
	}
	else if(!numberOfProcesses){
		fprintf(stderr,"Nessun processo disponibile. Controllare il file %s .\n",FILE_NAME);
	}

	if(preProcess(buffer,debugMode) == EOF){
		fprintf(stderr,"ERRORE. Troppi token separatori presenti in una sola riga di testo.\n"
			"Accertarsi che i nomi dei processi non contengano i caratteri \',\' , \';\' , \'.\' o \':\' .\n"
			"Tali caratteri sono usati come separatori.\n"
			"I token separatori devono essere al massimo 2 per riga (3 elementi per riga).\n"
			"Il programma verra' chiuso.");
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
	// Lista degli indici che non sono ancora arrivati in Ready List.
	unsigned int unReadyList[numberOfProcesses];
	// All'inizio, nessuno e' in Ready List.
	generateQueue(numberOfProcesses, unReadyList);
	// Salvo i puntatori nella struct.
	structure.length = numberOfProcesses;
	structure.processes = processes;
	structure.arrivals = arrivals;
	structure.durations = durations;
	structure.readyList = readyList;
	structure.unReadyList = unReadyList;
	/** DEBUG MODE (passato per argomento):
	 * 0) [DEFAULT] DISATTIVATO (Modalita' essenziale - release)
	 * != 0) ATTIVATO (Modalita' debug)
	*/
	if(argc>1)
		sscanf(argv[1],"%hu",&debugMode);
	printf("DEBUG_MODE: %d\n",debugMode);

	if(mode>0)
		importProcesses(buffer, structure, debugMode);

	// Continua ad eseguire, fino a quando non si inserisce un valore invalido o 0.
	while(mode>0){
		// Selezione della modalita'.
		// Questo programma continua ad eseguire fino a quando non si inserisce un
		// valore invalido o 0.
		mode = selectMode(debugMode);
		switch(mode){
		case FCFS_MODE:{
			// FCFS (First Come, First Served)
			if(debugMode)
				printf("EXPECTED PARAMETERS:\nprocesses = %p\narrivals = %p\ndurations = %p\nreadyList = %p\n",processes, arrivals, durations, readyList);
			emulateFCFS(structure, debugMode);
			break;
		}
		case RR_MODE:{
			// RR (Round Robin)
			emulateRR(structure, debugMode);
			break;
		}
		case PS_MODE:{
			// PS (Priority Scheduling)
			emulatePS(structure, debugMode);
			break;
		}
		case SPN_MODE:{
			// SPN (Shortest Process Next)
			emulateSPN(structure, debugMode);
			break;
		}
		case SRT_MODE:{
			// SRT (Shortest Remaining Time)
			emulateSRT(structure, debugMode);
			break;
		}
		default:{
			// Se la modalita' scelta non e' valida, significa che il selettore
			// della modalita' non e' gestito bene, o c'e' stata una violazione del programma.
			// quindi si assume un valore invalido, segnalando a stderr.
			// Se mode e' 0, allora questo passaggio viene ignorato.
			if(mode){
				fprintf(stderr,"POSSIBILE VIOLAZIONE DEL PROGRAMMA RILEVATA. La modalita' selezionata ( %d ) non e' valida. Chiudo il programma.\n",mode);
				mode = INVALID_MODE;
			}
			break;
		}
		}
	}
	// Libero la memoria allocata.
	free(buffer);
	// Libero la memoria allocata nell'array processes.
	freeArray(structure, debugMode);
	// Chiudo il file.
	fclose(file);
	// Controllo che il file non abbia subito errori.
	if(mode)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
