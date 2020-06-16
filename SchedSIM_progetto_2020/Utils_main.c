/*
 * Utils_main.c
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */

#include "Utils_main.h"
/**
 * Metodo per selezionare la modalita'.
 *
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @return la nuova modalita' da utilizzare nel programma, -1 in caso di valore invalido.
 */
unsigned short int selectMode(unsigned short int debugMode){
	unsigned short int newMode = 0;
	short int flag = 0;
	printf("Selezionare la modalita' dello scheduler:\n"
			"1) [DEFAULT] FCFS (First Come, First Served)\n"
			"2) RR (Round Robin)\n"
			"3) PS (Priority Scheduling)\n"
			"4) SPN (Shortest Process Next)\n"
			"5) SRT (Shortest Remaining Time)\n\n"
			"0) CHIUDI IL PROGRAMMA.\n");
	// Pulizia dello stdin...
	fflush(stdin);
	flag = scanf("%hud",&newMode);
	// Pulizia dello stdin...
	fflush(stdin);
	if(debugMode)
		printf("newMode[char]: %c \nnewMode[value]: %d\n",newMode,newMode);
	if(flag==EOF){
		fprintf(stderr,"ATTENZIONE. Errore in scanf.\nnewMode = ( %d ).\n",newMode);
	}
	// Controllo validita' della scelta...
	if(newMode < 0 || newMode > MODE_LENGTH){
		fprintf(stderr,"ATTENZIONE. La modalita' scelta ( %d ) non e' valida. Chiudo il programma.\n",newMode);
		return INVALID_MODE;
	}
	return newMode;
}

/**
 * Metodo che scansiona rapidamente il file, contando quanti processi ci sono.
 * Si considerano i processi separati da un carattere di newline (\n).
 *
 * @param buffer Il buffer da scansionare.
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @return il numero di processi
 */
int countProcesses(char* buffer, unsigned short int debugMode){
	int numberOfProcesses = 0;
	printf("DEBUG SSCANF: buffer = %c\n",*buffer);
	for(int i=0;*(buffer+i)!='\0' && i<=DEFAULT_SIZE;++i){
		printf("DEBUG *(buffer+%d) = %c\n",i,*(buffer+i));
		// I caratteri di newline consecutivi non contano.
		// Deve essere contato solo 1.
		// Inoltre, i deve essere > 0, o si ha comportamento indefinito.
		if(*(buffer+i) == '\n' && i && *(buffer+i-1) != '\n')
			++numberOfProcesses;
		if(i>=DEFAULT_SIZE)
			return EOF;
	}
	printf("DEBUG COUNTER = %d\n",numberOfProcesses);
	return numberOfProcesses;
}

//TODO: Specifiche
int preProcess(char* buffer, unsigned int debugMode){
	// Contatore di token separatori per ogni riga.
	unsigned int tokenCounter = 0;
	for(int i=0; i<=DEFAULT_SIZE && *(buffer+i)!='\0';++i){
		char temp = *(buffer+i);
		if(temp == '\n')
			tokenCounter = 0;
		else if(temp == ',' || temp == ';' || temp == ':' || temp == '.'){
			*(buffer+i) = ' ';
			++tokenCounter;
			printf("DEBUG tokenCounter : %u\n",tokenCounter);
			if(tokenCounter > 2){
				return EOF;
			}
		}
	}
	return 0;
}
/**
 * Metodo per importare tutti i processi.
 *
 * @param buffer Il buffer da scansionare.
 * @param length La lunghezza degli array (numero di processi considerato).
 * @param processes L'array contenente i puntatori ai vari nomi dei processi.
 * @param arrivals L'array contenente i tempi di arrivo.
 * @param durations L'array contentente le durate dei processi.
 * @param readyList L'array contenente gli indici dei processi nella coda Ready.
 * @return 0 in caso di successo, EOF in caso di errore.
 */
int importProcesses(char* buffer, unsigned int length, char* processes[length], unsigned int arrivals[length], unsigned int durations[length]){
	char* next = buffer;
	int flag = 0;
	for(int i = 0; i<length && next<buffer+DEFAULT_SIZE;++i){
		// Importazione dei nomi di processo.
		processes[i] = (char*) calloc(DEFAULT_SIZE+1,1);
		flag = sscanf(next,"%s %u %u\n",processes[i],&arrivals[i],&durations[i]);
		if(flag != 3){
			fprintf(stderr,"Rilevati %d token. Si aspetta che siano solo 3.\n");
			return EOF;
		}
		printf("DEBUG processes[%d] = %s\n",i,processes[i]);
		printf("DEBUG arrivals[%d] = %u\n",i,arrivals[i]);
		printf("DEBUG durations[%d] = %u\n",i,durations[i]);
		next = strchr(next,'\n');
		if(next == NULL){
			fprintf(stderr,"ERRORE IN FASE DI IMPORTAZIONE.\n");
			return EOF;
		}
		++next;
	}
	return 0;
}

/**
 * TODO: Specifiche.
 */
void freeArray(unsigned int length, char* processes[length], unsigned short int debugMode){
	for(int i=0; i<length; ++i){
		free(processes[i]);
	}
}
