#include "ApplicationTXT.h"

ApplicationTXT::ApplicationTXT() {};
ApplicationTXT::~ApplicationTXT() {}

void ApplicationTXT::Boucle(JeuBlackJack& jeu)
{

//Initialisation des variables
int mises[3];
int mise,j,i,c,nbMains,indiceMain;
bool partie,peutJouer,peutJouer2;
bool rejouer = true;
char rejouerChar;

//initPartie et cartes 
while (rejouer) {
    nbMains = 0;
    std::cout<<"Combien de mains voulez-vous jouer ? (max 3) "<<std::endl;
    while ((!(std::cin>>nbMains)) || nbMains <= 0 || nbMains > 3) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout<<"ERREUR : Reessayez pour le nombre de mains (Maximum 3) " <<std::endl;
    } 
    mises[0]=mises[1]=mises[2]=0;
    for (i = 0; i< nbMains; i++) {
        std::cout<<"Mise pour la main " <<i+1<<" : "<<std::endl;
        while ((!(std::cin>>mise)) || mise <= 0 || mise+mises[0]+mises[1]+mises[2] > jeu.getJoueur().getArgent() || mise > ((jeu.getJoueur().getArgent()-(mises[0]+mises[1]+mises[2]))-((-i-1)+nbMains))) {
            std::cout<<"ERREUR : Reessayez pour la main " <<i+1<<" : "<<std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        mises[i]=mise;
    }
    jeu.initTour(nbMains, mises);  
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Valeur de la carte du croupier : "<<jeu.getCroupier().getCarte(0).afficheCarte()<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    partie = true;
        do {
            for (indiceMain = 0; indiceMain<jeu.getJoueur().getMainTaille();indiceMain++) {
                peutJouer = true;
                peutJouer2 = true;
                do {
                    std::cout<<"-----------------------------"<<std::endl;
                    std::cout<<"Main "<<indiceMain+1<<" : "<<jeu.getJoueur().getMainIndice(indiceMain).valeur()<<" points"<<std::endl;
                    std::cout<<"Cartes : "<<std::endl;
                    for (i=0;i<jeu.getJoueur().getMainIndice(indiceMain).getNbCarte();i++) {
                        std::cout<<jeu.getJoueur().getMainIndice(indiceMain).getCarteIndice(i).afficheCarte()<<std::endl;
                    }
                    if((jeu.getJoueur().getMainIndice(indiceMain).estBJ())||(jeu.getJoueur().getMainIndice(indiceMain).valeur()==21)){
                        peutJouer2=false;
                    }
                    else {
                        std::cout<<"-----------------------------"<<std::endl;
                        std::cout<<"choisissez une action : "<<std::endl;
                        std::cout<< "1 - Tirer / 2 - Rester / 3 - Doubler / 4 - Split "<<std::endl;
                        std::cout<<"-----------------------------"<<std::endl;
                        while ((!(std::cin>>c)) || c < 1 || c > 4) {
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cout<<"ERREUR : Veuillez choisir un chiffre " <<std::endl;
                        } 
                        switch (c)
                        {
                        case 1:
                            jeu.executeLaMain(indiceMain, 1);
                            break;
                        case 2:
                            jeu.executeLaMain(indiceMain,2);
                            peutJouer2 = false;
                            break;
                        case 3:
                            if (jeu.getJoueur().peutDouble(indiceMain)) {
                                jeu.executeLaMain(indiceMain,3);
                                std::cout<<"Main "<<indiceMain+1<<" : "<<jeu.getJoueur().getMainIndice(indiceMain).valeur()<<" points"<<std::endl;
                                std::cout<<"Cartes : "<<std::endl;
                                for (i=0;i<jeu.getJoueur().getMainIndice(indiceMain).getNbCarte();i++) {
                                    std::cout<<jeu.getJoueur().getMainIndice(indiceMain).getCarteIndice(i).afficheCarte()<<std::endl;
                                }
                                peutJouer2 = false;
                                break;}
                            else {
                                std::cout<<"-----------------------------"<<std::endl;
                                std::cout<<"VOUS NE POUVEZ PAS DOUBLER"<<std::endl;
                                std::cout<<"-----------------------------"<<std::endl;
                                break;
                            }
                        case 4:
                            if (jeu.getJoueur().peutSplit(indiceMain)) {
                                jeu.executeLaMain(indiceMain,4);
                                break; }
                            else {
                                std::cout<<"-----------------------------"<<std::endl;
                                std::cout<<"VOUS NE POUVEZ PAS SPLITTER"<<std::endl;
                                std::cout<<"-----------------------------"<<std::endl;
                                break;
                            }          
                        }
                    
                        if (((jeu.getJoueur().getMainIndice(indiceMain).valeur() > 21) && (peutJouer2 == true))) {
                            peutJouer = false; 
                            std::cout<<"-----------------------------"<<std::endl;
                            std::cout<<"VOUS AVEZ DEPASSE 21, VOTRE TOUR EST DONC TERMINÉ"<<std::endl;
                            std::cout<<"-----------------------------"<<std::endl;
                            std::cout<<"Main "<<indiceMain+1<<" : "<<jeu.getJoueur().getMainIndice(indiceMain).valeur()<<" points"<<std::endl;
                            std::cout<<"Cartes : "<<std::endl;
                            for (i=0;i<jeu.getJoueur().getMainIndice(indiceMain).getNbCarte();i++) {
                                std::cout<<jeu.getJoueur().getMainIndice(indiceMain).getCarteIndice(i).afficheCarte()<<std::endl;
                            }
                        }
                    }
                    if (peutJouer2 == false) {
                        std::cout<<"-----------------------------"<<std::endl;
                        std::cout<<"VOTRE TOUR EST TERMINÉ"<<std::endl;
                        std::cout<<"-----------------------------"<<std::endl;
                        peutJouer = false;
                    }
                
                } while (peutJouer);
            } 
            //Croupier joue
            std::cout<<"-----------------------------"<<std::endl;
                jeu.tourCroupier17();
                for (j =0; j<jeu.getCroupier().getNbCarteCroupier();j++) {
                    std::cout<<"Valeur des cartes du croupier : "<<jeu.getCroupier().getCarte(j).afficheCarte()<<std::endl;
                }
                std::cout<<"Valeur finale de la main du croupier : "<<jeu.getCroupier().getValeurMain()<<std::endl;
            //Résultat du tour
                for (i =0; i< jeu.getJoueur().getMainTaille();i++) {
                    if ((jeu.getJoueur().getMainIndice(i).estBJ()) && !(jeu.getCroupier().estBJCroupier())){
                        std::cout<<"-----------------------------"<<std::endl;
                        std::cout<<"€€€€€€€€€€€€ BLACKJACK €€€€€€€€€€€€ VOUS GAGNÉ LA MAIN "<<i+1<<" (vous trichez !?!?!?)"<<std::endl;
                        std::cout<<"-----------------------------"<<std::endl;
                        jeu.setArgentJoueur(jeu.getJoueur().getArgent()+ 3*jeu.getJoueur().getMainIndice(i).getMise());
                    }
                    else {
                        if ((jeu.getJoueur().getMainIndice(i).valeur() <= 21) && (jeu.getCroupier().getValeurMain() > 21 || jeu.getJoueur().getMainIndice(i).valeur() > jeu.getCroupier().getValeurMain())) {
                            std::cout<<"-----------------------------"<<std::endl;
                            std::cout<<"FELICITATIONS, VOUS AVEZ GAGNÉ LA MAIN "<<i+1<<" !"<<std::endl;
                            std::cout<< jeu.getJoueur().getMainIndice(i).valeur()<<" points contre "<<jeu.getCroupier().getValeurMain()<<" points pour le croupier."<<std::endl;
                            std::cout<<"-----------------------------"<<std::endl;
                            jeu.setArgentJoueur(jeu.getJoueur().getArgent()+ 2*jeu.getJoueur().getMainIndice(i).getMise());
                        }
                        else if ((!(jeu.getJoueur().getMainIndice(i).estBJ()) && (jeu.getCroupier().estBJCroupier())) || ((jeu.getJoueur().getMainIndice(i).valeur())<(jeu.getCroupier().getValeurMain()) && (jeu.getCroupier().getValeurMain() <= 21)) || (jeu.getJoueur().getMainIndice(i).valeur()>21)) {
                                std::cout<<"-----------------------------"<<std::endl;
                                std::cout<<"DÉSOLÉ, VOUS AVEZ PERDU LA MAIN "<<i+1<<" !"<<std::endl;
                                std::cout<< jeu.getJoueur().getMainIndice(i).valeur()<<" points contre "<<jeu.getCroupier().getValeurMain()<<" points pour le croupier."<<std::endl;
                                std::cout<<"-----------------------------"<<std::endl;
                                }
                            else {
                                std::cout<<"-----------------------------"<<std::endl;
                                std::cout<< jeu.getJoueur().getMainIndice(i).valeur()<<" points contre "<<jeu.getCroupier().getValeurMain()<<" points pour le croupier."<<std::endl;
                                std::cout<<"VOUS AVEZ ÉGALISÉ LA MAIN "<<i+1<<" !"<<std::endl;
                                std::cout<<"-----------------------------"<<std::endl;
                                jeu.setArgentJoueur(jeu.getJoueur().getArgent()+jeu.getJoueur().getMainIndice(i).getMise());
                                }  
                            }    
                }
            partie = false;
        } while (partie);
    std::cout<<jeu.getJoueur().getNom()<<" votre solde actuel est de "<<jeu.getJoueur().getArgent()<<" euros."<<std::endl;
    std::cout<<"Voulez-vous rejouer ? (y pour oui, n pour non) "<<std::endl;
    while ((!(std::cin>>rejouerChar)) || (rejouerChar != 'y' && rejouerChar != 'n')) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout<<"ERREUR : Syntaxe invalide " <<std::endl;
    } 
    if (rejouerChar == 'n') {
        rejouer = false;
        std::cout<<"Merci d'avoir enrichi le casino et Israel, à bientôt !"<<std::endl;
        }
    else 
        if ((rejouerChar =='y') && (jeu.getJoueur().getArgent()==0)){
            std::cout<<"Vous êtes à sec, ALLEZ FAIRE UN PRÊT OU CASSEZ-VOUS!!!"<<std::endl;
            rejouer=false;
        }
        else 
            if ((rejouerChar=='y')&&(jeu.getJoueur().getArgent()<3)){
                std::cout<<"On est pas les Pièces Jaunes ici, allez, va t'acheter des bonbons ou reviens quand t'auras 3 euros."<<std::endl;
                rejouer=false;
            }
    }
    
}