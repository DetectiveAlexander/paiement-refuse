#include "Carte.h"
#include <iostream>
#include <stdio.h>
#include <cassert>


Carte::Carte() {
	couleur = VIDE;
	valeur = 0;
	estVisible = false;
}

Carte::Carte(int v, CouleurCarte c) {
	couleur = c;
	valeur = v;
	estVisible = false;
}

Carte::~Carte() {
	valeur = 0;
	couleur = VIDE;
	estVisible = false;
}

const int& Carte::getValeur() const {
	return valeur;
}

const CouleurCarte& Carte::getCouleurInt() const {
	return couleur;
}

std::string Carte::getCouleurString() const {
    switch (couleur) {
        case 1: return "Trefle";
        case 2: return "Carreau";
        case 3: return "Coeur";
        case 4: return "Pique";
        default: return "Vide"; 
    }
}

const bool& Carte::getVisible() const {
	return estVisible;
}

void Carte::setVisible() {
	if (estVisible)
		estVisible = false;
	else
		estVisible = true;
}

void Carte::setVisible(bool state) {
	estVisible = state;
}

std::string Carte::afficheCarte()const{
	int v=getValeur();
	if ((v<=10)&&(v>1)){
		std::string car=std::to_string(v)+" de "+getCouleurString();
		return car;
	}
	
		switch(v){
			case 1: return "As de "+getCouleurString();
			case 11: return "Valet de "+getCouleurString();
			case 12: return "Dame de "+getCouleurString();
			case 13: return "Roi de "+getCouleurString();
			default: return "Carte innexistante";
		}
	
	

}


void Carte::testRegression() {
	Carte cVide;
	assert(cVide.getValeur() == 0);

	assert(cVide.getVisible() == 0);
	cVide.setVisible(true);
	assert(cVide.getVisible() == 1);
	Carte c(10, COEUR);
	assert(c.getValeur() == 10);
	assert(c.getCouleurInt() == 3);
	assert(c.getCouleurString() == "Coeur");
	assert(c.getVisible() == 0);
	std::cout<<c.afficheCarte()<<std::endl;
	Carte c2(12, PIQUE);
	std::cout<<c2.afficheCarte()<<std::endl;
}


