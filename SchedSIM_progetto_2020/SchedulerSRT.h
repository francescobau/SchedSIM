/*
 * SchedulerSRT.h
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
 */

#ifndef SCHEDULERSRT_H_
#define SCHEDULERSRT_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

// Esecuzione dell'algoritmo SRT.
void emulateSRT(struct processesData processes);

#endif /* SCHEDULERSRT_H_ */
