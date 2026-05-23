#include "ApplicationSDL.h"
#include <iostream>
#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

const int WDIMX = 1200;
const int WDIMY = 900;

const float CARTE_W      = 1009.f / 14.f;  
const float CARTE_H      = 385.f  /  4.f;  
const float ESPACEMENT   = CARTE_W - 30.f;
const float PIOCHE_X      = WDIMX- CARTE_W - 300.f;
const float PIOCHE_Y      = 70.f;
const float MAIN_JOUEUR_Y   = WDIMY - CARTE_H - 140.f;
const float MAIN_CROUPIER_Y = 70.f;
const float MAIN_X_BASE  = 60.f;///< X de la premier main

const SDL_Rect srcFleche = {0,0,360,350};
const SDL_Color blanc ={255, 255, 255, 255};
const SDL_Color jaune={255, 255, 0, 255};
const SDL_Color rouge={255,0,0,255};

ApplicationSDL::ApplicationSDL()
{
    etat = MENU;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "Le mixeur SDL n'a pas pu s'initialiser : " << Mix_GetError() << endl;
        cout << "Pas de son pour cette partie" << endl;
        son = false;
    }
    else
        son = true;
    
    if (son) {
        son_victoire = Mix_LoadWAV("data/victoire.wav");
        if (!son_victoire) {
            cout << "Erreur lors du chargement du son de victoire : " << Mix_GetError() << endl;
            cout << "Pas de son de victoire pour cette partie" << endl;
            son = false;
        }
        son_defaite = Mix_LoadWAV("data/faaah.wav");
        if (!son_defaite) {
            cout << "Erreur lors du chargement du son de defaite : " << Mix_GetError() << endl;
            cout << "Pas de son de defaite pour cette partie" << endl;
            son = false;
        }
        son_chutePiece= Mix_LoadWAV("data/chutePiece.wav");
        if (!son_chutePiece) {
            cout << "Erreur lors du chargement du son de chute de piece : " << Mix_GetError() << endl;
            cout << "Pas de son de chute de piece pour cette partie" << endl;
            son = false;
        }
        son_placeBet = Mix_LoadWAV("data/placeBet.wav");
        if (!son_placeBet) {
            cout << "Erreur lors du chargement du son de placement de bet : " << Mix_GetError() << endl;
            cout << "Pas de son de placeBet pour cette partie" << endl;
            son = false;
        }
        son_cartes = Mix_LoadWAV("data/cartes.wav");
        if (!son_cartes) {
            cout << "Erreur lors du chargement du son de cartes : " << Mix_GetError() << endl;
            cout << "Pas de son de cartes pour cette partie" << endl;
            son = false;
        }
    }

    window = SDL_CreateWindow("BlackJack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WDIMX, WDIMY, SDL_WINDOW_SHOWN );
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    font = TTF_OpenFont("data/arial.ttf", 24);
    if (font == nullptr) {
        cout << "Police arial.ttf non trouvee" << endl;
        font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
        if (font == nullptr) {
            font = TTF_OpenFont("/System/Library/Fonts/Arial.ttf", 24); 
            if (font == nullptr) {
                cout << "Erreur : Aucune police trouvee." << endl;
                SDL_Quit();
                exit(1);
            }
        }
    }
    fontTitre = TTF_OpenFont("data/arial.ttf", 48);
    if (fontTitre == nullptr) {
        cout << "Police arial.ttf non trouvee" << endl;
        fontTitre = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 48);
        if (fontTitre == nullptr) {
            fontTitre = TTF_OpenFont("/System/Library/Fonts/Arial.ttf", 48); 
            if (fontTitre == nullptr) {
                cout << "Erreur : Aucune police trouvee." << endl;
                SDL_Quit();
                exit(1);
            }
        }
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init : " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    else
    {
        textureCartes = IMG_LoadTexture(renderer, "data/52_Cartes.png");
        textureFleche = IMG_LoadTexture(renderer, "data/fleche.png");
    }
    fondTexture = IMG_LoadTexture(renderer, "data/bj_fond.png");
    if (!fondTexture) {
    cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
}

ApplicationSDL::~ApplicationSDL()
{
    if ((textureCartes)){
        SDL_DestroyTexture(textureCartes);
    }
    if (textureFleche){
        SDL_DestroyTexture(textureFleche);
    }
    if (fondTexture) {
        SDL_DestroyTexture(fondTexture);
    }
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    if (son_victoire)
        Mix_FreeChunk(son_victoire);
    if (son_defaite)
        Mix_FreeChunk(son_defaite);
    if (son_chutePiece)
        Mix_FreeChunk(son_chutePiece);
    if (son_placeBet)
        Mix_FreeChunk(son_placeBet);
    if (son_cartes)
        Mix_FreeChunk(son_cartes);  
    if (font != nullptr)
        TTF_CloseFont(font);


    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool ApplicationSDL::verifMiseNull(int mise[], int nbMains){
    int total =1;
    for (int i =0; i<nbMains; i++){
        total*=mise[i];
    }
    if (total==0){
        return false;
    }
    else 
        return true;
}

void ApplicationSDL::afficherTexte(const char* texte, int x, int y, SDL_Color couleur, TTF_Font* fontUtiliser) {
    if (fontUtiliser == nullptr) return;
    
    // Création de la surface 
    SDL_Surface* surfaceTexte = TTF_RenderText_Blended(fontUtiliser, texte, couleur);
    if (surfaceTexte == nullptr) {
        cout << "Erreur creation surface texte : " << TTF_GetError() << endl;
        return;
    }
    
    // Convertir en texture
    SDL_Texture* textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
    if (textureTexte == nullptr) {
        cout << "Erreur creation texture texte : " << SDL_GetError() << endl;
        SDL_FreeSurface(surfaceTexte);
        return;
    }
    SDL_Rect rectTexte = {x, y, surfaceTexte->w, surfaceTexte->h};
    
    SDL_RenderCopy(renderer, textureTexte, nullptr, &rectTexte);
    
    SDL_DestroyTexture(textureTexte);
    SDL_FreeSurface(surfaceTexte);
}

void ApplicationSDL ::aff(JeuBlackJack &jeu, int nbMains, int mainCourante, int mises[3], int miseCourante,struct InfoJeu &info) {
    if (etat == MENU) {
        string argentText="Argent : " + to_string(jeu.getJoueur().getArgent());
        afficherTexte(argentText.c_str(), WDIMX / 2 - 65, 150, blanc, font);
        afficherTexte("BlackJack", WDIMX / 2 - 100, 100, blanc, fontTitre);
        if (info.misesChoisies) {
            afficherTexte("Nombre de mains :  " , 50, WDIMY / 2 - 50, blanc, fontTitre);
            char buffer[10];
            snprintf(buffer, sizeof(buffer), "%d", nbMains);
            string nb_mains = buffer;
            afficherTexte(nb_mains.c_str(), 225, WDIMY / 2 + 50, blanc, fontTitre);
        }
        else {
            afficherTexte("Nombre de mains :  " , 50, WDIMY / 2 - 50, jaune, fontTitre);
            char buffer[10];
            snprintf(buffer, sizeof(buffer), "%d", nbMains);
            string nb_mains = buffer;
            afficherTexte(nb_mains.c_str(), 225, WDIMY / 2 + 50, jaune, fontTitre);
            if(info.impossible2){
                afficherTexte("vous n'avez pas assez d'argent pour une main supplementaire",WDIMX / 2 - 325, WDIMY-100, rouge, font);
            }
            afficherTexte("Appuyez sur la touche entree pour choisir la valeur des mises", WDIMX / 2 - 325, WDIMY-50, blanc, font);
            
        }
        if (info.misesChoisies) {
            SDL_Rect dstFL ;
            for (int i = 0; i < nbMains; i++) {
            string miseText = "Mise Main " + to_string(i + 1) + " : " + to_string(mises[i]) + " euros";
            afficherTexte(miseText.c_str(), WDIMX / 2 + 200, WDIMY - 540 + i * 70, blanc, font);
            afficherTexte("Appuyez sur la touche entree pour commencer", WDIMX / 2 - 250, WDIMY-50, blanc, font);
            }
            afficherTexte("ALL IN (E)", WDIMX/2,WDIMY/2,blanc,font);
            if(info.fleche){
                if(info.miseOblig){
                    SDL_SetTextureColorMod(textureFleche, 255, 0, 0);
                    }
                else {
                    SDL_SetTextureColorMod(textureFleche,255,255,255);
                }
                dstFL.x = WDIMX / 2 + 500;
                dstFL.y = WDIMY - 555 + miseCourante * 70;
                dstFL.h = 60;
                dstFL.w = 60;
                SDL_RenderCopy(renderer, textureFleche, &srcFleche, &dstFL);
            }
        }
        else {
            for (int i = 0; i < nbMains; i++) {
            string miseText = "Mise Main " + to_string(i + 1) + " : " + to_string(mises[i]) + " euros";
            afficherTexte(miseText.c_str(), WDIMX / 2 + 200, WDIMY - 540 + i * 70, blanc, font);
            }
        }
        
    }
    else if (etat == ANIMATION) {
        string argentText="Argent : " + to_string(jeu.getJoueur().getArgent());
        afficherTexte(argentText.c_str(), WDIMX- 200, 50, blanc, font);
        afficherCarte();
        string ptCroupier = "Le croupier a " + to_string(jeu.getCroupier().getValeurMain()) + " points";
        afficherTexte(ptCroupier.c_str(), WDIMX / 2 - 130, WDIMY / 2 - 30, blanc, font);

    }
    else if (etat == FINPARTIE) {
        string argentText="Argent : " + to_string(jeu.getJoueur().getArgent());
        afficherTexte(argentText.c_str(), WDIMX- 200, 50, blanc, font);
        afficherTexte("FIN DE PARTIE", WDIMX / 2.25, WDIMY/8 , blanc, fontTitre); 
        int espace=WDIMY/4.5;
        for (int i =0; i< jeu.getJoueur().getMainTaille();i++) {
            string resultat = "Resultat de la main "+ to_string(i+1)+" :";
            afficherTexte(resultat.c_str(), WDIMX/10, espace, blanc, font);
            
            if ((jeu.getJoueur().getMainIndice(i).estBJ()) && !(jeu.getCroupier().estBJCroupier())){
                afficherTexte("!!!!!!! BLACKJACK !!!!!!!",WDIMX/10+350 , espace, {255,255,0,255}, fontTitre);
            }
            else {
                if ((jeu.getJoueur().getMainIndice(i).valeur() <= 21) && (jeu.getCroupier().getValeurMain() > 21 || jeu.getJoueur().getMainIndice(i).valeur() > jeu.getCroupier().getValeurMain())) {
                    afficherTexte("Vous battez le croupier, felicitation!",WDIMX/10+350 , espace, {51,255,51,255}, font);
                }
                else if ((!(jeu.getJoueur().getMainIndice(i).estBJ()) && (jeu.getCroupier().estBJCroupier())) || ((jeu.getJoueur().getMainIndice(i).valeur())<(jeu.getCroupier().getValeurMain()) && (jeu.getCroupier().getValeurMain() <= 21)) || (jeu.getJoueur().getMainIndice(i).valeur()>21)) {
                        afficherTexte("Vous avez perdu, dommage",WDIMX/10+350 , espace, blanc, font);
                        }
                    else {
                        afficherTexte("Vous egalisez le coupier",WDIMX/10+350 , espace, {0,255,255,255}, font);
                        }  
                }
            espace+=70;        
            }
        string solde="Il vous reste "+to_string(jeu.getJoueur().getArgent())+" euros";
        afficherTexte(solde.c_str(), WDIMX / 2.4, WDIMY/1.25, blanc, font);
        afficherTexte("Souhaitez-vous continuer de jouer? Oui (Y) | Non (N)", WDIMX / 3.4, WDIMY/1.2, blanc, font);
        if (info.impossible){
            afficherTexte("Vous etes a sec vous ne pouvez plus continuer",WDIMX/3,WDIMY/2, jaune, font);
        }
    }
    else if (etat == JOUEUR) {
        // Tour du joueur
        afficherCarte();
        // Texte au milieu de l'écran pour indiquer le tour du joueur et les actions possibles
        if (mainCourante < jeu.getJoueur().getMainTaille()) {
            string mainText = "Tour de la Main " + to_string(mainCourante + 1);
            afficherTexte(mainText.c_str(), WDIMX/2-95, WDIMY/2-30, blanc, font);
            //afficher juste en dessous du tour
            if(!(jeu.getJoueur().peutDouble(mainCourante))){
                afficherTexte("Tirer (A) | Rester (Z) ",WDIMX/2-110, WDIMY/2, blanc, font);
                }
            else if (!jeu.getJoueur().peutSplit(mainCourante) && (jeu.getJoueur().peutDouble(mainCourante))){
                afficherTexte("Tirer (A) | Rester (Z) | Doubler (E) ",420, WDIMY/2, blanc, font);
                }
                else
                    afficherTexte("Tirer (A) | Rester (Z) | Doubler (E) | Split (R)",380, WDIMY/2, blanc, font);
        }
        SDL_Color couleurInfo;
        //les valeurs de chacunes des mains à afficher en dessous des cartes
        for (int i = 0; i < jeu.getJoueur().getMainTaille(); i++) {
            if(i==mainCourante)couleurInfo=jaune;
            else couleurInfo=blanc;
            string pointsText = "Main " + to_string(i + 1) + " : " + to_string(jeu.getJoueur().getMainIndice(i).valeur()) + " points";
            string miseText= "Mise : " + to_string(jeu.getJoueur().getMainIndice(i).getMise());
            afficherTexte(pointsText.c_str(), MAIN_X_BASE + i * info.MAIN_OFFSET - 10, MAIN_JOUEUR_Y + CARTE_H +5, couleurInfo, font);
            afficherTexte(miseText.c_str(), MAIN_X_BASE + i * info.MAIN_OFFSET - 10, MAIN_JOUEUR_Y + CARTE_H +35, couleurInfo, font);
    }
        //affichage de l'argent
        string argentText="Argent : " + to_string(jeu.getJoueur().getArgent());
        afficherTexte(argentText.c_str(), WDIMX- 200, 50, blanc, font);
        //points du croupier à afficher sous ses cartes
        string pointsCroupier = "Croupier : " + to_string(jeu.getCroupier().getValeurMain()) + " points";
        afficherTexte(pointsCroupier.c_str(), MAIN_X_BASE-10, MAIN_CROUPIER_Y+CARTE_H+5, blanc, font);
    }
}

void ApplicationSDL ::boucleSDL(JeuBlackJack &jeu)
{
    //----l'ordre est Input -> Update -> Render-----------

    //---- Initialisation des variables------
    struct InfoJeu info;
    info.fleche =false;
    info.impossible=false;
    info.impossible2 = false;
    info.miseOblig=false;
    info.misesChoisies = false; // Indique si le joueur a terminé de choisir ses mises

    bool termine = false;
    etat = MENU;
    int nbMains = 1;
    SDL_Event evenements;
    cout << nbMains << endl;
    int mainCourante = 0; // Indice de la main en cours de jeu
    bool joueurPeutJouer = false;
    Uint32 dernierTempsAction = 0;
    const int DELAI_CARTE = 400; ///400 ms
    int miseCourante = 0;
    int mises[3]={0,0,0};
    //-----------------------

    while (!termine)
    {
        while (SDL_PollEvent(&evenements)) {
            if (evenements.type == SDL_QUIT) {
                termine = true;
            }
            if (etat == MENU) {
                if (son && son_placeBet) {
                    Mix_VolumeChunk(son_placeBet, 45);
                    Mix_PlayChannel(-1, son_placeBet, 0);
                    son_placeBet = nullptr; 
                }
                if (evenements.type == SDL_KEYDOWN){
                    if (evenements.key.keysym.scancode == SDL_SCANCODE_RETURN && info.misesChoisies && !verifMiseNull(mises, nbMains)) {
                        info.miseOblig=true;
                        for (int i=0; i<nbMains; i++){
                            if (mises[i]==0){
                                miseCourante=i;
                                break;
                            }
                        }
                    }
                    else if (evenements.key.keysym.scancode == SDL_SCANCODE_RETURN && info.misesChoisies){
                        info.fleche =false;
                        etat = JOUEUR;
                        info.misesChoisies =false;
                        info.impossible2 = false;
                        info.MAIN_OFFSET  = WDIMX/2-150;
                        jeu.initTour(nbMains, mises);
                        nettoyerCarteFenetre();
                        updateCarteFenetre(jeu,info.MAIN_OFFSET);
                        mainCourante = 0;
                        joueurPeutJouer = true;
                        cout << "Debut du tour pour la main " << mainCourante+1 << endl;
                    }
                    else if (evenements.key.keysym.scancode == SDL_SCANCODE_RETURN && !(info.misesChoisies)) {
                        info.misesChoisies = true;
                        info.fleche = true;
                    }
                    else if (!info.misesChoisies) {
                        switch (evenements.key.keysym.scancode) {
                            case SDL_SCANCODE_UP:
                                    if (((nbMains == 1) && (jeu.getJoueur().getArgent()<100)) || ((nbMains == 2) && (jeu.getJoueur().getArgent()<150))) {
                                        info.impossible2=true;
                                    }
                                    else if (nbMains<3){
                                        nbMains++;
                                        cout << "Nombre de mains : " << nbMains << endl;
                                    }
                                    break;
                                case SDL_SCANCODE_DOWN:
                                    if (nbMains > 1) {
                                        nbMains--;
                                        cout << "Nombre de mains : " << nbMains << endl;
                                    }
                                    break;
                                default:
                                    break;
                            }
                    }
                    else if (info.misesChoisies) {
                        switch (evenements.key.keysym.scancode) {
                            case SDL_SCANCODE_RIGHT:
                                info.miseOblig=false;
                                if (miseCourante < nbMains && ((mises[miseCourante] < jeu.getJoueur().getArgent()) && (mises[0]+mises[1]+mises[2] < jeu.getJoueur().getArgent()))) {
                                    mises[miseCourante] += 50;
                                    cout << "Mise pour la main " << miseCourante + 1 << " : " << mises[miseCourante] << endl;
                                }
                                else if (miseCourante < nbMains && (mises[0]+mises[1]+mises[2] == jeu.getJoueur().getArgent())) {
                                    mises[miseCourante] = 0;
                                    cout << "Mise pour la main " << miseCourante + 1 << " : " << mises[miseCourante] << endl;
                                }                               
                                break;
                            case SDL_SCANCODE_LEFT:
                                info.miseOblig=false;
                                if (miseCourante < nbMains && mises[miseCourante] > 50 ){
                                    mises[miseCourante] -= 50;
                                    cout << "Mise pour la main " << miseCourante + 1 << " : " << mises[miseCourante] << endl;
                                }
                                else if (miseCourante < nbMains && mises[miseCourante] <= 50) {
                                    mises[miseCourante] = jeu.getJoueur().getArgent()-(mises[0]+mises[1]+mises[2]-mises[miseCourante]);
                                }
                                break;
                            case SDL_SCANCODE_DOWN:
                                info.miseOblig=false;
                                if (miseCourante < nbMains - 1) {
                                    miseCourante++;
                                    cout << "Mise pour la main " << miseCourante + 1 << " : " << mises[miseCourante] << endl;
                                }
                                break;
                            case SDL_SCANCODE_UP:
                                info.miseOblig=false;
                                if (miseCourante > 0) {
                                    miseCourante--;
                                    cout << "Mise pour la main " << miseCourante + 1 << " : " << mises[miseCourante] << endl;
                                }
                                break;
                            case SDL_SCANCODE_E:
                                for(int i =0;i<nbMains;i++){
                                    mises[i]=(jeu.getJoueur().getArgent()/nbMains)-(jeu.getJoueur().getArgent()/nbMains)%50;
                                    if(jeu.getJoueur().getArgent()%nbMains != 0) {
                                        mises[0]=mises[1]+50;
                                    }
                                }
                            default:
                                break;
                        }
                    }
                }
            }
            else if (etat == JOUEUR) {
                //verifie si le joueur a 21
                if (son && son_cartes) {
                    Mix_VolumeChunk(son_cartes, 45);
                    Mix_PlayChannel(-1, son_cartes, 0);
                    son_cartes = nullptr;}
                if (joueurPeutJouer && evenements.type == SDL_KEYDOWN){
                    switch (evenements.key.keysym.scancode) {
                        case SDL_SCANCODE_Q:
                            cout << "Tirer une carte pour la main " << mainCourante+1 << endl;
                            jeu.executeLaMain(mainCourante, 1); 
                            cout << "Main " << mainCourante+1 << " : " << jeu.getJoueur().getMainIndice(mainCourante).valeur() << " points" << endl;
                            updateCarteFenetre(jeu,info.MAIN_OFFSET);
                            // Vérifier si la main dépasse 21
                            if (jeu.getJoueur().getMainIndice(mainCourante).valeur() > 21) {
                                cout << "Main " << mainCourante+1 << " : DEPASSE 21 !" << endl;
                                mainCourante++;
                                if (son && son_defaite) {
                                    Mix_VolumeChunk(son_defaite, 45);
                                    Mix_PlayChannel(-1, son_defaite, 0);
                                }
                            }
                            break;
                        case SDL_SCANCODE_W:
                            cout << "Stand pour la main " << mainCourante+1 << endl;
                            mainCourante++;
                            break;
                        case SDL_SCANCODE_E:
                            if(jeu.getJoueur().peutDouble(mainCourante)){
                                jeu.executeLaMain(mainCourante,3);
                                updateCarteFenetre(jeu,info.MAIN_OFFSET);
                                cout<<"vous venez de doubler la main "<<mainCourante+1<<endl;
                                mainCourante++;
                            }
                            else{
                                cout<<"vous ne pouvez pas doubler!!!"<<endl;
                            }
                            break;
                        case SDL_SCANCODE_R:
                            if (jeu.getJoueur().peutSplit(mainCourante)) {
                                jeu.executeLaMain(mainCourante,4);
                                nettoyerCarteFenetre();
                                info.MAIN_OFFSET=WDIMX/jeu.getJoueur().getMainTaille();
                                updateCarteFenetre(jeu,info.MAIN_OFFSET);
                                cout<<"vous venez de splitter la main "<<mainCourante+1<<endl;
                            }
                            else {
                                cout<<"-----------------------------"<<endl;
                                cout<<"VOUS NE POUVEZ PAS SPLITTER"<<endl;
                                cout<<"-----------------------------"<<endl;
                            }   
                            break;
                        default:
                            break;
                    }
                }
            }
            else if (etat == FINPARTIE) {
                if (evenements.type == SDL_KEYDOWN){
                    switch (evenements.key.keysym.scancode) {
                            case SDL_SCANCODE_Y:
                                if (jeu.getJoueur().getArgent()<50){
                                    info.impossible = true;
                                }
                                else {
                                    son_cartes = Mix_LoadWAV("data/cartes.wav");
                                    son_chutePiece = Mix_LoadWAV("data/chutePiece.wav");
                                    son_defaite = Mix_LoadWAV("data/faaah.wav");
                                    son_victoire = Mix_LoadWAV("data/victoire.wav");
                                    son_placeBet = Mix_LoadWAV("data/placeBet.wav");
                                    etat=MENU;
                                    for (int i=0; i<3; i++){
                                        mises[i]=0;
                                    }
                                    mainCourante=0;
                                    nbMains=1;
                                    miseCourante=0;
                                    }
                                break;
                            case SDL_SCANCODE_N:
                                termine=true;
                                break;
                            default:
                                break;
                    }
                }
            
            }
        
        }
    if(etat==JOUEUR){
        if (mainCourante >= jeu.getJoueur().getMainTaille()) {
            cout << "Toutes les mains ont joué. Tour du croupier:" << endl;
            joueurPeutJouer = false;
        }
        else if (jeu.getJoueur().getMainIndice(mainCourante).valeur() == 21) {
                    mainCourante++;
                    if (son && son_victoire) {
                        Mix_VolumeChunk(son_victoire, 45);
                        Mix_PlayChannel(-1, son_victoire, 0);
                    }
        }
        if (!(joueurPeutJouer)) {
            etat = ANIMATION;
            dernierTempsAction=SDL_GetTicks();
        }
    }
    if(etat==ANIMATION){
        Uint32 tempsActuel = SDL_GetTicks();
        if(!(jeu.getCroupier().getCarte(1).getVisible())){
            jeu.revelerCarteCroupier();
            updateCarteFenetre(jeu,info.MAIN_OFFSET);
        }
        if(jeu.getCroupier().getValeurMain()<17){
            if(tempsActuel-dernierTempsAction>DELAI_CARTE){ 
                jeu.hitCroupier();
                updateCarteFenetre(jeu,info.MAIN_OFFSET);
                dernierTempsAction=tempsActuel;
            }
        }
        else
        {
            bool pasDeMouvement =true;
            for (auto* c: cartesCroupierSDL){
                if(c->getEnMouvement())pasDeMouvement=false;
            }
            if(pasDeMouvement&&(tempsActuel - dernierTempsAction > 2500))
            {
                for (int j =0; j<jeu.getCroupier().getNbCarteCroupier();j++) {
                    cout<<"Valeur des cartes du croupier : "<<jeu.getCroupier().getCarte(j).afficheCarte()<<endl;
                }
                etat=FINPARTIE;
                for (int i =0; i< jeu.getJoueur().getMainTaille();i++) {
                    if ((jeu.getJoueur().getMainIndice(i).estBJ()) && !(jeu.getCroupier().estBJCroupier())){
                        jeu.setArgentJoueur(jeu.getJoueur().getArgent()+ 3*jeu.getJoueur().getMainIndice(i).getMise());
                    }
                    else {
                        if ((jeu.getJoueur().getMainIndice(i).valeur() <= 21) && (jeu.getCroupier().getValeurMain() > 21 || jeu.getJoueur().getMainIndice(i).valeur() > jeu.getCroupier().getValeurMain())) {
                            jeu.setArgentJoueur(jeu.getJoueur().getArgent()+ 2*jeu.getJoueur().getMainIndice(i).getMise());
                        }
                        else if (!((!(jeu.getJoueur().getMainIndice(i).estBJ()) && (jeu.getCroupier().estBJCroupier())) || ((jeu.getJoueur().getMainIndice(i).valeur())<(jeu.getCroupier().getValeurMain()) && (jeu.getCroupier().getValeurMain() <= 21)) || (jeu.getJoueur().getMainIndice(i).valeur()>21))) {
                                jeu.setArgentJoueur(jeu.getJoueur().getArgent()+jeu.getJoueur().getMainIndice(i).getMise());
                        }
                    }        
                }   
            }
        }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, fondTexture, NULL, NULL);

    aff(jeu,nbMains, mainCourante, mises,miseCourante,info);
    
    SDL_RenderPresent(renderer);
    SDL_Delay(16); 
}
}


void ApplicationSDL::afficherCarte()
{
    for (auto *c : cartesCroupierSDL)
    {
        c->update();
        c->renderCarte(renderer);
    }
    for (auto& main : cartesJoueurSDL)
    {
        for (SDL_Carte* j : main)
            {
                j->update();
                j->renderCarte(renderer);
            }
    }

    // AFFICHAGE DE LA PIOCHE
    SDL_Rect rectDos; 
    SDL_Rect dstRect;
    rectDos.x = 13 * (int)CARTE_W;
    rectDos.y = 0;
    dstRect.x = (int)PIOCHE_X;
    dstRect.y = (int)PIOCHE_Y;
    rectDos.w = dstRect.w = (int)CARTE_W;
    rectDos.h = dstRect.h = (int)CARTE_H;
    SDL_RenderCopy(renderer, textureCartes, &rectDos, &dstRect);
}
void ApplicationSDL::updateCarteFenetre(JeuBlackJack &jeu, float MAIN_OFFSET) {
    int totalCroupier = jeu.getCroupier().getNbCarteCroupier();
    int actuelCroupier = (int)cartesCroupierSDL.size();
    if (etat == ANIMATION) {
        cartesCroupierSDL[1]->setCarteCachee(false);
    }
    for (int i = actuelCroupier; i < totalCroupier; i++) {
        cartesCroupierSDL.push_back(new SDL_Carte(
            jeu.getCroupier().getCarte(i).getValeur(), 
            jeu.getCroupier().getCarte(i).getCouleurInt(), 
            textureCartes,
            PIOCHE_X, PIOCHE_Y, /// Depart 
            MAIN_X_BASE + i * ESPACEMENT, MAIN_CROUPIER_Y, /// Arrivee
            !(jeu.getCroupier().getCarte(i).getVisible()) 
        ));
    }
    int nbMainsLogique = jeu.getJoueur().getMainTaille();
    if (cartesJoueurSDL.size() < (size_t)nbMainsLogique) {
        cartesJoueurSDL.resize(nbMainsLogique);
    }

    for (int j = 0; j < nbMainsLogique; j++) {
        int totalCartesMain = jeu.getJoueur().getMainIndice(j).getNbCarte();
        int actuelCartesVisuel = (int)cartesJoueurSDL[j].size();

        float origineX = MAIN_X_BASE + j * MAIN_OFFSET;

        for (int i = actuelCartesVisuel; i < totalCartesMain; i++) {
            cartesJoueurSDL[j].push_back(new SDL_Carte(
                jeu.getJoueur().getMainIndice(j).getCarteIndice(i).getValeur(), 
                jeu.getJoueur().getMainIndice(j).getCarteIndice(i).getCouleurInt(), 
                textureCartes,
                PIOCHE_X, PIOCHE_Y, 
                origineX + i * ESPACEMENT, MAIN_JOUEUR_Y - i * 30, 
                false
            ));
        }
    }
}

void ApplicationSDL::nettoyerCarteFenetre(){
    for (auto& main : cartesJoueurSDL){
        for (SDL_Carte* c : main) delete c;
    }
    cartesJoueurSDL.clear();
    for (SDL_Carte* c : cartesCroupierSDL) delete c;
    cartesCroupierSDL.clear();
}