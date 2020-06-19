/*
 * Utils.c
 *
 *      @author		Francesco Bau' 1136850
 *  	@since		16 giu 2020
 */

#include "Utils.h"

/**
 * Funzione per controllare quali processi entrano in coda a RL ad un certo istante time.
 * Si considera uRL gia' ordinato.
 *
 * @param time			L'istante di tempo preso in considerazione.
 * @param processes 	Le proprieta' dei vari processi.
 * @return 				il numero di processi che entrano in coda RL.
 *
 * TODO: Gestione avanzata per algoritmi piu' avanzati.
 */
unsigned int checkArrivals(unsigned int time, struct processesData processes) {
	unsigned int count = 0;
	for (unsigned int i = 0; i < *(processes.lenURL); i++) {
		if (processes.arrivals[processes.unReadyList[0]] <= time) {
			// Si mette in coda RL cio' il primo elemento di uRL.
			enqueue(dequeue(processes, unReadyList), processes);
			++count;
		}
	}
	return count;
}
/**
 * Funzione che ripristina RL e uRL allo stato iniziale.
 *
 * @param processes 	Le proprieta' dei vari processi.
 */
void restoreLists(struct processesData processes) {
	*(processes.lenRL) = 0;
	*(processes.lenURL) = processes.length;
	for (unsigned int i = 0; i < processes.length; ++i) {
		processes.unReadyList[i] = i;
		processes.readyList[i] = 0;
		processes.leftovers[i] = processes.durations[i];
	}
}

/**
 * Funzione che rimuove un processo da RL o da uRL, dato un certo indice.
 * @param index 		L'indice di RL o uRL considerato.
 * @param processes 	Le proprieta' dei vari processi.
 * @param lt			Specifica se si vuole considerare Ready List o unReady List.
 * @return				EOF in caso di errore, altrimenti restituisce l'indice del processo rimosso.
 */
int removeProcessAt(unsigned int index, struct processesData processes,
		enum listType lt) {
	unsigned short int dm = processes.debugMode;
	int temp = EOF;
	unsigned int length = 0;
	unsigned int *pointer;
	if (!processes.length) {
		fprintf(stderr, "ERRORE. Non ci sono processi disponibili.\n");
		return EOF;
	}
	if (index >= processes.length) {
		nonValidIndexError(index);
		return EOF;
	}
	if (lt == readyList) {
		if (!*(processes.lenRL)) {
			fprintf(stderr, "ERRORE. La Ready List e' vuota.\n");
			return EOF;
		}
		if (index >= *(processes.lenRL)) {
			fprintf(stderr,
					"ERRORE. L'indice %u non e' disponibile in Ready List.\n",
					index);
			return EOF;
		}
		if (dm)
			printf("DEBUG Rimozione processo da Ready List.\n");
		pointer = processes.readyList;
		length = *(processes.lenRL);
		--*(processes.lenRL);
	} else if (lt == unReadyList) {
		if (!*(processes.lenURL)) {
			fprintf(stderr, "ERRORE. La unReady List e' vuota.\n");
			return EOF;
		}
		if (index >= *(processes.lenURL)) {
			fprintf(stderr,
					"ERRORE. L'indice %u non e' disponibile in unReady List.\n",
					index);
			return EOF;
		}
		if (dm)
			printf("DEBUG Rimozione processo da UnReady List.\n");
		pointer = processes.unReadyList;
		length = *(processes.lenURL);
		--*(processes.lenURL);
	} else {
		fprintf(stderr, "ERRORE SCONOSCIUTO in fase di rimozione.\n");
		return EOF;
	}
	temp = pointer[index];
	for (unsigned int i = index; i < length; ++i) {
		pointer[i] = pointer[i + 1];
	}
	if (dm)
		printf("DEBUG Processo n. %u rimosso.\n"
				"Nome Processo eliminato: %s\n", temp,
				processes.processes[temp]);
	return temp;
}
/**
 * Funzione che inserisce l'indice dato di un processo in RL.
 *
 * @param processIndex	L'indice del processo considerato, da inserire in Ready List.
 * @param targetIndex	L'indice della Ready List in cui processIndex sara' inserito.
 * @param processes 	Le proprieta' dei vari processi.
 * @return				EOF in caso di errore, 0 altrimenti.
 */
int addProcessAt(unsigned int processIndex, unsigned int targetIndex,
		struct processesData processes) {
	if (processIndex >= processes.length) {
		nonValidIndexError(processIndex);
		return EOF;
	}
	if (targetIndex > *(processes.lenRL)) {
		nonValidIndexError(targetIndex);
		return EOF;
	}
	processes.readyList[targetIndex] = processIndex;
	++*(processes.lenRL);
	return 0;
}

