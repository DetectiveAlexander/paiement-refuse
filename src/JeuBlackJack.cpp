#include "JeuBlackJack.h"
#include <iostream>
#include <cassert>
const int DECK_GLOBAL=2;
using namespace std;

JeuBlackJack::JeuBlackJack(){};
JeuBlackJack::~JeuBlackJack(){};
JeuBlackJack::JeuBlackJack(string s, int arg): joueur(s,arg),pioche(DECK_GLOBAL){}

const Deck& JeuBlackJack::getDeck() const {return pioche;}
const Joueur& JeuBlackJack::getJoueur() const {return joueur;}
const Croupier& JeuBlackJack::getCroupier() const {return croupier;}

void JeuBlackJack::initTour(int nbMains,int listeOfMise[3]) {
    croupier.initCroupier();
    joueur.viderTabMain(); 
    pioche.initDeck(DECK_GLOBAL);
    pioche.melanger();
    if (nbMains<=3){
        for(int i=0;i<nbMains;i++){
            joueur.ajouteMain(listeOfMise[i]);
            joueur.hit(i,pioche);
            joueur.hit(i,pioche);
        }
    }
    croupier.ajouteCarte(pioche.piocher());
    croupier.ajouteCarteCache(pioche.piocher());
}

void JeuBlackJack::setMainMiser(int indiceMain,int mise){
    joueur.setMiseMain(indiceMain,mise);}

void JeuBlackJack::executeLaMain(int indiceMain,int exe)///1:hit - 2:stay - 3:double - 4:split
{
switch(exe){
    case 1:
        joueur.hit(indiceMain,pioche);
        break;
    case 2:
        joueur.stay(indiceMain);
        break;
    case 3:
        joueur.doubler(indiceMain,pioche);
        break;
    case 4:
        joueur.split(indiceMain,pioche);
        break;
    }
}

void JeuBlackJack::tourCroupier17(){ croupier.hit17(pioche); }

void JeuBlackJack::setArgentJoueur(int argent){ joueur.setArgent(argent);}

void JeuBlackJack::hitCroupier(){
    croupier.ajouteCarte(pioche.piocher());
}

void JeuBlackJack::revelerCarteCroupier(){croupier.revelerCarte(1);}

void JeuBlackJack::testRegression(){
    JeuBlackJack j("toto",0);
    j.setArgentJoueur(12000);
    int mises3[] = {100, 200, 300};
    int mises2[] = {85, 35};
    cout<<"argent avant mises :"<<j.getJoueur().getArgent()<<endl;
    j.initTour(3,mises3);
    assert(j.getDeck().getNbDeck()==DECK_GLOBAL);
    j.setMainMiser(0,15000);
    cout<<j.getJoueur().getMainIndice(0).getMise()<<endl;
    j.executeLaMain(1,2);
    unsigned long int tailleAvant = j.getDeck().getNbCarte();
    j.executeLaMain(2,1);
    assert(j.getDeck().getNbCarte()==tailleAvant-1);
    assert(j.getJoueur().getMainIndice(1).getEstStay()==true);
    j.initTour(2,mises2);
    assert(j.getCroupier().getNbCarteCroupier()==j.getJoueur().getMainIndice(0).getNbCarte());
    cout<<"argent apres mises :"<<j.getJoueur().getArgent()<<endl;
    cout<<"main du croupier avant tour: "<<j.getCroupier().getValeurMain()<<endl;
    j.tourCroupier17();
    cout<<"main du croupier après: "<<j.getCroupier().getValeurMain()<<endl;

}