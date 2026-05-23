#ifndef APPLICATIONSDL_H_
#define APPLICATIONSDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <cmath>
#include <vector>

#include "JeuBlackJack.h"
#include "SDL_Carte.h"

/** 
*@brief Etats possibles du jeu servant à pouvoir gérer les différentes phases de jeu
*
*/
enum EtatJeu {
	MENU, ///< Menu de l'application, choix des mises et nb de mains
	FINPARTIE, ///< Affichage des resultats de la partie et option pour rejouer ou quitter
	JOUEUR, ///< Tour de jeu, affichages cartes et interactions avec les mains
	ANIMATION ///< Animatiojn des cartes du croupier (distribution et tour croupier)
};

/** 
*@struct InfoJeu
*@brief Structure stockant les informations calculés pendant le jeu et utilisées sur la fonction affichage 
*/
struct InfoJeu {
	/**
	* @brief booléens pour gérer les différentes options d'affichage et de jeu
	*/
    bool fleche; ///< fleche : affiche la fleche pour choisir les mises
	bool impossible;///< impossible : affiche le message d'impossibilité de rejouer si le joueur n'a pas assez d'argent
	bool impossible2;///<impossible2 : affiche le message d'impossibilité de choisir une main supplémentaire si le joueur n'a pas assez d'argent
	bool miseOblig;///<miseOblig : indique que le joueur doit choisir une mise pour au moins une main avant de pouvoir commencer la partie	
	bool misesChoisies;///<misesChoisies : indique que le joueur a terminé de choisir ses mises et peut commencer la partie
	float MAIN_OFFSET;///< MAIN_OFFSET : variable pour gérer l'espacement entre les mains du joueur à l'affichage en fonction du nombre de mains choisies
};

/**
* @class ApplicationSDL
* @brief Classe gérant l'application entière avec SDL, calcul de jeu et affichage 
*/
class ApplicationSDL {
	private :
		JeuBlackJack jeu; ///<Classe gérant les règles du jeu BlackJackk et les actions
		SDL_Window *window; ///<Fenetre SDL vide 
		SDL_Renderer *renderer; ///<Renderer SDL
		SDL_Texture *textureCartes; ///< Texture des cartes (dos et face)
		SDL_Texture *textureFleche; ///<Texture de la flèche de mise courante dans le menu
		SDL_Texture *fondTexture; ///< Texture du fond d'écran
		TTF_Font * font; ///<Police pour l'affichage des textes normaux -> Taille = 24
		TTF_Font * fontTitre; ///<Police pour l'affichage des titres -> Taille = 48
		Mix_Chunk *son_victoire; ///<Son du jeu en cas de blackjack ou de 21 de la part du joueur (data/victoire.wav)
		Mix_Chunk *son_defaite; ///<son de défaite -> dépassement de 21 lors du jeu (data/faaah.wav)
		Mix_Chunk *son_chutePiece; ///<son pour l'affichage des résultats (data/chutePiece.wav)
		Mix_Chunk *son_placeBet; ///<son pour le menu, début de partie (data/placeBet.wav)
		Mix_Chunk *son_cartes; ///<son pour le bruitage de distribution des cartes (data/cartes.wav)
		bool son; ///<booléen gérant l'activation des sons ou non
		EtatJeu etat; ///< Etat actuel du jeu
		std::vector<SDL_Carte*>cartesCroupierSDL; ///< tableau contenant les cartes du croupier
		std::vector<std::vector<SDL_Carte*>> cartesJoueurSDL; ///< tableau contenant les cartes du joueur

		/** @brief fonction de vérification des mises 
		 * @param mise : tableau des mises pour chaque main
		 * @param nbMains : nombre de mains 
		*/
		bool verifMiseNull(int mise[], int nbMains);

		/** @brief procédure d'affichage du tete sur la fenêtre avec la postion et la couleur souhaitée 
		 * @param texte : le texte à afficher
		 * @param x : coordonnée x pour l'affichage
		 * @param y : coordonnée y pour l'affichage
		 * @param couleur : couleur du texte à afficher
		 * @param fontUtiliser : police à utiliser pour l'affichage 
		*/
		void afficherTexte(const char* texte, int x, int y, SDL_Color couleur, TTF_Font* fontUtiliser = nullptr);

		/** @brief procédure d'affichage du jeu en entier
		 * @param jeu : le jeu de BlackJack sur laquelle la partie est en cours
		 * @param nbMains : le nombre de mains choisies par le joueur
		 * @param mainCourante : l'indice de la main en cours de jeu et modification
		 * @param mises : tableau contenant les mises de chaque main 
		 * @param miseCourante : la mise de la main en cours de jeu et modification
		 * @param info : structure avec les différentes infos de jeu utiles
		 */
		void aff(JeuBlackJack &jeu, int nbMains, int mainCourante, int mises[3], int miseCourante,InfoJeu &info);

		/** @brief procédure d'affichage des cartes */
		void afficherCarte();

		/** @brief procédure de mise à jour des cartes à afficher (position modifiée, nouvelles cartes, ...) */
		void updateCarteFenetre(JeuBlackJack &jeu,float MAIN_OFFSET);

		/** @brief procédure de nettoyage de la fenêtre des cartes */
		void nettoyerCarteFenetre();

	public :
		/** @brief Constructeur de la classe ApplicationSDL */
		ApplicationSDL();

		/** @brief Destructeur de la classe ApplicationSDL */
		~ApplicationSDL();

		/** @brief Boucle principale de l'application SDL 
		 * @param jeu : le jeu de BlackJack sur laquelle la partie est en cours
		*/
		void boucleSDL(JeuBlackJack &jeu);
		
		
};

#endif