#include "Croupier.h"
#include <iostream>
#include <cassert>
using namespace std; 

Croupier::Croupier(){}
Croupier::~Croupier(){}

void Croupier::initCroupier(){
    cartes.clear();
}

void Croupier::ajouteCarte(Carte ca){  /*ajoute une carte a la main vector*/
	ca.setVisible(true);
	cartes.push_back(ca);
}

void Croupier::ajouteCarteCache(Carte ca){  /*ajoute une carte a la main( vector*/
	ca.setVisible(false);
	cartes.push_back(ca);
}

void Croupier::revelerCarte(int indice){
	cartes[indice].setVisible(true);
	}

const Carte& Croupier::getCarte(int indice) const {
    return cartes[indice];
}

int Croupier::getValeurMain()const{
	int somme = 0;
	bool asa11 = false;
	int s=cartes.size();
	for (int i = 0; i < s;i++) {
		if(cartes[i].getVisible()){
			if (cartes[i].getValeur() == 1) {
				if (somme > 10) {
					somme = somme + 1;
				}
				else {
					somme = somme + 11;
					asa11 = true;
				}
			}
			else {
				if (cartes[i].getValeur() > 10) {
					somme = somme + 10;
				}
				else {
					somme = somme + cartes[i].getValeur();
				}
				if ((somme > 21) && (asa11 == true)) {
					somme = somme - 10;
					asa11 = false;
				}
			}
		}
	}
	return somme;
}

void Croupier::hit17(Deck& d){
	cartes[1].setVisible(true);
    while(getValeurMain() < 17){
        ajouteCarte(d.piocher());
    }
}

int Croupier::getNbCarteCroupier() const {return cartes.size();}

bool Croupier::estBJCroupier() const{
	if (cartes.size() == 2 && getValeurMain() == 21) {
		return true;
	}
	else {
		return false;
	}
}

void Croupier::testRegression() {
    Croupier c;
    assert(c.getValeurMain() == 0);


    Carte carte1(10, COEUR); 
    c.ajouteCarte(carte1);
    assert(c.getValeurMain() == 10);
    assert(c.getCarte(0).getValeur() == 10);

    Carte carte2(1, PIQUE); // Un As (1)
    c.ajouteCarteCache(carte2);

    c.revelerCarte(1);
    assert(c.getCarte(1).getVisible() == true);
    assert(c.getCarte(1).getValeur() == 1);
	assert(c.estBJCroupier()==true);

    assert(c.getValeurMain() == 21);
    Croupier c2;
    Deck d(2);
    Carte ca(4,PIQUE);
    Carte ca2(5,PIQUE);
    c2.ajouteCarte(ca);
    c2.ajouteCarte(ca2);
    assert(c2.getValeurMain()==9);
    c2.hit17(d);
    assert(c2.getValeurMain()==19);
	cout << "Test de régression du Croupier réussi" << endl;

    
}
