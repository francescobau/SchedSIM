/*
 * SchedulerRR.h
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
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
