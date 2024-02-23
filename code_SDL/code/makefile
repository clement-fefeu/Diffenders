#makefile à executer avec l'installation de SDL dans les salles TP
#Version du 09/02/23 
CC=gcc

SDLLIB_DIR=/usr/lib/x86_64-linux-gnu
SDLINC_DIR= /usr/include/SDL2

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG1=fonc.o
PROG2=main.o

all: test

test: fonc.o main.o
	${CC}  ${PROG1} ${PROG2} -o test ${LIBS} ${INCLUDES}

fonc.o: fonc.c
	${CC} -c fonc.c fonc.h

main.o: main.c 
	${CC} -c main.c fonc.h

clean: 
	rm -f ${PROG1}
	rm -f ${PROG2}
	rm -f *.o