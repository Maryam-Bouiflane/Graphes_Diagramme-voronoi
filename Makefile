all: main.out

main.out: main.o Grille.o 
	g++ -g -W -Wall main.o Grille.o -o main.out 

main.o: main.cpp Grille.h 
	g++ -g -W -Wall -c main.cpp

Grille.o: Grille.h Grille.cpp
	g++ -g -W -Wall -c Grille.cpp -o Grille.o

clean:
	rm *.o

veryclean: clean
	rm *.out
