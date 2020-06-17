/*
 * Utils.c
 *
 *  Created on: 16 giu 2020
 *      Author: francesco
 */

#include "Utils.h"

//TODO: SPECIFICHE.
int checkArrivals(unsigned int time, struct processesData processes){
	return 0;
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
//TODO: SPECIFICHE.
int removeProcessAt(unsigned int index, struct processesData processes, enum listType lt, unsigned int debugMode){
	int temp = EOF;
	unsigned int length = 0;
	unsigned int* pointer;
	if(index>=processes.length){
		fprintf("ERRORE. L'indice cercato (%u) non e' disponibile. Riprovare con un indice valido.\n",index);
		return EOF;
	}
	if(lt==readyList){
		if(debugMode)
			printf("DEBUG Rimozione processo da Ready List.\n");
		pointer = processes.readyList;
		length = processes.lenRL;
		--processes.lenRL;
	}
	else if(lt==unReadyList){
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
