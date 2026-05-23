#ifndef _JEUBLACKJACK_H_
#define _JEUBLACKJACK_H_

#include <string>
#include "Joueur.h"
#include "Deck.h"
#include "Croupier.h"
using namespace std;

/**
*@class JeuBlackJack
*@brief Classe gérant le croupier, le joueur et la pioche
*/
class JeuBlackJack {
    private:
        Croupier croupier; ///< parametre de type Croupier
        Joueur joueur; ///< parametre de type Joueur
        Deck pioche;///< parametre de type Deck
    public:
        /** *@brief Consturcteur par défaut */
        JeuBlackJack();

        /** *@brief Constructeur avec des parametres 
        *@param s le nom du joueur de type String
        *@param argent l'argent de départ du joueur de type entiers*/
        JeuBlackJack(string s, int argent);

        /** *@brief Destructeur par défaut */
        ~JeuBlackJack(); 

        /** 
        *@brief initialise le jeu pour de nouveau tour et les mise en même temps 
        ** Puis pioche les cartes et les crates pour le croupier
        *@param nbMains le nb de mains <=3 à créer
        *@param listeOfMise liste des mises pour chaque main */     
        void initTour(int nbMains,int listeOfMise[3]);

        /** @brief setteur pour changer l'argent du joueur
         * @param argent la nouvelle valeur de l'argent du joueur
         */
        void setArgentJoueur(int argent);

        /** @brief exécute une action sur une main donnée
         * @param indiceMain l'indice de la main sur laquelle exécuter l'action
         * @param exe l'action à exécuter (1:hit - 2:stay - 3:double - 4:split)
         */
        void executeLaMain(int indiceMain,int exe);///1:hit - 2:stay - 3:double - 4:split

        /** @brief fait le tour du croupier jusqu'à atteindre 17  */
        void tourCroupier17();///< croupier va piocher jusqu'a 17 en supposant que c'est dejà init
        
        /** *@brief setteur pour changer la mise d'une main 
        *@param indiceMain indice de la main à configurer
        *@param mise la nouvelle mise*/
        void setMainMiser(int indiceMain,int mise);///< miser pour la main d'indice

        void hitCroupier();

        void revelerCarteCroupier();

        /**
        *@brief get par référence de Deck */
        const Deck& getDeck() const;

        /**
        *@brief getteur par référence de Joueur */
        const Joueur& getJoueur() const;

        /**
        *@brief getteur par référence de Croupier */
        const Croupier& getCroupier() const;

        /** *@brief */
        static void testRegression ();
};

#endif