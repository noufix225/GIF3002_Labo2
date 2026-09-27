/*
******************************************************************************
 *
 *  Created on: 23 sept. 2026
 *      Author: &&&
 *      File:   ADC.c
 *
 *      Ce fichier contient notamment l'implémentation complète des
 *      différentes fonctions demandées dans le module ADC.
 ******************************************************************************
*/

/* Includes */
#include "adc.h"


// Cette variable permettra de conserver le résutat obtenu après chaque conversion de l'ADC.
static volatile uint16_t adc_result_conv = 0;

/**
  * Fonction ADC_Init().
  *
  *  Cette fonction permet l'initialisation de l'ADC notament avec une configuration de ses regsitres
  *  ainsi que celui de la broche GPIO ( PC3 ) au quel est reliée son entrée analogique.
  *
  */
void ADC_Init(){
	// étape 1 : mettre les  bits adéquats des registres du périphérique RCC pour
	// activer les holorges des registres à configurer pour faire fonctionner l'ADC.

	RCC -> AHB1ENR |= BIT2; // Pour activer la clock du GPIO du port C
	RCC -> APB2ENR |= BIT8; // Pour activer la clock de l'ADC

	// étape 2 : la configuration de la broche GPIO en mode analog
	GPIOC -> MODER |= (BIT7 | BIT6) ;

	// étape 3 : la configuration de l'ADC lui_même.
	/*
	  * Un seul canal (le Channel 13 en occurence), donc une séquence d’une seule conversion.
	  * Les bits 23 à 20 du registre SQR1 permettent la sélection du
	  * nombre total de conversions dans la séquence de conversion du canal. ils sont par défaut
	  * à la valeur "0000", ce qui indique un total de 1 conversion comme voulu ici, on ne modifie
	  * donc rien ici.
	  *
	  * Par contre les bits 4 à 0 du registre SQR3 doivent être modifiés, en effet, on doit y
	  * inscrire la valeur hexadécimale de notre canal 13, ces bits indiquant la position de la 1ère conversion de la séquence
	  * dans la valeur de ce registre
	  * */
	  ADC1 -> SQR3 &= ~(BTI4 | BTI3 | BTI2 | BTI1 | BTI0); // On commence par nettoyer les bits concernés
	  ADC1 -> SQR3 |= (BTI3 | BTI2 | BTI0); // Puis on applique le masque sur les bits qui doivent être à 1

	// Pas de DMA, on en touche donc pas au BIT 8 du registre CR2

    /* Résolution de conversion de 12 bits, il faut pour cela configurer le registre CR1
	 en mettant ces bits 25, 24 à "00", il s'agit déjà de la configuration par défaut,
	 donc on n'y touchera pas */

	/* Les 12 bits alignés à droite, le BIT ALIGN du registre CR2 est déjà par défaut en right alignement,
	   il n'est donc pas modifié. */

	/* Pour le single conversion MODE, c'est le bit CONT du registre 2 qui est à modifié, mais vu qu'il
	 a déjà par défaut la valeur équivalente à ce mode, inutile de le modifier. */

    // Enfin le bit EOCIE du registre CR1 doit être mis à 1 afin d'activer l'interruption EOC (End of Conversion).
    ADC1 -> CR1 |= BIT5;

    /* Enfin, il faut s'assurer de configurer le registre ISER du NVIC afin que le coeur puisse traiter l'interruption EOC lorsqu'elle est générée.
     * Pour cela, il suffit d'utiliser la fonction NVIC_EnableIRQ() conçu à cet effet avec en paramètre le
     * ADC_IRQn qui est une macro qui nous est donné par le fichier
     * stm32f4xx.h contenant le numéro correspondant aux interruptions matérielles de l'ADC.*/
     void NVIC_EnableIRQ(ADC_IRQn);

     ADC1 -> CR2 |= BIT0; // Le bit ADON permettant au bit SWSTART de pouvoir être activé
}

/**
  * Fonction ADC_conversion().
  *
  *  Cette fonction permettra la conversion des valeurs faite par l'ADC.
  *
*/

void ADC_start_conversion(){
	/* Le bit SWSSTART du registre CR2 est le bit permettant au logiciel de débuter la conversion, pour cela il doit être mis à 1
	   On constate en lisant le manuel que pour que cela fonctionne, il faut aussi le que le bit ADON du même registre
	   soit mis à 1, c'est lui qui permet d'enclencher la conversion de l'ADC. Il est donc activé dans la fonction d'initialisation de l'ADC. */
	   ADC1 -> CR2 |= BIT30;
}

/**
  * Fonction ADC_GetconvertedValue().
  *
  *
  * Cette fonction permettra de retourner la valeur convertie par l’ADC.
*/
uint16_t ADC_GetSample(){
	/*
	 * Afin de réaliser cette fonction, on a principalement besoin du registre DR de l'ADC dont les bits de 0 à 15
	 * contiennent le résultat de la conversion faire par le canal de l'ADC. Vu que l'alignement a été configuré à droite
	 * et que la résolution de la conversion a été configuré avec 12 bits, les bits 15 à 12 seront automatiquement à 0.
	 *
	 * le type uint16_t permet d'indiquer qu'on veut juste récupérer les bits 15 à 0, étant donné que les autres sont réservés dans ce registre.
	 * En retournant la variable adc_result_conv, on retourne le résultat de la lecture du registre DR faite dans la fonction d'interruption de
	 * l'ADC implémentée ci-dessous. */
	return adc_result_conv;
}

/**
  * Fonction ADC_IRQHandler().
  *
  *
  *   Il s'agit de la fonction d'interruption générée par l’ADC lorsque une conversion est prête.
  *
  *   Logique de derrière le code de cette fonction : On apprend au niveau du registre SR de l'ADC que son bit 1 (EOC) est immédiatement forcé à 1 par le matériel.
  *   lorsqu'une conversion est achevé. Et cela, couplé au fait que le Bit EOCIE du registre CR1 soit activé
  *   génère l'interruption ADC_IRQHandler dont le code sera traité par le programme de la carte, si la configuration du registre
  *   ISER du NVIC a été effectué adéquatement. On apprend aussi que le 1 du bit EOC s'efface automatiquement à la lecture du registre DR.
  *   De ce fait notre fonction d'interruption doit le lire afin que le bit reste bloqué à 1 que le programme reste figé à l'interruption.
  *   Enfin, le résultat de la conversion lu doit être stocké dans une variable.
*/

void ADC_IRQHandler(){
	adc_result_conv = ADC1 -> DR; // On utilise ici la variable conçue à cet effet;
}
