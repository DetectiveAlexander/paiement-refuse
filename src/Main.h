#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <vector>
#include "Carte.h"
using namespace std;

/**
*@class Main
*
*@brief Classe composée d'un tableau dynamique de cartes et d'une mise; 
**Des fonctions de calcul de la valeur totale de la main, des options de choix et 
*gestions des modes, et d'ajout de cartes
*/
class Main {
	private :
		int mise;             ///<int argent misé pour la main
		bool estSplitAs;      ///<état du mode split de la main
		bool estDouble;       ///<état du mode double de la main
		bool estStay;         ///< état du mode stay de la main
		vector<Carte> cartes; ///<tableau dynamique des cartes composant la main
	   
	public :
		/** 
		@brief Constructeur de la classe : initialise mise à 0 
		*n’alloue aucune mémoire pour le tableau de cartes
		*initialise estSplitAs, estDouble, estStay à false
		*/
		Main();	
		 
		/** 
		*@brief Constructeur de la classe : initialise la mise
		*initialise estSplitAs, estDouble, estStay à false
		*n’alloue aucune mémoire pour le tableau de cartes
		*@param m Entier représentent la mise de la main
		*/
		Main(int m);
		
		/**
		*@brief Destructeur de la classe : déallocation de la mémoire du tableau de cartes (fait automatiquement)
		* et mise à jour du champ mise à 0
		*et des champs estSplitAs, estDouble, estStay à false
		*/
		~Main();
		
		/**
		*@brief Accesseur : récupère la mise de la main.
                *@return Un Entier représentant la valeur mise.
                */
		int getMise()const ;
		
		/**
		*@brief Accesseur : récupère l'état du mode Split de la main.
                *@return Un Booléen représentant l'état de estSplitAs.
                */
		bool getEstSplitAs()const;
		
		/**
		*@brief Accesseur : récupère l'état du mode Double de la main.
                *@return Un Booléen représentant l'état de estDouble.
                */
		bool getEstDouble()const;
		
		/**
		*@brief Accesseur : récupère l'état du mode Stay de la main.
                *@return Un Booléen représentant l'état de estStay.
                */
		bool getEstStay()const;
		
		/**
		*@brief Calcul la somme de la valeur des cartes de la main avec verification de la valeur de l'As
		*@return Un Entier représentant le résultat de cette somme
		*/
		int valeur() const;
		
		/**
		*@brief Vérifie si la main fait un BlackJack (la valeur d'une main de 2 cartes est égale à 21)
		*@return Un Booléen représentant le résultat de cette vérification
		*/
		bool estBJ() const;
		
		/**
		*@brief Modifie la valeur de la mise de la main
		*@param m valeur mise de la main.
		*/
		void setMise(int m);
		
		/**
		*@brief Modifie l'état du mode estSplit de la main en true
		*/
		void setSplitAs();
		
		/**
		*@brief Setteur pour doucler la main 
		*L'état du mode estDouble de la main en true, 
		* ajoute une carte au tableau de cartes de la main et double la valeur de la mise
		*@param ca la carte ajoutée à la main
		*/
		void setDouble(const Carte ca);
		
		/**
		*@brief Modifie l'état du mode estStay de la main en true
		*/
		void setStay();
		
		/**
		*@brief Ajoute une carte à la main dans le tableau de cartes
		*@param ca la carte ajoutée à la main
		*/
		void ajouteCarte(Carte ca);
		
		/**
		*@brief Récupère le nombre de carte de la main
		*@return Un Entier représentant la taille du tableau de cartes.
        	*/
		int getNbCarte()const;

		/** @brief supprime une cartfe de la main -> utile pour le Split
		 * @param indice l'indice de la carte à supprimer
		 */
		void supprimerCarte(int indice);

		/** @brief accesseur pour récupérer une carte spécifique de la main
		 * @param indice l'indice de la carte souhaitée
		 * @return une référence constante vers la carte d'indice donné
		 */
		const Carte& getCarteIndice(int indice)const;
		
		/**
		*@brief Fonction statique de test de régression pour tester et valider le comportement de la classe Main.
        	*/
		static void testRegression();
		
	};
	

#endif
