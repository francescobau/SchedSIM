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
short int selectMode(unsigned short int debugMode){
	short int newMode = 0;
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
		return EOF;
	}
	// Controllo validita' della scelta...
	if(newMode < 0 || newMode > MODE_LENGTH){
		fprintf(stderr,"ATTENZIONE. La modalita' scelta ( %d ) non e' valida.\n",newMode);
		// In caso che l'utente dovesse inserire un EOF apposta,
		// allora newMode viene cambiato.
		if(newMode == EOF)
			newMode = EOF + EOF;
	}
	return newMode;
}

/**
 * Funzione che scansiona rapidamente il file, contando quanti processi ci sono.
 * Si considerano i processi separati da un carattere di newline (\n).
 *
 * @param buffer Il buffer da scansionare.
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @return il numero di processi
 */
int countProcesses(char* buffer, unsigned short int debugMode){
	int numberOfProcesses = 0;
	if(debugMode)
		printf("DEBUG SSCANF: buffer = %c\n",*buffer);
	for(unsigned int i=0;*(buffer+i)!='\0' && i<=DEFAULT_SIZE;++i){
		if(debugMode)
			printf("DEBUG *(buffer+%d) = %c\n",i,*(buffer+i));
		// I caratteri di newline consecutivi non contano.
		// Deve essere contato solo 1 carattere di newline.
		// Inoltre, i deve essere > 0, o si ha comportamento indefinito.
		if(*(buffer+i) == '\n' && i && *(buffer+i-1) != '\n')
			++numberOfProcesses;
		if(i>=DEFAULT_SIZE)
			return EOF;
	}
	if(debugMode)
		printf("DEBUG COUNTER = %d\n",numberOfProcesses);
	return numberOfProcesses;
}

//TODO: Specifiche
int preProcess(char* buffer, unsigned short int debugMode){
	// Contatore di caratteri separatori per ogni riga.
	unsigned int tokenCounter = 0;
	for(unsigned int i=0; i<=DEFAULT_SIZE && *(buffer+i)!='\0';++i){
		char temp = *(buffer+i);
		// Se il carattere e' di newLine, allora si azzera tokenCounter.
		if(temp == '\n')
			tokenCounter = 0;
		// Se il carattere e' un separatore...
		else if(temp == ',' || temp == ';' || temp == ':' || temp == '.'){
			// ...allora sostituisco il carattere puntato con uno spazio...
			*(buffer+i) = ' ';
			// ...e incremento tokenCounter.
			++tokenCounter;
			if(debugMode)
				printf("DEBUG tokenCounter : %u\n",tokenCounter);
			// Controllo per vedere se i caratteri separatori sono usati
			// usati in modo appropriato o no.
			if(tokenCounter >= MAX_TOKENS)
				return EOF;
		}
	}
	return 0;
}
/**
 * Metodo per importare tutti i processi.
 *
 * @param buffer Il buffer da scansionare.
 * @param processes Le proprieta' dei vari processi.
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @return Il numero di aree di memoria allocate dinamicamente per i processi.
 */
int importProcesses(char* buffer, struct processesData processes, unsigned short int debugMode){
	// Il puntatore da cui verranno estratti i dati dallo sscanf.
	char* next = buffer;
	char* temp = next;
	// Memorizza il numero di token estratti con successo da sscanf.
	int nTokens = 0;
	unsigned int counter = 0;
	for(counter = 0; counter<processes.length && next<buffer+DEFAULT_SIZE;++counter){
		// Importazione dei nomi di processo.
		processes.processes[counter] = (char*) calloc(DEFAULT_SIZE+1,1);
		nTokens = sscanf(next,"%s %u %u\n",(processes.processes[counter]),&(processes.arrivals[counter]),&(processes.durations[counter]));
		if(nTokens != MAX_TOKENS){
			fprintf(stderr,"%d token rilevato da sscanf. Si aspetta che siano %d token per ogni riga.\n",nTokens,MAX_TOKENS);
			return counter+sizeof(char);
		}
		if(debugMode){
			printf("DEBUG processes[%d] = %s\n",counter,processes.processes[counter]);
			printf("DEBUG arrivals[%d] = %u\n",counter,processes.arrivals[counter]);
			printf("DEBUG durations[%d] = %u\n",counter,processes.durations[counter]);
		}
		next = strchr(temp,'\n');
		temp = next;
		if(next == NULL){
			fprintf(stderr,"ERRORE SCONOSCIUTO IN FASE DI IMPORTAZIONE.\n");
			return counter+sizeof(char);
		}
		if(!processes.durations[counter]){
			fprintf(stderr,"ERRORE. Rilevato processo con durata nulla. Il programma verra' chiuso.\n");
			return counter+sizeof(char);
		}
		++next;
	}
	if(debugMode)
		printf("DEBUG i = %u\n",counter);
	return counter;
}

/**
 * TODO: Specifiche.
 */
void freeArray(struct processesData processes, unsigned short int amount, unsigned short int debugMode){
	for(unsigned int i=0; i<amount && i<processes.length; ++i){
		free(processes.processes[i]);
		if(debugMode)
			printf("DEBUG MEMORIA LIBERATA: %d\n",i);
	}
}
