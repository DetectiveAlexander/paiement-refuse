#include "Carte.h"
#include "Deck.h"
#include "Croupier.h"
#include "Main.h"
#include "Joueur.h"
#include "JeuBlackJack.h"

int main(void)	{
	Carte::testRegression();
	Deck::testRegression();
	Croupier::testRegression();
	Main::testRegression();
	Joueur::testRegression();
	JeuBlackJack::testRegression();
	return 0; 
}
