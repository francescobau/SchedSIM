/*
 * SchedulerPS.h
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
 */

#ifndef SCHEDULERPS_H_
#define SCHEDULERPS_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

// Esecuzione dell'algoritmo PS.
void emulatePS(struct processesData processes, unsigned short int debugMode);

#endif /* SCHEDULERPS_H_ */
