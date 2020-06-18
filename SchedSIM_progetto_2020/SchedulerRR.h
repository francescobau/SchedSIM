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

// Esecuzione dell'algoritmo RR.
void emulateRR(struct processesData processes, unsigned short int debugMode);

#endif /* SCHEDULERRR_H_ */
