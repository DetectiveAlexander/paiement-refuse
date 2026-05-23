#include "SDL_Carte.h"
#include <cmath>

bool SDL_Carte::getEnMouvement() const {return m_enMouvement;}

SDL_Carte::~SDL_Carte(){}

SDL_Carte::SDL_Carte(int valeur, CouleurCarte couleur, SDL_Texture* image, float srcX, float srcY, float destX, float destY,bool faceCachee)
{
    //création des variable:
    m_vitesse=0.1f;
    m_enMouvement=true;
    m_textureCartes=image; 
    m_x=srcX; 
    m_y=srcY; 
    m_cibleX=destX;
    m_cibleY=destY; 
    m_faceCachee=faceCachee; 
    int carteL = 1009 / 14; 
    int carteH = 385 / 4;
    m_largeur=carteL;
    m_hauteur=carteH;

    //Calcul du rectangle de la FACE
    //On fait (couleur - 1) car enum commence à VIDE=0
    m_srcRect.x = (valeur - 1) * carteL; // As=1, (1-1)=0 (colonne 1)
    m_srcRect.y = (static_cast<int>(couleur) - 1) * carteH; 
    m_srcRect.w = carteL;
    m_srcRect.h = carteH;

    // Calcul du rectangle du DOS (Dernière colonne = index 13)
    m_dosRect.x = 13 * carteL; 
    m_dosRect.y = 0;
    m_dosRect.w = carteL;
    m_dosRect.h = carteH;
}

void SDL_Carte::update() {
    if (!m_enMouvement) return;
    
    // Formule du Lerp: Position = Position + (Cible - Position) * Vitesse
    m_x += (m_cibleX - m_x) * m_vitesse;
    m_y += (m_cibleY - m_y) * m_vitesse;

    // Si on est à moins d'un demi-pixel de la cible, on s'arrête
    if (std::abs(m_cibleX - m_x) < 0.5f && std::abs(m_cibleY - m_y) < 0.5f) {
        m_x = m_cibleX;
        m_y = m_cibleY;
        m_enMouvement = false;
    }
}

void SDL_Carte::renderCarte(SDL_Renderer* renderer) {
    SDL_Rect dstRect = { (int)m_x, (int)m_y, m_largeur, m_hauteur };

    SDL_Rect* rectAUtiliser;
    if(m_faceCachee){
        rectAUtiliser = &m_dosRect;}
    else{
        rectAUtiliser = &m_srcRect;}

    SDL_RenderCopy(renderer, m_textureCartes, rectAUtiliser, &dstRect);
}

void SDL_Carte::setNouvelleCible(float x, float y) {
    m_cibleX = x;
    m_cibleY = y;
    m_enMouvement = true;
}

void SDL_Carte::setCarteCachee(bool etat){m_faceCachee=etat;}