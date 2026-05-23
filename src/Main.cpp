#include "Main.h"
#include <iostream>
#include <cassert>

using namespace std;

Main::Main(){
	mise=0;
	estSplitAs=false;
	estDouble=false;
	estStay=false;
}

Main::Main(int m) {
	mise=m;
	estSplitAs=false;
	estDouble=false;
	estStay=false;
}

Main::~Main(){
	mise=0;
	estSplitAs=false;
	estDouble=false;
	estStay=false;
}

int Main::getMise()const {
	return mise;
}

void Main::setMise(int m){
	mise=m;
}

bool Main::getEstDouble() const {
	return estDouble;
}

void Main::setStay() {
	estStay=true;
}

void Main::setDouble(const Carte ca) {
	estDouble=true;
	mise=mise*2;
	ajouteCarte(ca);
	setStay();

}


bool Main::getEstSplitAs()const {
	return estSplitAs;
}

void Main::setSplitAs() {
	estSplitAs=true;
}

bool Main::getEstStay() const {
	return estStay;
}



void Main::ajouteCarte(Carte ca){  /*ajoute une carte a la main( vector*/
	ca.setVisible(true);
	cartes.push_back(ca);
}

int Main::valeur() const {
	int somme = 0;
	bool asa11 = false;
	int s=cartes.size();
	for (int i = 0; i < s;i++) {
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
	return somme;
}


bool Main::estBJ() const{
	if (valeur() == 21 && cartes.size() == 2) {
		return true;
	}
	else {
		return false;
	}
}

int Main::getNbCarte()const {
	return cartes.size();
	}

const Carte& Main::getCarteIndice(int indice)const{
	return cartes.at(indice);
}	

void Main::supprimerCarte (int indice) {
	cartes.erase(cartes.begin() + indice);
}
void Main::testRegression(){
	Main mVide;
	/*------*/
	cout<<"Début du test de régression de la main"<<endl;
	assert(mVide.getMise()==0);
	assert(mVide.getEstDouble() == false);
	assert(mVide.getEstStay()==false);
	assert(mVide.getEstSplitAs()==false);
	assert(mVide.cartes.size()==0);
	cout<<"initialisation d'une main par défaut : ok"<<endl;
	/*-------*/
	Main m(10);
	/*-----*/
	assert(m.getMise()==10);
	assert(m.cartes.size()==0);
	cout<<"initialisation d'une main avec une mise : ok"<<endl;
	/*------*/
	Carte ca(10,COEUR);
	Carte ca2(9,TREFLE);
	Carte ca3(1,PIQUE);
	m.setStay();
	m.setSplitAs();
	
	/*----------*/
	assert(m.getEstStay()==true);
	assert(m.getEstSplitAs()==true);
	cout<<"récupération des donnée de split et stay : ok"<<endl;
	/*----------*/
	m.ajouteCarte(ca);     /* ajout d'un 10 de coeur*/
	m.ajouteCarte(ca2);    /* ajout d'un 9 de trefle*/
	/*----ca------*/
	assert(m.cartes[0].getValeur() == 10);
	assert(m.cartes[0].getVisible() == true);
	/*-----ca2-----*/
	assert(m.cartes[1].getValeur() == 9);
	cout<<"ajout de 2 cartes à une main : ok"<<endl;
	/*---------*/
	assert(m.valeur()==19);
	cout<<"récupération de la valeur d'une main de 2 cartes hors As : ok"<<endl;
	/*--------*/
	m.setDouble(ca3);  /* ajout d'un As de pique*/
	/*------*/
	assert(m.cartes[2].getValeur() == 1);
	assert(m.cartes[2].getVisible() == true);	
	assert(m.getMise()==20);
	assert(m.getEstDouble()==true);
	assert(m.getEstStay()==true);
	assert(m.valeur() == 20);
	cout<<"la main a été doublé et l'As ajouté a pris la valeur 1 : ok"<<endl;
	/*-------------*/
	Main m2;              /* nouvelle mise */
	Carte ca4(2,COEUR);
	m2.ajouteCarte(ca);   /* ajout d'un 10 de coeur*/
	m2.ajouteCarte(ca2);  /* ajout d'un 9 de trefle*/
	m2.ajouteCarte(ca4);  /* ajout d'un 2 de coeur*/
	assert(m2.getNbCarte()==3);
	/*------*/
	assert(m2.estBJ()==false);
	cout<<"une main de plus de 2 cartes ne fait pas BlackJack : ok"<<endl;
	/*------*/
	Main m3;               /* nouvelle mise */
	m3.ajouteCarte(ca3);   /* ajout d'un As de pique*/
	m3.ajouteCarte(ca);    /* ajout d'un 10 de coeur*/
	/*--------*/
	assert(m3.valeur()==21);
	cout<<"l'As a prit la valeur 11 : ok"<<endl;
	assert(m3.estBJ()==true);
	cout<<"la main a fait BlackJack : ok"<<endl;
	/*-------*/
	Main m5;               /* nouvelle mise */
	m5.ajouteCarte(ca3);   /* ajout d'un As de pique*/
	m5.ajouteCarte(ca2);   /* ajout d'un 9 de trefle*/
	assert(m5.valeur()==20);
	m5.ajouteCarte(ca);    /* ajout d'un 10 de coeur*/
	/*------*/
	assert(m5.valeur()==20);
	cout<<"l'As avait la valeur 11 puis a changé en 1 : ok"<<endl;
	assert(m5.getNbCarte()==3);
	Carte car=m5.getCarteIndice(1);
	assert(car.getValeur()==9);
	assert(car.getCouleurInt()==TREFLE);
	m5.supprimerCarte(1);
	assert(m5.getCarteIndice(1).getValeur()==10);
	cout<<"test regression de Main : ok"<<endl;

	
}
	

	
	
	
	
