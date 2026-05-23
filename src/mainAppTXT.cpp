#include "ApplicationTXT.h"
#include <iostream>
const int ARGENT_DEPART = 5000;

int main(void) {
	ApplicationTXT app;
    std::cout<<"Choisissez votre nom : "<<std::endl;
    std::string nom;
    std::cin >> nom;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Bonjour "<<nom<<", vous avez "<<ARGENT_DEPART<<" euros."<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    JeuBlackJack jeu(nom,ARGENT_DEPART);
    app.Boucle(jeu);
	return 0;
}