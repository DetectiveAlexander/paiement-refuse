#ifndef _DECK_H_
#define _DECK_H_

#include "Carte.h"
#include <vector>
using namespace std;


/**
*@class Deck
*@brief classe gérant un ensemble de cartes (un ou plusieurs paquets).
**Cette classe permet de stocker des objets Carte dans un vecteur, 
*de les mélanger et de simuler la pioche. 
*/
class Deck{
	private:
		vector<Carte> cartes; ///< Tableau dynmique stockant des cartes de type Carte
		int nbDeck; ///< Le nombre de paquets de 52 cartes utilisé
	public:
		/** 
		*@brief Constructeur par défaut
		*Initialsie un deck vide
		*/
		Deck();

		/** *@brief Constructeur avec un parametre
		*Initialise un deck de n paquets
		*@param n le nombre de paquet a creer 
		*/
		Deck(int n);

		/** *@brief Destructeur de la classe */
		~Deck();

		/** 
		*@brief Mélange aléatoirement le Deck avec l'algo Mersenne Twister 
		*/
		void melanger();

		/** 
		*@brief Retire et renvoie la carte située en haut du deck
		*@return La carte pioché visible 
		*/
		Carte piocher();

		/**
		*@brief supprimme et réinitialise
		*@param nbdeck le nombre de pioche à créer
		*/
		void initDeck(int nbdeck);

		/** 
		*@brief Accesseur pour le nombre de paquets
        *@return Le nombre de paquets de 52 cartes
		*/
		int getNbDeck() const;
		/**
		*@brief Accesseur du nombres de cartes au total 
		*@return nombre de cartes en long unsigned int*/
		long unsigned int getNbCarte()const;

		/** 
		*@brief Fais des tests pour le bon fonctinnement de la classe 
		*/
		static void testRegression();
	};

#endif
