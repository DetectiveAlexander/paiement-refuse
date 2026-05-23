#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "Main.h"
#include "Deck.h"
#include <string>


/** 
*@class Joueur
*@brief La classe qui gère les actions du joueurs et ses 3 mains
*/
class Joueur {
	private:
		std::string nom;		///<string nom du joueur
		vector<Main> mains;		///<Tableau dynamique de Main
		int argent;				///<int argent totale du joueur
		
	public: 
		/** 
		@brief Constructeur de la classe :n'attribut pas de nom  
		*n’alloue aucune mémoire pour le tableau de Main
		*initialise argent à 0.
		*/
		Joueur();

		/** 
		*@brief Constructeur de la classe : initialise nom à n,
		*argent à arg,
		*n’alloue aucune mémoire pour le tableau de Main.
		*@param n string repréentant le nom du joueur.
		*@param arg entier rprésentant le solde du joueur.
		*/
		Joueur(std::string n, int arg);

		/**
		*@brief Destructeur de la classe : déallocation de la mémoire du tableau de Main (fait automatiquement)
		*mise à jour du champ argent à 0
		*et le champ nom est vidé.
		*/
		~Joueur();
		
		/**
		*@brief Ajoute une main au tableau de Main et retire la mise de cette main à 'argent'.
		*@param m un Entier représentant la valeur de la mise souhaitée pour cette nouvelle main.
		*/
		void ajouteMain(int m);


		/**
		*@brief Fait appel à la fonction setStay de Main.h .
		*@param indiceMain un Entier représentant l'indice de la main concérnée par l'action.
		*/
		void stay(int indiceMain);

		/**
		*@brief Accesseur : récupère le nom du joueur.
        *@return Un String représentant le contenu de 'nom'.
        */
		const std::string& getNom()const;

		/**
		*@brief Accesseur : récupère la valeur de 'argent' de Joueur.
        *@return Un Entier représentant la valeur de 'argent'.
        */
		const int& getArgent()const;

		/**
		*@brief Modifie la valeur de l'argent du joueur 
		*@param a un Entier représentant la nouvelle valeur de 'argent' de Joueur
		*/
		void setArgent(int a);

		/**
		*@brief Vérifie que la main choisie respecte les condition pour faire hit.
		*@param indiceMain un Entier représentant l'indice de la main concérnée par l'action.
		*@return Un Booléen représentant la possibilité ou non de faire hit.
		 */
		bool peutHit(int indiceMain) const ;

		/**
		*@brief Ajoute une carte piochée à la main choisie.
		*@param indiceMain un Entier représentant l'indice de la main concérnée par l'action.
		*@param d un Deck représentant la pioche utilisée pour la complétion de la main.
		*/
		void hit(int indiceMain, Deck& d);

		/**
		*@brief Vérifie que la main choisie respecte les condition pour faire double.
		*@param indiceMain un Entier représentant l'indice de la main concérnée par l'action.
		*@return Un Booléen représentant la possibilité ou non de faire double.
		 */
		bool peutDouble(int indiceMain) const;

		/**
		*@brief Vérifie que la main choisie respecte les condition pour faire split.
		*@param indiceMain un Entier représentant l'indice de la main concérnée par l'action.
		*@return Un Booléen représentant la possibilité ou non de faire split.
		 */
		bool peutSplit(int indiceMain) const;

		/**
		*@brief Fait appel à la fonction setDouble de Main.h .
		*@param indiceMain un Entier représentant l'indice de la main concérnée par l'action.
		*@param d un Deck représentant la pioche utilisée pour la complétion de la main.
		*/
		void doubler (int indiceMain, Deck& d);

		/**
		*@brief Enlève une carte à la main de 2 cartes du joueur; la carte enlevée est ajoutée à une nouvelle main dans 'mains' et chacune des mains pioche une nouvelle carte.
		*(si la main initiale est composée de 2 As, les mains formées de celle-ci ne peuvent plus split)
		*@param indiceMain un Entier représentant l'indice de la main concérnée par l'action.
		*@param d un Deck représentant la pioche utilisée pour la complétion des mains.
		*/
		void split(int indiceMain, Deck& d); 

		/**
		*@brief Vide la tableau de Main
		*/
		void viderTabMain();

		/** @brief setteur pour changer la mise d'une main
		 * @param indiceMain l'indice de la main à configurer
		 * @param mise la nouvelle mise
		 */
		void setMiseMain(int indiceMain,int mise);

		/** @brief accesseur pour récupérer une main spécifique
		 * @param indice l'indice de la main souhaitée
		 * @return une référence constante vers la main d'indice donné
		 */
		const Main& getMainIndice(int indice)const;

		/** @brief accesseur pour récupérer le nombre de mains du joueur
		 * @return le nombre de mains du joueur
		 */
		const int getMainTaille()const;
		/**
		*@brief Fonction statique de test de régression pour tester et valider le comportement de la classe Joueur.
        	*/
		static void testRegression();
		 
};

#endif
