/*
******************************************************************************
 *
 *  Created on: 10 sept. 2026
 *      Author: Antho
 *      File:   gpio.h
 *
 *      Ce fichier contient principalement les prototypes des fonctions
 *      demandées dans le module GPIO, ainsi que la définition des adresses de bases
 *      des différents périphériques liès aux I/Os que nous souhaitons utiliser.
 *      .
 ******************************************************************************
*/

#ifndef GPIO_H_
#define GPIO_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/* Définition des adresses de bases des ports A et G et du
 * périphérique RCC indiqués dans le ref Manuel du STM32, p.65
 */

#define RCC 0x40023800
#define GPIOA_BASE 0x40020000
#define GPIOG_BASE 0x40021800

/* Adresse du registre AHB1ENR qui est le registre permettant l'activation de
 * l'horloge de chaque périphérique connecté au bus AHB1 parmi lesquels
 * on a les périphériques des GPIO dont celui du port A et du port G. On trouve notamment
 * l'offset de ce registre à la p.180 du manuel.
 */

#define RCC_AHB1ENR (*(volatile uint32_t*)(RCC + 0x30))


// Prototypes des 3 fonctions demandées
/*  À noter qu'elles ont été crées dépendament du contexte du laboratoire. En effet,
 *  il n'y a précisement que 3 I/O qui nous intéressent dont deux sur
 * les 3 qui sont reliées au même port GPIO (de broches différentes). Le code de ces fonctions aurait été
 * moins circonstanciel en cas d'un nombre plus élévé de différentes broches.
*/

/*  Fonction GPIO_InitPin() - Pour la configuration d'une broche de GPIO.
 *
 *  Les paramètres de cette fonction sont :
 *
 *    le port - indiquant s'il s'agit du port A de notre entrée, le bouton utilisateur où
 *    s'il s'agit du port port G de nos sorties les LED. En fonction de cette information,
 *    on saura comment configuer les registres de configuration pour le mode, le pull, etc.
 *
 *    le pin - indiquant précisement le pin de la broche afin de configurer efficament les registres
 *    en modifiant les bits ou groupes de bits adéquats des valeurs hexadécimales contenues aux adresses
 *    mémoires des regitsres GPIO permettant de modifier le comportement physique du microcontrôleur STM32.
 *
 */
void GPIO_InitPin(uint32_t port, uint8_t pin);

/*  Fonction GPIO_WritePin() - Pour l'écriture dans une GPIO.
 *
 *  En plus des paramètres de la fonction précédente, cette fonction a aussi le paramètre
 *  value qui permet d'indiquer la valeur qu'on veut écrire à la broche GPIO, soit un 1 ou soit un 0.
*/

void GPIO_WritePin(uint32_t port, uint8_t pin, uint8_t value);


/*  Fonction GPIO_ReadPin() - Pour la lecture de l'état d'une GPIO, retournant ainsi un 1 ou un 0.
 *  Elle a les mêmes paramètres que la fonction GPIO_InitPin(). Elle retournera un nombre entier non signé
 *  sur 8 bits tel que sa valeur sera soit 1, soit 0 comme demandé.
*/

uint8_t GPIO_ReadPin(uint32_t port, uint8_t pin);


#endif /* GPIO_H_ */
