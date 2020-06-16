/*
 * SchedulerPS.h
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */

#ifndef SCHEDULERPS_H_
#define SCHEDULERPS_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

// TODO: Specifiche.
void emulatePS(struct processesData processes, unsigned short int debugMode);

#endif /* SCHEDULERPS_H_ */
