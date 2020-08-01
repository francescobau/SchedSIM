/*
 * SchedulerPS.c
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
 */
#include "SchedulerPS.h"
/**
 * Esecuzione dell'algoritmo PS.
 *
 * @param processes 	Le proprieta' dei vari processi.
 *
 * TODO: Ottimizzare codice.
 */
void emulatePS(struct processesData processes) {
	sortPerArrival(processes);
	unsigned short int dm = processes.debugMode;
	unsigned int timeRemaining = 0;
	unsigned int currentProcessID = processes.length;
	unsigned int arrivalsCount = 0;
	unsigned int time = 0;
	restoreDefaultPriorities(processes);
	if (dm)
		printf("RECEIVED PARAMETERS:\nprocesses = %p\narrivals = %p\n"
				"durations = %p\nreadyList = %p\nunreadyList = %p\n",
				(processes.processes), (processes.arrivals),
				(processes.durations), (processes.readyList),
				(processes.unReadyList));
	// Newline aggiuntivo per risaltare l'output.
	printf("\n");
	for (time = 0;
			*(processes.lenRL) > 0 || *(processes.lenURL) > 0
					|| timeRemaining > 0; ++time) {
		arrivalsCount = 0;
		// Applico la tecnica di aging ai processi che hanno aspettato in RL all'istante precedente.
		// Non viene applicata a chi sta per essere messo in RL.
		increasePriorities(processes);
		if (*(processes.lenURL)) {
			arrivalsCount = checkArrivals(time, processes);
		}
		if (*(processes.lenRL)) {
			// Se l'ID Processo corrente e' stato acquisito, allora in questo momento e' terminato.
			if (currentProcessID != processes.length) {
				if (!timeRemaining)
					printf("Esecuzione processo \" %s \" terminata.\n",
							processes.processes[currentProcessID]);
				else if (arrivalsCount
						&& hasLowerPriority(currentProcessID, processes)) {
					printf(
							"Il processo \" %s \" si mette in coda di Ready List.\n",
							processes.processes[currentProcessID]);
					enqueue(currentProcessID, processes);
					currentProcessID = dequeue(processes, readyList);
				}
			}
			// timeRemaining e' 0 di default, ma questa operazione va fatta in ogni caso, quando timeRemaining e' 0.
			if (!timeRemaining)
				currentProcessID = dequeue(processes, readyList);
			// Sincronizzo timeRemaining.
			timeRemaining = processes.leftovers[currentProcessID];
		}
		printf("[T=%u]\nESECUZIONE: %s [ID = %u] [P = %u]\n", time,
				processes.processes[currentProcessID], currentProcessID,
				processes.priorities[currentProcessID]);
		printf("Tempo rimasto: %u\n", timeRemaining);
		printf("Ready List:\n");
		printArray(processes, readyList);
		if (dm) {
			printf("DEBUG unReady List:\n");
			printArray(processes, unReadyList);
		}
		if (timeRemaining)
			--(processes.leftovers[currentProcessID]);
		// Sincronizzo il tempo rimasto.
		timeRemaining = processes.leftovers[currentProcessID];
		// Newline aggiuntivo per risaltare l'output.
		printf("\n");
	}
	printf(
			"[T=%u]\nEsecuzione processo \" %s \" terminata.\nTUTTI I PROCESSI SONO TERMINATI.\n\n",
			time, processes.processes[currentProcessID]);
}
/**
 * Funzione per ripristinare le priorita' ai valori di default.
 *
 * @param processes 	Le proprieta' dei vari processi.
 */
void restoreDefaultPriorities(struct processesData processes) {
	for (unsigned int i = 0; i < processes.length; ++i) {
		processes.priorities[i] = 0;
	}
}

/**
 * Funzione che verifica se il processo in esecuzione ha minore priorita' del primo processo in Ready List.
 *
 * @param currentIndex l'indice del processo in esecuzione.
 * @param processes 	Le proprieta' dei vari processi.
 * @return 1 se il primo processo in Ready List ha priorita' maggiore di quello in esecuzione, 0 altrimenti.
 *
 */
int hasLowerPriority(unsigned int currentIndex, struct processesData processes) {
	unsigned int dm = processes.debugMode;
	if (dm)
		printf("DEBUG VALORE DI RETURN: %d\n",
				processes.priorities[currentIndex]
						< processes.priorities[processes.readyList[0]]);
	return processes.priorities[currentIndex]
			< processes.priorities[processes.readyList[0]];
}
/**
 * Funzione che applica la tecnica di aging ai processi che hanno atteso in Ready List.
 *
 * @param processes 	Le proprieta' dei vari processi.
 */
void increasePriorities(struct processesData processes) {
	unsigned int dm = processes.debugMode;
	for (unsigned int i = 0; i < *(processes.lenRL); ++i) {
		++(processes.priorities[processes.readyList[i]]);
		if (dm)
			printf("DEBUG increased priority: [ID=%u] [P=%u]\n",
					processes.readyList[i],
					processes.priorities[processes.readyList[i]]);
	}
}
