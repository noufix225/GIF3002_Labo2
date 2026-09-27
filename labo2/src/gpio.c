/*
******************************************************************************
 *
 *  Created on: 10 sept. 2026
 *      Author: Antho
 *      File:   gpio.c
 *
 *      Ce fichier contient notamment l'implémentation complète des
 *      différentes fonctions demandées dans le module GPIO.
 ******************************************************************************
*/

/* Includes */
#include "gpio.h"

// Implémentation des trois fonctions

// 1. Fonction pour la configuration du GPIO
void GPIO_InitPin(uint32_t port, uint8_t pin){
	// On crée des pointeurs génériques vers les adresses des registres GPIO pour la configuration des broches
	volatile uint32_t* GPIO_MODER = (volatile uint32_t*)(port + 0x00);
	volatile uint32_t* GPIO_OTYPER = (volatile uint32_t*)(port + 0x04);
	volatile uint32_t* GPIO_OSPEEDR = (volatile uint32_t*)(port + 0x08);
	volatile uint32_t* GPIO_PUPDR = (volatile uint32_t*)(port + 0x0C);

	if (port == GPIOA_BASE){
		// on règle le mode à Input étant donné que notre bouton utilisateur de la broche PA0 est une entrée
		*GPIO_MODER &= ~(3U << (pin * 2));

		// On s'assure de mettre d'abord les 2 bits à 00 avant de programmer le pull down(10) car on ne connait pas leur
		// état d'origine afin d'éviter tout un cas de configuration incohérent.
		*GPIO_PUPDR &= ~(3U << (pin * 2));
		*GPIO_PUPDR |= (2U << (pin * 2));
	}
	else if (port == GPIOG_BASE) {
		// étant donné qu'on veut configurer le mode à output (01), comme
		// précédement on met d'abord le groupe de bits concernant le pin du port
		// de la LED à 00, pour s'assurer qu'on tombe pas sur un cas de configuration
		// non désiré après avoir forcé les bits correpondants
		*GPIO_MODER &= ~(3U << (pin * 2));
		*GPIO_MODER |= (1U << (pin * 2));

		// Par mesure de sécurité, on désire de configurer les valeurs des registres suivants bien qu'elles soient les mêmes que les
		// valeurs par défaut, parce qu'on est pas à l'abri d'un flottement des valeurs au niveau de certains bits,
		// étant donné les différentes pertubations qui peuvent avoir lieu.

		// le type de sortie est push/pull pour les LEDs, donc le bit correspondant
		// au pin doit rester à 0
		*GPIO_OTYPER &= ~(1U << pin);

		// On choisira de mettre la vitesse de sortie à medium donc le groupe de 2 bits
		// correspondant à 01. On réalise donc la procédure de "sécurité" souvent réalisée
		// dans les lignes suivantes.
		*GPIO_OSPEEDR  &= ~(3U << (pin * 2));
		*GPIO_OSPEEDR  |= (1U << (pin * 2));

		// On choisira de ne configurer aucune résistance pull up ou pull down pour les LEDS, les bits
		// concernées doivent donc être mis à 00 selon le manuel
		*GPIO_PUPDR &= ~(3U << (pin * 2));
		}
}

// 2. Fonction pour l'écriture dans une GPIO
void GPIO_WritePin(uint32_t port, uint8_t pin, uint8_t value){
	// On crée un pointeur générique vers l'adresse mémoire du registre ODR,
	// permettant, selon le manuel, la lecture et l'écriture des bits dans les GPIO.
	volatile uint32_t* GPIO_ODR = (volatile uint32_t*)(port + 0x14);
	if (value == 1){
		*GPIO_ODR |= (1U << pin); // On met le bit de la valeur correspondant au pin de la broche à 1
	}
	else {
		*GPIO_ODR &= ~(1U << pin); // On met le bit de la valeur correspondant au pin de la broche à 1
	}
}

// 3. Fonction pour la lecture du GPIO
uint8_t GPIO_ReadPin(uint32_t port, uint8_t pin){
	// Encore une fois, on crée un pointeur générique vers l'adresse mémoire du registre IDR,
	// permettant, selon le manuel, la lecture de la valeur d'entrée du port I/O, indiquant ainsi
	// l'état de la broche GPIO
	volatile uint32_t* GPIO_IDR = (volatile uint32_t*)(port + 0x10);

	// On déréférence le contenu du regsitre IDR, et on décale vers l'extrème droite le bit correspondant
	// au pin de notre port. À cela, on ajoute le masque & 1U, au cas où si les bits des broches voisines
	// n'étaient pas à 0, pour que la valeur retournée ne soit pas parasité par eux.
	return ((*GPIO_IDR >> pin) & 1U);
}
