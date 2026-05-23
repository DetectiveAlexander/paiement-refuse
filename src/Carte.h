#ifndef _CARTE_H_
#define _CARTE_H_
#include <string>

/**
*@brief Représente les couleur (symboles) des cartes
** Le numéro permet de chercher dans l'image des 52 cartes 
*la colonne correspondante à la couleur
*/
enum CouleurCarte {
	VIDE, ///< 0 = cartes sans couleurs
	TREFLE, ///<  1: Trèfle
	CARREAU, ///< 2: Carreau
	COEUR, ///< 3: Coeur
	PIQUE  ///< 4: Pique
};

/**
*@class Carte
*
*@brief classe initialisant toutes les cartes utilisée dans le jeu de BlackJack 
*
*/
class Carte {
	private :
		CouleurCarte couleur; ///< Couleur (symbole) de la carte
		int valeur; ///< Valeur des cartes: As=1, Valet = 11 ; Dame = 12 ; Roi = 13
		bool estVisible; ///< La carte est face visible ou non (utile à l'affichage et le croupier)
	public :
		/**
		*@brief constructeur de base de la classe, intialise une couleur vide et une valeur nulle
		*/
		Carte();
		
		/**
		*@brief constructeur avec paramètres de la classe, 
		**initalise à une valeur et une couleur choisies
		*@param valeur  valeur de la carte
		*@param couleur couleur de la carte
		*/
		Carte(int valeur, CouleurCarte couleur);
		
		/**
		*@brief destructeur de la classe, remet tous les paramètres à 0
		*
		*/
		~Carte();
		
		/**
		*@brief Getter du paramètre valeur de la carte
		*@return int de la valeur de la carte
		*/
		const int& getValeur() const;
		
		/**
		*@brief getter de la couleur de la carte en CouleurCarte (int)
		*@return couleur de la carte en Int
		*/
		const CouleurCarte& getCouleurInt() const;
		
		/**
		*@brief getter de la couleur de la carte en string
		*@return couleur en String 
		*/
		std::string getCouleurString() const;
		

		/**
		*@brief getter de la visibilité de la carte, utile pour le croupier qui devra 	
		*avoir une carte cachée au début et dans le deck ou les cartes ne doivent pas 
		*être affichée
		*@return bool de la visibilité de la carte
		*/
		const bool& getVisible() const;
		
		/**
		*@brief setter de la visibilité de la carte, 
		*change le statut de visibilité à son inverse
		*/
		void setVisible();
		
		/**
		*@brief setter de la visibilité de la carte en modifiant le status 
		*@param booléen à mettre en statut
		*/ 
		void setVisible(bool state); 

		/**
		*@brief permet de créer un string avec la valeur (ou figure) de la carte suivie de sa couleur.
		*@return un string avec la valeur et la couleur de la carte
		*/ 
		std::string afficheCarte()const;
		
		/**
		*@brief fonction de test de la classe
		*
		*/
		static void testRegression();
		
};





#endif
