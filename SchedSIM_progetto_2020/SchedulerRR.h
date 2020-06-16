/*
 * SchedulerRR.h
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */

#ifndef SCHEDULERRR_H_
#define SCHEDULERRR_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

//TODO: Specifiche.
void emulateRR(unsigned int length, char* processes[length], unsigned int* arrivals, unsigned int* durations, unsigned int* readyList);

#endif /* SCHEDULERRR_H_ */
