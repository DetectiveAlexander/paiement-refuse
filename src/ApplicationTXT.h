#ifndef APPLICATIONTXT_H_
#define APPLICATIONTXT_H_

#include "JeuBlackJack.h"

/**
*@class ApplicationTXT
*@brief Classe gérant toute l'application sur la console
*avec l'affichage du jeu, des Menus et la gestion de 
*toutes les fontionnalités
*/
class ApplicationTXT {
	private:
		JeuBlackJack jeu; ///< jeu de type JeuBlackJack 
	public:
	/** 
	*@brief constructeur de base de la classe */
		ApplicationTXT();
	/** 
	*@brief destructeur de la classe */
		~ApplicationTXT();
	/** 
	*@brief méthode principale gérant la boucle de jeu 
	 * @param jeu le jeu de blackjack à utiliser pour la partie
	*/
		void Boucle(JeuBlackJack& jeu);
		
};

#endif
