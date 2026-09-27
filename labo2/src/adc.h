/*
******************************************************************************
 *
 *  Created on: 23 sept. 2026
 *      Author: &&&
 *      File:   ADC.h
 *
 *      Ce fichier contient principalement les prototypes des fonctions
 *      demandées dans le module ADC.
 *

 *      .
 ******************************************************************************
*/


#ifndef ADC_H_
#define ADC_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "stm32f4xx.h"


// Prototype de la fonction pour l'initialisation de l'ADC servant à récueillir les données d'un potentiomètre;
void ADC_Init();

// Prototype de la fonction permettant la conversion des valeurs faite par l'ADC;
void ADC_start_conversion();

// Prototype de la fonction qui retournera la valeur convertie par l’ADC
uint16_t ADC_GetSample();

// Prototype de la fonction d'interruption générée par l’ADC lorsque une conversion est prête
void ADC_IRQHandler(); // doit porter le même nom que la fonction associée dans la table des vecteurs d’interruption.
               // Ce nom se situe à la ligne 173 du fichier startup_stm32429x.s



#endif /* ADC_H_ */
