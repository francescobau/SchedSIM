/*
 * SchedulerFCFS.c
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */
#include "SchedulerFCFS.h"
//TODO: Specifiche.
void emulateFCFS(struct processesData processes, unsigned short int debugMode){
	sortPerArrival(processes, debugMode);
	unsigned int timeRemaining = 0;
	unsigned int currentProcessID = processes.unReadyList;
	int arrivalsCount = 0;
	if(debugMode)
		printf("RECEIVED PARAMETERS:\nprocesses = %p\narrivals = %p\n"
			"durations = %p\nreadyList = %p\nunreadyList = %p\n",
			(processes.processes), (processes.arrivals), (processes.durations),
			(processes.readyList), (processes.unReadyList));
	for(unsigned int i=0; processes.lenRL > 0 || processes.lenURL > 0 || timeRemaining > 0; ++i){
		arrivalsCount = checkArrivals(i, processes, debugMode);
		if(!timeRemaining){
			currentProcessID = dequeue(processes, readyList, debugMode);
			timeRemaining = processes.arrivals[currentProcessID];
		}
		printf("[T=%u]\nESECUZIONE: %u\n",i,currentProcessID);
		if(debugMode)
			printf("DEBUG Tempo rimasto: %u\n",timeRemaining);
		if(arrivalsCount){
			printf("Ready List:\n");
			printArray(processes, readyList, debugMode);
			printf("unReady List:\n ");
			printArray(processes, unReadyList, debugMode);
		}
	}
}
