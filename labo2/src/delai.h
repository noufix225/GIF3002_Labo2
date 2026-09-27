/*
******************************************************************************
 *
 *  Created on: 16 sept. 2026
 *      Author: Antho
 *      File:   delai.h
 *
 *      Ce fichier contient principalement les prototypes des fonctions
 *      demandées dans le module delai,
 *
 *      ainsi que la définition des adresses de bases
 *      des différents périphériques liès aux I/Os que nous souhaitons utiliser.
 *      .
 ******************************************************************************
*/

#ifndef DELAI_H_
#define DELAI_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "stm32f4xx.h"// On inclut ce fichier car il contient notamment un include du fichier
// core_cm4.h contenant les structures du processeur du Cortex M4 et de tous ces périphériques de coeur
// notamment celle du Systick que nous pourrons ainsi utiliser afin de pointer plus facilement vers
// les adresses des registres du Systick nécessaires pour l'implémentation des fonctions de ce module.

// Prototype de la fonction SysTick Handler. Cette fonction étant par défaut la fonction qui appellé
// par le SysTick toutes les 1ms, elle jouera donc le rôle du prototype de la fonction/routine d'interruption du SysTick
void SysTick_Handler(void);

// Prototype de la fonction pour l'initialisation du Systick pour une base de temps de 1ms;
void SysTick_Init();

// Prototype de la fonction retournant la valeur actuelle du compteur
unsigned int Systick_current_compt_value();

// Prototype de la fonction permettant de réaliser un délai souhaité en fonction de la valeur du SysTick
void SysTick_create_delay(unsigned int delay);

#endif /* DELAI_H_ */
