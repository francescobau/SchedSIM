/*
 * SchedulerSPN.h
 *
 *      @author		Francesco Bau' 1136850
 *      @since		7 giu 2020
 */

#ifndef SCHEDULERSPN_H_
#define SCHEDULERSPN_H_

// Importazione condizionata di Utils.h .
#ifndef UTILS_H_
#include "Utils.h"
#endif /* UTILS_H_ */

// Esecuzione dell'algoritmo SPN.
void emulateSPN(struct processesData processes);

#endif /* SCHEDULERSPN_H_ */
