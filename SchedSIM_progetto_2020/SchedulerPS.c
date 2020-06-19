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
		if (*(processes.lenURL)) {
			arrivalsCount = checkArrivals(time, processes);
		}
		if (*(processes.lenRL)) {
			if (currentProcessID != processes.length) {
				// Se l'ID Processo corrente e' stato acquisito, allora in questo momento e' terminato.
				if (!timeRemaining) {
					printf("Esecuzione processo \" %s \" terminata.\n",
							processes.processes[currentProcessID]);
					currentProcessID = dequeue(processes, readyList);
				}
				// Se dei processi sono appena arrivati in Ready List, e c'erano gia' dei processi
				// che aspettavano in RL, allora si mette il processo in coda RL, che cede
				// l'esecuzione al prossimo processo in RL.
				else if (arrivalsCount && arrivalsCount < *(processes.lenRL)) {
					printf(
							"Il processo \" %s \" si mette in coda di Ready List.\n",
							processes.processes[currentProcessID]);
					enqueue(currentProcessID, processes);
					currentProcessID = dequeue(processes, readyList);
				}
			}
			// Caso in cui currentProcessID e timeRemaining siano ancora di default.
			else {
				currentProcessID = dequeue(processes, readyList);
			}
			timeRemaining = processes.leftovers[currentProcessID];
		}
		printf("[T=%u]\nESECUZIONE: %s [ID = %u]\n", time,
				processes.processes[currentProcessID], currentProcessID);
		printf("Tempo rimasto: %u\n", timeRemaining);
		if (arrivalsCount) {
			printf("Ready List:\n");
			printArray(processes, readyList);
			if (dm) {
				printf("DEBUG unReady List:\n");
				printArray(processes, unReadyList);
			}
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
