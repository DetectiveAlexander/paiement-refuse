all: bin/test bin/appTXT bin/appSDL

bin/test: src/mainTest.cpp obj/Carte.o obj/Deck.o obj/Croupier.o obj/Main.o obj/Joueur.o obj/JeuBlackJack.o obj/ApplicationTXT.o
	g++ -g -Wall -o bin/test src/mainTest.cpp obj/Carte.o obj/Deck.o obj/Croupier.o obj/Main.o obj/Joueur.o obj/JeuBlackJack.o obj/ApplicationTXT.o

bin/appTXT: src/mainAppTXT.cpp obj/Carte.o obj/Deck.o obj/Croupier.o obj/Main.o obj/Joueur.o obj/JeuBlackJack.o obj/ApplicationTXT.o 
	g++ -g -Wall -o bin/appTXT src/mainAppTXT.cpp obj/Carte.o obj/Deck.o obj/Croupier.o obj/Main.o obj/Joueur.o obj/JeuBlackJack.o obj/ApplicationTXT.o

bin/appSDL: src/mainAppSDL.cpp obj/Carte.o obj/Deck.o obj/Croupier.o obj/Main.o obj/Joueur.o obj/JeuBlackJack.o obj/ApplicationSDL.o obj/SDL_Carte.o
	g++ -g -Wall -o bin/appSDL src/mainAppSDL.cpp obj/Carte.o obj/Deck.o obj/Croupier.o obj/Main.o obj/Joueur.o obj/JeuBlackJack.o obj/ApplicationSDL.o obj/SDL_Carte.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

obj/Main.o : src/Main.cpp src/Main.h src/Carte.h
	g++ -g -Wall -o obj/Main.o -c src/Main.cpp
	
obj/Joueur.o : src/Joueur.cpp src/Joueur.h src/Main.h
	g++ -g -Wall -o obj/Joueur.o -c src/Joueur.cpp
	
obj/Croupier.o : src/Croupier.cpp src/Croupier.h src/Carte.h
	g++ -g -Wall -o obj/Croupier.o -c src/Croupier.cpp 

obj/Deck.o : src/Deck.cpp src/Deck.h src/Carte.h
	g++ -g -Wall -o obj/Deck.o -c src/Deck.cpp 

obj/Carte.o : src/Carte.cpp src/Carte.h
	g++ -g -Wall -o obj/Carte.o -c src/Carte.cpp 

obj/JeuBlackJack.o : src/JeuBlackJack.cpp src/JeuBlackJack.h
	g++ -g -Wall -o obj/JeuBlackJack.o -c src/JeuBlackJack.cpp
obj/SDL_Carte.o: src/SDL_Carte.cpp src/SDL_Carte.h
	g++ -g -Wall -o obj/SDL_Carte.o -c src/SDL_Carte.cpp -lSDL2 -lSDL2_image

obj/ApplicationTXT.o : src/ApplicationTXT.cpp src/ApplicationTXT.h
	g++ -g -Wall -o obj/ApplicationTXT.o -c src/ApplicationTXT.cpp

obj/ApplicationSDL.o : src/ApplicationSDL.cpp src/ApplicationSDL.h
	g++ -g -Wall -o obj/ApplicationSDL.o -c src/ApplicationSDL.cpp 
docu:
	doxygen doc/doxyfile

clean:
	rm -rf obj/*.o doc/html doc/latex bin/*
