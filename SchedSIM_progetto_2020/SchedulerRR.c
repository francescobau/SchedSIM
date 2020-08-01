/*
 * SchedulerRR.c
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
 */
#include "SchedulerRR.h"
/**
 * Esecuzione dell'algoritmo RR.
 *
 * @param processes 	Le proprieta' dei vari processi.
 */
void emulateRR(struct processesData processes) {
	sortPerArrival(processes);
	unsigned short int dm = processes.debugMode;
	unsigned int timeRemaining = 0;
	unsigned int currentProcessID = processes.length;
	unsigned int arrivalsCount = 0;
	unsigned int time = 0;
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
			// Se l'ID Processo corrente e' stato acquisito, allora in questo momento e' terminato.
			if (currentProcessID != processes.length) {
				if (!timeRemaining)
					printf("Esecuzione processo \" %s \" terminata.\n",
							processes.processes[currentProcessID]);
				else {
					printf(
							"Quanto di tempo scaduto. Il processo \" %s \" si mette in coda di Ready List.\n",
							processes.processes[currentProcessID]);
					enqueue(currentProcessID, processes);
				}
			}
			currentProcessID = dequeue(processes, readyList);
			timeRemaining = processes.leftovers[currentProcessID];
			// Se non e' arrivato nessun processo da unReadyList, vuol dire che e' cambiata solo la Ready List.
			if (!arrivalsCount)
				++arrivalsCount;
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
