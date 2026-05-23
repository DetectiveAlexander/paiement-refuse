#ifndef _CROUPIER_H_
#define _CROUPIER_H_

#include "Carte.h"
#include "Deck.h"


/** *@class Croupier
*@brief Classe gérant la main et les actions du Croupier
*Elle permet de stocker les cartes reçues, de gérer la mise de la table
*/
class Croupier {
	private:
		vector<Carte> cartes; ///< Tableau dynmique stockant les cartes de type Carte
	public:
		/** *@brief Constructeur par défaut 
		* Intialise tous à 0*/
		Croupier();

		/** *@brief Destructeur de la classe */
		~Croupier();

		/** *@brief Ajoute un carte visible à la main 
		*@param ca la carte à ajouter */
		void ajouteCarte(Carte ca);

		/** *@brief initialise la classe */
		void initCroupier();

		/** *@brief Ajoute un carte cachée à la main 
		*@param ca la carte à ajouter */
		void ajouteCarteCache(Carte ca);

		/** *@brief Révèle une carte cachée 
		*@param indice l'indice de la position de la carte à révéler */
		void revelerCarte(int indice);

		/** *@brief Accesseur pour récupérer la valeur de la main
        *@return la somme de la meilleur main */
		int getValeurMain()const;

		/** *@brief Accesseur pour récupérer une carte spécifique de la main
        *@param indice l'indice de la carte souhaitée
        *@return référence constante vers Carte correspondant à l'indice
        */
		const Carte& getCarte(int indice) const;

		/** @brief accesseur pour récupérer le nombre de cartes du croupier
		 * @return le nombre de cartes du croupier
		 */
		int getNbCarteCroupier() const;

		/** @brief Fonction pour le croupier lorsqu'il doit tirer les cartes jusqu'à atteindre 17
		 * @param d Référence vers le deck de cartes à utiliser pour tirer les cartes 
		 */
		void hit17(Deck& d);

		/**
		*@brief Vérifie si les cartes font un BlackJack (la valeur d'une main de 2 cartes est égale à 21)
		*@return Un Booléen représentant le résultat de cette vérification
		*/
		bool estBJCroupier() const;

		/** *@brief Fais des tests pour le bon fonctinnement de la classe */
		static void testRegression();
	};

#endif
