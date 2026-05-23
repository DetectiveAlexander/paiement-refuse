#include "Deck.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>

using namespace std;

Deck::~Deck(){
	nbDeck=0;
	}
Deck::Deck(){nbDeck=0;}

Deck::Deck(int n){
	nbDeck=n;
	for(int i=0;i<n;i++){
		for(int j=1;j<=13;j++){
				cartes.push_back(Carte(j,PIQUE));
				cartes.push_back(Carte(j,CARREAU));
				cartes.push_back(Carte(j,TREFLE));
				cartes.push_back(Carte(j,COEUR));
			}
		}
	}
	Carte Deck::piocher(){
		Carte carte_pioche=cartes.back();
		carte_pioche.setVisible(true);
		cartes.pop_back();
		return carte_pioche;
		}
	
	void Deck::melanger(){
		random_device rd;///< Empêche la répétition à chaque appel
		mt19937 g(rd()); ///Le Mersenne Twister est un générateur de nombres pseudo-aléatoires,réputé pour sa qualité
		shuffle(cartes.begin(),cartes.end(),g);
		}
	
	int Deck::getNbDeck()const{return nbDeck;}
	long unsigned int Deck::getNbCarte()const{return cartes.size();}
	
	void Deck::initDeck(int nbdeck){
		cartes.clear();
		nbDeck=nbdeck;
		for(int i=0;i<nbDeck;i++){
		for(int j=1;j<=13;j++){
				cartes.push_back(Carte(j,PIQUE));
				cartes.push_back(Carte(j,CARREAU));
				cartes.push_back(Carte(j,TREFLE));
				cartes.push_back(Carte(j,COEUR));
			}
		}
	}

	void Deck::testRegression(){
		Deck d;
		assert(d.cartes.size() == 0);
    	assert(d.getNbDeck() == 0);

		int n = 3;
    	Deck p(n);
    	assert(p.cartes.size() == (size_t)(n * 52));
    	assert(p.getNbDeck() == n);

		p.melanger();

		long unsigned int tailleAvant = p.cartes.size();
    	Carte c = p.piocher();
    	assert(p.getNbCarte() == tailleAvant - 1);
		p.initDeck(1);
		
		cout<<"Test regression Deck réussi"<<endl;
		}

