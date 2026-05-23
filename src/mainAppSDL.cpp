#include "ApplicationSDL.h"
#include <iostream>

int main(void){
    ApplicationSDL app;
    JeuBlackJack jeu{"Nom a choisr",5000};
    app.boucleSDL(jeu);  
}