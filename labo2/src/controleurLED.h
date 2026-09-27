/*
******************************************************************************
 *
 *  Created on: 23 sept. 2026
 *      Author: &&&
 *      File:   ControleurLED.h
 *
 *      Ce fichier contient principalement les prototypes des fonctions
 *      demandées dans le module ControleurLED.
 *
 *      .
 ******************************************************************************
*/

#ifndef CONTROLEURLED_H_
#define CONTROLEURLED_H_

/* Includes ------------------------------------------------------------------*/

#include <adc.h>
#include <pwm.h>
#include <stdint.h>

// Prototype de la fonction pour l'initialisation du module ControleurLED;
void ControleurLED_Init();

// Prototype des fonctions servant à allumer et éteindre la LED.
void ControleurLED_LEDon();

void ControleurLED_LEDoff();

// Prototype de la fonction permettant l'ajustement de  l’intensité lumineuse en fonction de la valeur de l’ADC.
void ControleurLED_ajustLightLED();

#endif /* CONTROLEURLED_H_ */

