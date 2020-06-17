/*
 * Utils.h
 *
 *  Created on: 16 giu 2020
 *      Author: francesco
 */

#ifndef UTILS_H_
#define UTILS_H_

// Importazione condizionata di <stdio.h> .
#ifndef STDIO_H_
#include <stdio.h>
#endif /* STDIO_H_ */

// Importazione condizionata di <stdlib.h> .
#ifndef STDLIB_H_
#include <stdlib.h>
#endif /* STDLIB_H_ */

struct processesData{
	unsigned int length;
	unsigned int lenRL;
	unsigned int lenURL;
	char** processes;
	unsigned int* arrivals;
	unsigned int* durations;
	unsigned int* readyList;
	unsigned int* unReadyList;
};

// enum per specificare se si vuole effettuare l'operazione
// dalla Ready List o dalla UnReady List.
typedef enum listType {readyList,unReadyList};

//TODO: SPECIFICHE.
int checkArrivals(unsigned int time, struct processesData processes);
//TODO: SPECIFICHE.
void restoreQueues(struct processesData processes, unsigned int debugMode);
//TODO: SPECIFICHE.
int removeProcessAt(unsigned int index, struct processesData processes, enum listType lt, unsigned int debugMode);
#endif /* UTILS_H_ */
