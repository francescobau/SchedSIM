/*
 * SchedulerFIFO.h
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
 */

#ifndef SCHEDULERFCFS_H_
#define SCHEDULERFCFS_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

// Esecuzione dell'algoritmo FCFS.
void emulateFCFS(struct processesData processes, unsigned short int debugMode);

#endif /* SCHEDULERFCFS_H_ */
