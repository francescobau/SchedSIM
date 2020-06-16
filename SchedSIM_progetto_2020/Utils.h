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
	char** processes;
	unsigned int* arrivals;
	unsigned int* durations;
	unsigned int* readyList;
	unsigned int** unReadyList;
};

//TODO: SPECIFICHE.
int checkArrivalsAtTime(unsigned int time, unsigned int length, unsigned int arrivals[length], unsigned int remainingIndexes, unsigned int queue[remainingIndexes]);
//TODO: SPECIFICHE.
void generateQueue(unsigned int length, unsigned int queue[length]);
#endif /* UTILS_H_ */