/**
 * Funzione che mette un processo in coda a RL.
 *
 * @param processIndex	L'indice del processo considerato, da inserire in coda di Ready List.
 * @param processes 	Le proprieta' dei vari processi.
 * @return				EOF in caso di errore, 0 altrimenti.
 */
int enqueue(unsigned int processIndex, struct processesData processes) {
	return addProcessAt(processIndex, *(processes.lenRL), processes);
}
/**
 * Funzione che rimuove il primo processo in RL o uRL.
 *
 * @param processes 	Le proprieta' dei vari processi.
 * @param lt			Specifica se si vuole considerare Ready List o unReady List.
 */
int dequeue(struct processesData processes, enum listType lt) {
	return removeProcessAt(0, processes, lt);
}
/**
 * Funzione che sposta in testa un processo da uRL.
 *
 * @param index		L'indice di uRL considerato.
 * @param processes Le proprieta' dei vari processi.
 * @return 			EOF in caso di indice errato, altrimenti viene restituito 0.
 *
 * TODO: Restituire il nuovo indice, anziche' 0. Da gestire i casi degeneri.
 */
int putOnHead(unsigned int index, struct processesData processes) {
	unsigned short int dm = processes.debugMode;
	unsigned int i;
	if (index >= *(processes.lenURL) || index >= processes.length) {
		nonValidIndexError(index);
		return EOF;
	}
	// Controllo anche che non vada in Overflow.
	for (i = index - 1;
			i >= 0 && i < processes.length
					&& (processes.arrivals[processes.unReadyList[i]]
							> processes.arrivals[processes.unReadyList[i + 1]]);
			--i) {
		unsigned int temp = processes.unReadyList[i];
		processes.unReadyList[i] = processes.unReadyList[i + 1];
		processes.unReadyList[i + 1] = temp;
		if (dm)
			printf("DEBUG i = %u\n", i);
	}
	if (dm)
		printf("DEBUG i finale = %u\n", i);
	return 0;
}
/**
 * Funzione che stampa in stderr la non validita' dell'indice scelto.
 * @param index L'indice non valido.
 */
void nonValidIndexError(unsigned int index) {
	fprintf(stderr, "ERRORE. L'indice %u non e' disponibile.\n", index);
}
/**
 * Funzione che riordina la unReady list. Viene usato un Bubble Sort ottimizzato.
 *
 * @param processes		Le proprieta' dei vari processi.
 *
 * TODO: 	Implementare algoritmo migliore (si usera' Insertion Sort dall'inizio,
 * 			quindi questa funzione non ci sara' piu'.
 */
void sortPerArrival(struct processesData processes) {
	unsigned short int dm = processes.debugMode;
	unsigned int value;
	unsigned int nextValue;
	unsigned int swaps = 0;
	unsigned int temp = 0;
	for (unsigned int i = *(processes.lenURL);
			i > 0 && (swaps || (i == *(processes.lenURL))); --i) {
		swaps = 0;
		for (unsigned int j = 0; j < i - sizeof(char); ++j) {
			value = processes.arrivals[processes.unReadyList[j]];
			nextValue = processes.arrivals[processes.unReadyList[j + 1]];
			if (nextValue < value) {
				temp = processes.unReadyList[j];
				processes.unReadyList[j] = processes.unReadyList[j + 1];
				processes.unReadyList[j + 1] = temp;
				++swaps;
			}
		}
	}
	if (dm) {
		printf("DEBUG unReady List ordinata:\n");
		printArray(processes, unReadyList);
	}
}
/**
 * Funzione per stampare il contenuto di RL o di uRL.
 *
 * @param processes		Le proprieta' dei vari processi.
 * @param lt 			Specifica se si vuole considerare Ready List o unReady List.
 * @return 				EOF in caso di errore, 0 se viene eseguito correttamente.
 *
 * TODO: Estendere printArray anche per altre liste.
 * TODO: Migliorare il return, se necessario.
 */
int printArray(struct processesData processes, enum listType lt) {
	unsigned int length;
	unsigned int *pointer;
	if (lt == readyList) {
		length = *(processes.lenRL);
		pointer = processes.readyList;
	} else if (lt == unReadyList) {
		length = *(processes.lenURL);
		pointer = processes.unReadyList;
	} else {
		fprintf(stderr, "ERRORE. enum non valido.\n");
		return EOF;
	}
	for (unsigned int i = 0; i < length; ++i) {
		printf("[%u] -> %s [ID = %u] [TL = %u]\n", i,
				processes.processes[pointer[i]], pointer[i],
				processes.leftovers[pointer[i]]);
	}
	if (!length)
		printf("[Empty]\n");
	return 0;
}
