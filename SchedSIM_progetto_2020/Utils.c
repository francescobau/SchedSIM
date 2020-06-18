/*
 * Utils.c
 *
 *  Created on: 16 giu 2020
 *      Author: francesco
 */

#include "Utils.h"


//TODO: SPECIFICHE.
unsigned int checkArrivals(unsigned int time, struct processesData processes, unsigned int debugMode){
	unsigned int count = 0;
	for(unsigned int i=0;i<processes.lenURL;i++){
		if(processes.arrivals[processes.unReadyList[0]]<=time){
//			if(!count)
			enqueue(dequeue(processes, unReadyList, debugMode),processes,debugMode);
			++count;
//			else
//				putOnHead(i, processes, debugMode);
		}
	}
	return count;
}
//TODO: SPECIFICHE.
void restoreQueues(struct processesData processes, unsigned int debugMode){
	processes.lenRL = 0;
	processes.lenURL = processes.length;
	for(unsigned int i=0;i<processes.length;++i){
		processes.unReadyList[i] = i;
		processes.readyList[i] = 0;
	}
}

/**
 * Funzione che rimuove un processo da RL o da uRL, dato un certo indice.
 * @param index L'indice di RL o uRL considerato.
 * @param processes Le proprieta' dei vari processi.
 * @param lt specifica se si vuole considerare Ready List o unReady List.
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @return EOF in caso di errore, altrimenti restituisce l'indice del processo rimosso
 */
int removeProcessAt(unsigned int index, struct processesData processes, enum listType lt, unsigned int debugMode){
	int temp = EOF;
	unsigned int length = 0;
	unsigned int* pointer;
	if(!processes.length){
		fprintf(stderr,"ERRORE. Non ci sono processi disponibili.\n");
		return EOF;
	}
	if(index >= processes.length){
		nonValidIndexError(index);
		return EOF;
	}
	if(lt==readyList){
		if(!processes.lenRL){
			fprintf(stderr,"ERRORE. La Ready List e' vuota.\n");
			return EOF;
		}
		if(index>=processes.lenRL){
			fprintf(stderr,"ERRORE. L'indice %u non e' disponibile in Ready List.\n",index);
			return EOF;
		}
		if(debugMode)
			printf("DEBUG Rimozione processo da Ready List.\n");
		pointer = processes.readyList;
		length = processes.lenRL;
		--processes.lenRL;
	}
	else if(lt==unReadyList){
		if(!processes.lenURL){
			fprintf(stderr,"ERRORE. La unReady List e' vuota.\n");
			return EOF;
		}
		if(index>=processes.lenURL){
			fprintf(stderr,"ERRORE. L'indice %u non e' disponibile in unReady List.\n",index);
			return EOF;
		}
		if(debugMode)
			printf("DEBUG Rimozione processo da UnReady List.\n");
		pointer = processes.unReadyList;
		length = processes.lenURL;
		--processes.lenURL;
	}
	else{
		fprintf(stderr,"ERRORE SCONOSCIUTO in fase di rimozione.\n");
		return EOF;
	}
	temp = pointer[index];
	for(unsigned int i=index; i<length; ++i){
		pointer[i] = pointer[i+1];
	}
	if(debugMode)
		printf("DEBUG Processo n. %u rimosso.\n"
				"Nome Processo eliminato: %s\n",temp,processes.processes[temp]);
	return temp;
}

// Funzione che inserisce l'indice dato di un processo in RL.
// TODO: SPECIFICHE.
int addProcessAt(unsigned int processIndex, unsigned int targetIndex, struct processesData processes, unsigned int debugMode){
	if(processIndex >= processes.length){
		nonValidIndexError(processIndex);
		return EOF;
	}
	if(targetIndex > processes.lenRL){
		nonValidIndexError(targetIndex);
		return EOF;
	}
	processes.readyList[targetIndex] = processIndex;
	return 0;
}

