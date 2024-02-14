#makefile à executer avec l'installation de SDL dans les salles TP
#Version du 09/02/23 
CC=gcc

SDLLIB_DIR=/usr/lib/x86_64-linux-gnu
SDLINC_DIR= /usr/include/SDL2

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG=test_sdl

all: test_sdl

test_sdl: test1.c
	${CC} -o ${PROG} test1.c ${LIBS} ${INCLUDES}

clean: 
	rm -f ${PROG}
	rm -f *.o