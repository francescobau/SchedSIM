/*
 * SchedulerSRT.h
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */

#ifndef SCHEDULERSRT_H_
#define SCHEDULERSRT_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

//TODO: Specifiche.
void emulateSRT(unsigned int length, char* processes[length], unsigned int* arrivals, unsigned int* durations, unsigned int* readyList);

#endif /* SCHEDULERSRT_H_ */
