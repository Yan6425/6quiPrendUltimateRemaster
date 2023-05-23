exe: fonctions.o main.o
@echo "compilation de l'executable"
gcc fonctions.o main.o -o exe

fonctions.o: fonctions.c fonctions.h
@echo "compilations de fonctions"
gcc -c -Wall fonctions.c  -o fonctions.o

main.o: main.c fonctions.h
@echo "compilations du main"
gcc -c -Wall main.c -o main.o
clean:
@echo "J'ai tout effacé"
rm -f *.o