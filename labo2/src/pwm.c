/*
******************************************************************************
 *
 *  Created on: 23 sept. 2026
 *      Author: &&&
 *      File:   PWM.c
 *
 *      Ce fichier contient notamment l'implémentation complète des
 *      différentes fonctions demandées dans le module PWM.
 ******************************************************************************
*/

/* Includes */
#include "pwm.h"

/**
  * Fonction PWM_Init().
  *
  *  Cette fonction permet l'initialisation du PWM du TIM2 notament avec une configuration de ses regsitres
  *  ainsi que celui de la broche GPIO (PA0) à  laquelle le signal généré sera envoyé.
  *
  */
void PWM_Init(){
	// étape 1 : mettre les  bits adéquats des registres du périphérique RCC pour
    // activer les holorges des registres à configurer pour faire fonctionner le PWM.

	RCC -> AHB1ENR |= BIT0; // On active la clock du GPIO qui servira de sortie au signal du PWM (Timer2)
	RCC -> APB1ENR |= BIT0; // On active la clock du TIM2.

	// étape 2 : Configuration du GPIO de la broche PA5 en mode alternate en tant que sortie du TIM2.
	GPIOA -> MODER &= ~(BIT11 | BIT10); // Pour s'assurer que les bits qu'on veut mettre à "10" sont bien à "00" et ne pas avoir une configuration inattendue.
	GPIOA -> MODER |= BIT11; // Seul le bit11 est mis à "1", le bit 10 étant déjà à 0 par l'opération précédente.

	GPIOA -> OSPEEDR &= ~(BIT11 | BIT10);
	GPIOA -> OSPEEDR |= BIT10; // Seul le bit 10 est mis à 1, étant donné qu'on doit mettre le champ des des 2 bits à "01"

	GPIOA -> AFR &= ~( BIT23 | BIT22 | BIT21 | BIT20); // On nettoie le champ AFRL5 avant de lui donner la valeur de AF1 (0001).
	GPIOA -> AFR |= BIT20;

	// étape 3 : Configuration du TIM2 pour le PWM.


}

/**
  * Fonction PWM_ajustDutyCycle().
  *
  *  Cette fonction permettra d’ajuster le ratio (Duty Cycle).
  *  Pour cela, elle reçoit en paramètre un entier "valeur_duty_cycle" exprimant le pourcentage du duty Cycle.
  *
*/

void PWM_ajustDutyCycle(uint8_t valeur_duty_cycle){
	;
}


/**
  * Fonction PWM_ajustFrequence().
  *
  *  Cette fonction permettra d’ajuster le frequence.
  *  Pour cela, elle reçoit en paramètre un entier "frequence" exprimant la fréquence à ajuster.
  *
*/
void PWM_ajustFrequence(uint8_t frequence){
	;
}

