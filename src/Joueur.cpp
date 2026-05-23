#include "Joueur.h"
#include <iostream>
#include <cassert>
using namespace std;

Joueur::Joueur(){
	argent=0;
	}

Joueur::Joueur(std::string s, int arg){
	nom=s;
	argent=arg;
	}

Joueur::~Joueur(){
	nom.clear();
	argent=0;
	}



void Joueur::ajouteMain(int m){
	if(m<=argent){
	Main ma(m);
	mains.push_back(ma);
	argent -= m;
	}
}

void Joueur::stay(int idMain){
	mains[idMain].setStay();
	}

const string& Joueur::getNom()const{
	return nom;
	}

const int& Joueur::getArgent() const{
	return argent;
	}

void Joueur::setArgent(int a){
	argent=a;
	}

bool Joueur::peutHit(int idMain) const{ 
	if((mains[idMain].getEstStay()) || (mains[idMain].valeur() >= 21) || (mains[idMain].getEstDouble())){
		return false; }
	return true;

}

void Joueur::hit(int idMain, Deck& d){
	Carte ca=d.piocher();
	mains[idMain].ajouteCarte(ca);
}

bool Joueur::peutDouble(int indiceMain) const{
	if ((mains[indiceMain].getMise()*2 <= argent) && (mains[indiceMain].getNbCarte()==2) && (mains[indiceMain].estBJ()==false) && (mains[indiceMain].getEstStay()==false))return true;
	return false;
}

bool Joueur::peutSplit(int indiceMain) const{
	if((mains[indiceMain].getNbCarte()==2) && 
((mains[indiceMain].getCarteIndice(0).getValeur()==mains[indiceMain].getCarteIndice(1).getValeur()) || (( mains[indiceMain].getCarteIndice(0).getValeur()>=10 ) && (mains[indiceMain].getCarteIndice(1).getValeur() >=10 )) ) && 
(mains[indiceMain].getEstSplitAs()==false) && (mains[indiceMain].getMise()<= argent) ){return true;}
	return false;
}

void Joueur::doubler(int indiceMain, Deck& d) {
		argent-=mains[indiceMain].getMise();
		mains[indiceMain].setDouble(d.piocher());
		
}

void Joueur::split(int indiceMain, Deck& d) {
	
	
	mains.insert(mains.begin() + indiceMain + 1, mains[indiceMain]);
	mains[indiceMain].supprimerCarte(0);
	mains[indiceMain + 1].supprimerCarte(1);
	mains[indiceMain].ajouteCarte(d.piocher());
	mains[indiceMain + 1].ajouteCarte(d.piocher());
	if (mains[indiceMain].getCarteIndice(0).getValeur()==1) {
		mains[indiceMain].setSplitAs();
		mains[indiceMain + 1].setSplitAs();
	}
	argent -= mains[indiceMain].getMise();

}

void Joueur::viderTabMain(){
	mains.clear();
}

void Joueur::setMiseMain(int indiceMain,int mise){
	mains[indiceMain].setMise(mise);
}

const Main& Joueur::getMainIndice(int indice)const {
	return mains[indice];
}

const int Joueur::getMainTaille()const {
	return (int)mains.size();
}

void Joueur::testRegression(){
	cout<<"Début du test regression de JOUEUR"<<endl;
	Joueur j;
	assert(j.getNom()=="");
	assert(j.getArgent()==0);
	assert(j.mains.size()==0);
	cout<<"Initialisation d'un joueur par défaut : ok"<<endl;
	
	string n = "Toto";
	Joueur j2(n,1856);
	assert(j2.getNom()=="Toto");
	assert(j2.getArgent()==1856);
	assert(j2.mains.size()==0);
	cout<<"Initialisation d'un joueur avec un nom et une somme d'argent : ok"<<endl;
	
	j2.setArgent(j2.getArgent()-10);
	assert(j2.getArgent()==1846);
	//*-------------*/
	
	Deck d(2);
	d.melanger();
	j2.ajouteMain(846);
	assert(j2.getArgent()==1000);
	j2.mains[0].ajouteCarte(d.piocher());
	j2.mains[0].ajouteCarte(d.piocher());
	/*----------------*/
	assert(j2.mains.size()==1);
	assert(j2.mains[0].getNbCarte()==2);
	cout<<"ajout d'une main au joueur : ok"<<endl;
	
	j2.hit(0,d);
	assert(j2.mains[0].getNbCarte()==3);
	cout<<"faire un hit : ok"<<endl;
	
	j2.stay(0);
	assert(j2.mains[0].getEstStay()==true);
	cout<<"stay : ok"<<endl;
	
	/*-------------------------------------------------------------------------*/
	Carte ca(10,COEUR);
	Carte ca2(9,TREFLE);
	Carte ca3(1,PIQUE);
	/*------------------------------test peutHit/peutDouble/peutSplit--------------------------------------------*/
	Joueur j3(n,600000);
	j3.ajouteMain(10);
	j3.mains[0].ajouteCarte(ca);
	j3.mains[0].ajouteCarte(ca3);       /*valeur de la main =21*/
	cout<<j3.mains[0].estBJ()<<endl;
	assert(j3.peutHit(0)==false);		/*test peuHit condition estBJ*/
	assert(j3.peutDouble(0)==false);	/*test peuDouble condition estBj*/
	assert(j3.peutSplit(0)==false);		/*test peuSplit condition 2cartes differentes*/
	j3.mains[0].supprimerCarte(1);     	/*------la main a 1 cartes------*/
	assert(j3.peutSplit(0)==false);		/*test peu split condition main de plus ou moins de 2 cartess*/
	assert(j3.peutDouble(0)==false);	/*test peuDouble condition main de plus ou moins de 2 cartes*/
	assert(j3.peutHit(0)==true);		/*test peuHit quand tout va bien*/
	j3.mains[0].ajouteCarte(ca2);   	/*------------la main a un 10 et un 9*/
	assert(j3.peutDouble(0)==true);		/*test peuDouble quand tout va bien*/
	j3.setArgent(0);
	assert(j3.peutDouble(0)==false);	/*test peuDouble condition pas d argent*/
	j3.mains[0].setStay();
	assert(j3.peutHit(0)==false);		/*test peuHit et peuDouble condition estStay*/
	assert(j3.peutDouble(0)==false);
	
	
	/*---------------------main de 2 as-----------------*/

	Joueur j4(n,15);
	j4.ajouteMain(10);
	j4.mains[0].ajouteCarte(ca3);
	j4.mains[0].ajouteCarte(ca3); 
	assert(j4.peutSplit(0)==false);
	j4.setArgent(14000);
	
	j4.split(0,d);
	assert(j4.peutSplit(0)==false);
	assert(j4.peutSplit(1)==false);
	assert(j4.mains[0].getCarteIndice(0).getValeur()==1);
	assert(j4.mains[1].getCarteIndice(0).getValeur()==1);
	assert(j4.mains[0].getNbCarte()==2 && j4.mains[1].getNbCarte()==2);

	/*------------------test doubler-------------------------------*/
	Joueur j5(n,1400);
	j5.ajouteMain(10);
	j5.mains[0].ajouteCarte(ca3);
	j5.mains[0].ajouteCarte(ca3); 
	j5.doubler(0,d);
	assert(j5.peutSplit(0)==false);
	assert(j5.peutHit(0)==false);
	j5.viderTabMain();
	assert(j5.mains.size()==0);
	}
	
	
	







	

	
	