// Funzione che mette un processo in coda a RL.
// TODO: SPECIFICHE.
int enqueue(unsigned int processIndex, struct processesData processes, unsigned int debugMode){
	return addProcessAt(processIndex, processes.lenURL, processes, debugMode);
}
// Funzione che rimuove il primo processo in RL o uRL.
// TODO: SPECIFICHE.
int dequeue(struct processesData processes, enum listType lt, unsigned int debugMode){
	return removeProcessAt(0, processes, lt, debugMode);
}
/**
 * Funzione che sposta in testa un processo da uRL.
 *
 * @param index L'indice di uRL considerato.
 * @param processes Le proprieta' dei vari processi.
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @return EOF in caso di indice errato, altrimenti viene restituito 0.
 * TODO: Restituire il nuovo indice, anziche' 0. Da gestire i casi degeneri.
 */
int putOnHead(unsigned int index, struct processesData processes, unsigned int debugMode){
	unsigned int i;
	if(index>=processes.lenURL || index>=processes.length){
		nonValidIndexError(index);
		return EOF;
	}
	// Controllo anche che non vada in Overflow.
	for(i=index-1; i>=0 && i<processes.length &&
	(processes.arrivals[processes.unReadyList[i]]
			> processes.arrivals[processes.unReadyList[i+1]]);--i){
		unsigned int temp = processes.unReadyList[i];
		processes.unReadyList[i] = processes.unReadyList[i+1];
		processes.unReadyList[i+1] = temp;
		if(debugMode)
			printf("DEBUG i = %u\n",i);
	}
	if(debugMode)
		printf("DEBUG i finale = %u\n",i);
	return 0;
}
/**
 * Funzione che stampa in stderr la non validita' dell'indice scelto.
 * @param index L'indice non valido.
 */
void nonValidIndexError(unsigned int index){
	fprintf(stderr,"ERRORE. L'indice %u non e' disponibile.\n",index);
}
/**
 * Funzione che riordina la unReady list. Viene usato un Bubble Sort ottimizzato.
 *
 * @param processes Le proprieta' dei vari processi.
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * TODO: Implementare algoritmo migliore (si usera' Insertion Sort dall'inizio, quindi questa funzione non ci sara' piu'.
 */
void sortPerArrival(struct processesData processes, unsigned int debugMode){
	unsigned int value;
	unsigned int nextValue;
	unsigned int swaps = 0;
	for(int i=processes.lenURL; i>0 && (swaps || (i!=processes.lenURL)); --i){
		swaps = 0;
		for(int j=0;j<i; ++j){
			value = processes.unReadyList[j];
			nextValue = processes.unReadyList[j];
			if(nextValue<value){
				processes.unReadyList[j] = nextValue;
				processes.unReadyList[j+1] = value;
				++swaps;
			}
		}
	}
	if(debugMode){
		printf("DEBUG unReady List ordinata:\n");
		printArray(processes, unReadyList, debugMode);
	}
}
/**
 * Funzione per stampare il contenuto di RL o di uRL.
 *
 * @param processes Le proprieta' dei vari processi.
 * @param lt specifica se si vuole considerare Ready List o unReady List.
 * @param debugMode 0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 * @return EOF in caso di errore, 0 se viene eseguito correttamente.
 * TODO: Estendere printArray anche per altre liste.
 */
int printArray(struct processesData processes, enum listType lt, unsigned int debugMode){
	unsigned int length;
	unsigned int* pointer;
	if(lt==readyList){
		length = processes.lenRL;
		pointer = processes.readyList;
	}
	else if(lt==unReadyList){
		length = processes.lenURL;
		pointer = processes.unReadyList;
	}
	else{
		fprintf(stderr,"ERRORE. enum non valido.\n");
		return EOF;
	}
	for(unsigned int i=0; i<length; ++i){
		printf("array[%u] = %u\n",i,pointer[i]);
	}
	return 0;
}
