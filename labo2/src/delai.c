/*
******************************************************************************
 *
 *  Created on: 16 sept. 2026
 *      Author: Antho
 *      File:   delai.c
 *
 *      Ce fichier contient notamment l'implémentation complète des
 *      différentes fonctions demandées dans le module delai.
 ******************************************************************************
*/

/* Includes */
#include "delai.h"


// On crée ici une varibale dans le but de l'incrémenter toutes les 1 ms.
static volatile unsigned int compt_millis = 0;

/**
  *  Fonction SysTick Handler.
  *
  *  Cette fonction permet l'incrémentation d'un compteur toutes les 1ms.
  *
  */
void SysTick_Handler(void)
{
	compt_millis++;
}

/**
  *  Fonction Systick_current_compt_value.
  *
  *  Cette fonction permet de retourner la valeur actuelle du compteur
  *  incrémenté toutes les 1ms.
  *
  */
unsigned int Systick_current_compt_value(){
		return compt_millis;
}


/**
  * Fonction SysTick_Init().
  *
  *  Cette fonction permet l'initialisation du Systick notament avec une configuration de ses regsitres
  *  VAL, LOAD et CTRl
  *
  */
void SysTick_Init(){
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

	SysTick->VAL = 0U; // On pouvait mettre n'importe quelle valeur pour remettre le compteur actuel du Systick à 0.

	SysTick->LOAD = ((SystemCoreClock / 1000)-1); // On met le Load du Systick à 71999 afin de pouvoir créer une base de temps de 1s pour notre Timer Systick
	// la valeur 71999 est obtenue par le calcul réalisé par l'opération ici affectée au registre LOAD.
}

/**
  * Fonction SysTick_create_delay().
  *
  *  Cette fonction permet de créer le delai souhaité mis en paramètre à partir
  *  du compteur de millisecondes
  *
  */
void SysTick_create_delay(unsigned int delay){
	unsigned int start_time = Systick_current_compt_value();
	// le microcontrôleur appelera la routine d'interruption Systick_Handler() comme elle le fait par défaut,
	// toutes les 1 ms, ce qui aura pour résultat d'incrémenter le compteur renvoyé par
	// Systick_current_compt_value() jusqu'à ce que la valeur soit supérieure au délai souhaité(en ms) et c'est ainsi que cette fonction
	// terminera son exécution.
	while ( Systick_current_compt_value() - start_time < delay){}
}


