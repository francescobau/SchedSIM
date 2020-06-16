/*
 * SchedulerFIFO.h
 *
 *  Created on: 7 giu 2020
 *      Author: francesco
 */

#ifndef SCHEDULERFCFS_H_
#define SCHEDULERFCFS_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

//TODO: Specifiche.
void emulateFCFS(struct processesData processes, unsigned short int debugMode);


#endif /* SCHEDULERFCFS_H_ */
