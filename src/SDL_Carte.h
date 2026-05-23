#ifndef SDL_CARTE_H_
#define SDL_CARTE_H_

#include "Carte.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
*@class SDL_Carte
*@brief class permettent d'afficher et d'animer les cartes sur la fenêtre
*/
class SDL_Carte {
private:
    SDL_Texture* m_textureCartes;///< Pointeur vers le l'image contenant les 52 cartes
    SDL_Rect m_srcRect;///< Rectangle de découpe dans l'image
    SDL_Rect m_dosRect; ///< stocke la position du dos dans la carte
    int m_largeur, m_hauteur;///< Taille d'affichage à l'écran

    float m_x, m_y;///< coordonneé source
    float m_cibleX, m_cibleY;///< coordonneé destination
    float m_vitesse;///<la vitesse de mouvement (en float pour la fluidité)
    bool m_enMouvement;///< bool vérifiant si carte est en mouvement
    bool m_faceCachee;///< Booléen stockant si la carte affiche le dos ou le recto

public:
    /**
    *@brief Constructeur avec des paramètres
    *@param valeur Entier de la valeur de la carte
    *@param couleur Couleur du symbole de la carte
    *@param image La texture de l'image de 52 cartes
    *@param srcX Coordonnée X du début de mouvement
    *@param srcY Coordonnée Y du début de mouvement
    *@param destX Coordonnée X du fin de mouvement
    *@param destY Coordonnée Y du fin de mouvement
    *@param faceCachee Le dos est affiché ou pas
    */
    SDL_Carte(int valeur, CouleurCarte couleur, SDL_Texture* image, float srcX, float srcY, float destX, float destY,bool faceCachee);
    
    /**
    *@brief Destructeur par défaut
    */
    ~SDL_Carte();
    
    /**
    *@brief Calcul la position suivante avec la formule de Lerp pour l'animation de mouvement
    */
    void update();

    /**
    *@brief Affichege de la carte sur la page
    *@param renderer Référence vers la fenêtre (renderer) */
    void renderCarte(SDL_Renderer* renderer);

    /**
    *@brief Accesseur pour connaitre si la carte est toujours en mouvement 
    *@return Booléen du mouvement*/
    bool getEnMouvement() const ;

    /**
    *@brief Modifie la destination pour un nouveau mouvement
    *@param x Coordonnée X de la nouvelle destination
    *@param y Coordonnée Y de la nouvelle destination
    */
    void setNouvelleCible(float x, float y);

    /**
    *@brief Modifie la visibilité de la carte
    *@param etat true: la carte affiche son dos / false: la carte affiche sa face */
    void setCarteCachee(bool etat);
};

#endif