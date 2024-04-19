#makefile à executer avec l'installation de SDL dans les salles TP
#Version du 09/02/23 
CC=gcc

SDLLIB_DIR=/usr/lib/x86_64-linux-gnu
SDLINC_DIR= /usr/include/SDL2

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG1=fonc.o
PROG2=menu.o
PROG3=map.o
MAIN=main.o
BDD=base_struct.o
TEST=jeu.o
EXECUTABLE=../bin/test

all: test

test: fonc.o menu.o main.o base_struct.o jeu.o map.o
	${CC}  ${PROG1} ${PROG2} ${PROG3} ${MAIN} ${BDD} ${TEST} -o ../bin/test ${LIBS} ${INCLUDES}

fonc.o: fonc.c
	${CC} -c fonc.c ../lib/fonc.h

map.o: map.c
	${CC} -c map.c ../lib/fonc.h

menu.o: menu.c 
	${CC} -c menu.c ../lib/fonc.h

main.o: main.c
	${CC} -c main.c ../lib/fonc.h

base_struct.o:	base_struct.c
	${CC} -c base_struct.c ../lib/base_struct.h

jeu.o:	jeu.c
	${CC} -c jeu.c ../lib/base_struct.h


clean: 
	rm -f ${PROG1}
	rm -f ${PROG2}
	rm -f ${PROG3}
	rm -f ${MAIN}
	rm -f ../lib/*.gch
	rm -f ${BDD}
	rm -f ${TEST}
	rm -f ${EXECUTABLE}
	rm -f *.o