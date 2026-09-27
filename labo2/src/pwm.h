/*
******************************************************************************
 *
 *  Created on: 23 sept. 2026
 *      Author: &&&
 *      File:   PWM.h
 *
 *      Ce fichier contient principalement les prototypes des fonctions
 *      demandées dans le module PWM.
 *

 *      .
 ******************************************************************************
*/


#ifndef PWM_H_
#define PWM_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "stm32f4xx.h"

// Prototype de la fonction pour l'initialisation du timer PWM;
void PWM_Init();

// Prototype de la fonction  permettant d’ajuster le ratio (Duty Cycle).
// Elle prendra un entier en paramètre exprimant donc le pourcentage du duty cycle.
void PWM_ajustDutyCycle(uint8_t valeur_duty_cycle);

// Prototype de la fonction  permettant d’ajuster la fréquence.
// Elle prendra un entier en paramètre exprimant la valeur de la fréquence voulue.
void PWM_ajustFrequence(uint8_t frequence);


#endif /* PWM_H_ */
