#makefile à executer avec l'installation de SDL dans les salles TP
#Version du 09/02/23 
CC=gcc

SDLLIB_DIR=/usr/lib/x86_64-linux-gnu
SDLINC_DIR= /usr/include/SDL2

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG1=fonc.o
PROG2=menu.o
MAIN=main.o
BDD=base_struct.o
TEST=testSDL.o
EXECUTABLE=test

all: test

test: fonc.o menu.o main.o base_struct.o testSDL.o
	${CC}  ${PROG1} ${PROG2} ${MAIN} ${BDD} ${TEST} -o test ${LIBS} ${INCLUDES}

fonc.o: fonc.c
	${CC} -c fonc.c ../lib/fonc.h

menu.o: menu.c 
	${CC} -c menu.c ../lib/fonc.h

main.o: main.c
	${CC} -c main.c ../lib/fonc.h

base_struct.o:	base_struct.c
	${CC} -c base_struct.c ../lib/base_struct.h

testSDL.o:	testSDL.c
	${CC} -c testSDL.c ../lib/base_struct.h


clean: 
	rm -f ${PROG1}
	rm -f ${PROG2}
	rm -f ${MAIN}
	rm -f ${BDD}
	rm -f ${TEST}
	rm -f ${EXECUTABLE}
	rm -f *.o