/*
 * SchedulerFCFS.c
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
 */
#include "SchedulerFCFS.h"
/**
 * Esecuzione dell'algoritmo FCFS.
 *
 * @param processes 	Le proprieta' dei vari processi.
 * @param debugMode 	0 per Modalita' Release, altrimenti viene usata modalita' di Debug.
 */
void emulateFCFS(struct processesData processes, unsigned short int debugMode) {
	sortPerArrival(processes, debugMode);
	unsigned int timeRemaining = 0;
	unsigned int currentProcessID = processes.length;
	unsigned int arrivalsCount = 0;
	unsigned int time = 0;
	if (debugMode)
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
			arrivalsCount = checkArrivals(time, processes, debugMode);
		}
		if (*(processes.lenRL) && !timeRemaining) {
			// Se l'ID Processo corrente e' stato acquisito, allora in questo momento e' terminato.
			if (currentProcessID != processes.length)
				printf("Esecuzione processo \" %s \" terminata.\n",
						processes.processes[currentProcessID]);
			currentProcessID = dequeue(processes, readyList, debugMode);
			timeRemaining = processes.leftovers[currentProcessID];
			// Se non e' arrivato nessun processo in ReadyList, vuol dire che e' solo cambiato il processo
			// in esecuzione, quindi e' cambiata la Ready List.
			if (!arrivalsCount)
				++arrivalsCount;
		}
		printf("[T=%u]\nESECUZIONE: %s [ID = %u]\n", time,
				processes.processes[currentProcessID], currentProcessID);
		printf("Tempo rimasto: %u\n", timeRemaining);
		if (arrivalsCount) {
			printf("Ready List:\n");
			printArray(processes, readyList, debugMode);
			if (debugMode) {
				printf("DEBUG unReady List:\n");
				printArray(processes, unReadyList, debugMode);
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
