# paiement-refusé
**GRAZIANO Edoardo - GURSEL Mustafa - ETIENNE Nathan**
**- 12402567 - 12400647 - 12405730**

**Identifiant forge : 42465**

Paiement-refusé est une application présentant un jeu de BlackJack complet avec toutes ses règles et fonctionnalités classiques.
IL est écrit en C++ et est compilable sous Linux, Windows et MacOS

## Organisation fichiers

L'organisation des fichiers est la suivante :

- **paiement-refusé/bin** : Répertoire contenant les fichiers executables à appeler pour lancer les différentes démos, le jeu en TXT ainsi qu'en SDL
- **paiement-refusé/data** : Répertoire contenant les images, sons et polices utilisés dans l'application SDL
- **paiement-refusé/obj** : Répertoire contenant les fichiers objets permettant de construire les executables (utilisés dans les Makefile) 
- **paiement-refusé/src** : Toutes les classes et code de l'application
- **paiement-refusé/doc** : Répertoire contenant la documentation doxygen, consultable grâce au Makefile


## Compilation et execution

### Installer SDL2 

Pour installer SDL2 sous Linux ou avec WSL/Windows

``` sudo apt install python3 valgrind doxygen libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev imagemagick ```

Pour Windows, le répertoire extern contient une version précompilé de SDL2 pour CB.

### Version tests régression

``` make bin/test ```

``` ./bin/test ```

### Application texte 

``` make bin/appTXT ```

``` ./bin/appTXT ```


### Application SDL2

``` make bin/appSDL ```

``` ./bin/appSDL ```


### Documentation du code

``` make docu ```

``` firefox doc/html/index.html ```


### Nettoyage des fichiers objets et executables

``` make clean ```

## Fonctionnement de l'application


### Fonctionnement appTXT

L'application en TXT tourne sur le terminal, seul le clavier sera donc utile.

Après avoir choisi son nombre de mains et ses mises pour chacunes, l'application vous précisera donc les actions possibles et le nombre a rentrer dans le terminal pour chacune.
Pour les action de double ou de split, il est toujours possible de rentrer leur chiffres mais l'application vous précisera si l'action à été effectuée ou alors s'il n'est pas possible et qu'il faut rejouer.

##### Actions possibles

- Choix du nombre de main : entrez le nombre au clavier (entre 1 et 3)
- choix des mises : entrez le nombre au clavier
- choix de l'action à réaliser : entrez un chiffre entre 1 et 4
- Fin de partie : Option rejouer : y, quitter l'application : n

A la fin de la partie, vos victoires et défaites seont décrites et l'agent gagné ou perdu seras modifié.

### Fonctionnement appSDL

L'application SDL ouvre une nouvelle fenếtre à son lancement, seul le clavier est utile.

Une première page permet de choisir son nombre de main et les mises.
Cette page envoie ensuite sur la page de Jeu ou les actions seront choisie avec des boutons.
Une troisième page est affichée à la fin du jeu pour les résultats.

##### Actions possibles 

- Choix du nombre de mises : utilisation des flèches directionnelles haut et bas, appuyer sur entrée pour valider
- choix des mises : flèches directionnelles gauche et droite pour choisir le montant, flèches haut et bas pour changer de mise, entrée pour valider
- choix de l'action à réaliser : les actions possibles pour la main s'affichent dynamiquement. Appuyez sur les touches A, Z, E ou R pour jouer.
-  Fin de partie : Option rejouer : y, quitter l'application : n



## Règles du jeu du BlackJack: 
BlackJack : Le BlackJack est un jeu de cartes où le joueur joue contre le croupier. 
As : 1 ou 11 pts   K/D/J : 10 pts   cartes numériques : leur valeur

Le croupier distribue deux cartes chacun, les deux sont dévoilées pour le joueur et une reste face cachée pour le croupier. L’objectif du jeu pour les deux joueurs est de se rapprocher le plus possible de 21 avec la somme de leurs cartes. 
	

Le joueur , lorsqu’il a pris connaissances de sa somme, à plusieurs possibilités : 

### BlackJack -> As + 10  : Le joueur gagne instantanément et il gagne 2.5 fois sa mise.
### Tirer ( hit ): le joueur demande une carte supplémentaire pour se rapprocher de 21. Attention -> possibilité de dépasser
- Possibilité de tirer autant que voulu
### Rester ( stay ) : le joueur se contente de ses deux cartes et finit son tour
### Doubler  ( double ): Le joueur double sa mise, une carte supplémentaire lui est donnée
- Il n’est plus possible de tirer de cartes ensuite
- possible seulement si le solde le permet
### Séparer ( split ) : Lorsque le joueur à deux cartes de même valeur il est possible de split, les deux cartes sont séparées et se transforment en deux jeux. Une carte est distribuée à chaque jeu et le joueur peut continuer à jouer normalement avec les deux.
- Doublement de la mise -> chaque jeu à la mise de départ
- possible seulement si le solde le permet
- Lorsque les As sont split, pas de possibilité de jouer ensuite
### Abandonner ( surrender ): Le joueur peut abandonner et donc la manche ne se joue pas, le joueur récupère la moitié de sa mise.
- Possible seulement si aucune autre action à été effectuée en amont


### Si carte croupier = 11 :
Assurance ( insurance ) : Avant que le croupier vérifie s’il à BlackJack, possibilité de prendre une assurance. On pose une somme d’argent valant la moitié de la mise initiale.
L’assurance paie 2 pour 1 : 
	BlackJack : le joueur double son assurance et la mise initiale est perdue.
	Pas BlackJack : le joueur perd son assurance et la main continue avec la mise initiale.

Une fois que tous les jours autour de la table ont joué, la main retourne au croupier.
 
Le croupier retourne donc sa deuxième carte et compte son score.

**Score < 17 :** le croupier reprend des cartes jusqu'à obtenir 17 ou plus 

**Score > 17 :** le croupier ne tire plus de cartes

**Si le croupier a dépassé 21 :** toutes les mains de joueur n’ayant pas dépassé gagnent et double leur mise de départ.

**Autre :** Les joueurs gagnent si leur score est plus élevé que le score du croupier et double donc leur mises.
	Les joueurs ayant un score inférieur perdent leur mise.
