/*
 * SchedulerFCFS.c
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */
#include "SchedulerFCFS.h"
//TODO: Specifiche.
void emulateFCFS(struct processesData processes, unsigned short int debugMode){
	printf("RECEIVED PARAMETERS:\nprocesses = %p\narrivals = %p\n"
			"durations = %p\nreadyList = %p\nunreadyList = %p\n",
			(processes.processes), (processes.arrivals), (processes.durations),
			(processes.readyList), (processes.unReadyList));
}
