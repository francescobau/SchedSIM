/*
 * SchedulerSPN.h
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */

#ifndef SCHEDULERSPN_H_
#define SCHEDULERSPN_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

//TODO: Specifiche.
void emulateSPN(struct processesData processes, unsigned short int debugMode);

#endif /* SCHEDULERSPN_H_ */
