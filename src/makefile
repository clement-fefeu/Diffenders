CC=gcc

 
SDLLIB_DIR=/usr/lib/x86_64-linux-gnu
SDLINC_DIR= /usr/include/SDL2

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG=sdl_text

all: sdl_text

sdl_text: testSDL.c
	${CC} -o ${PROG} testSDL.c ${LIBS} ${INCLUDES}

prog: base_struct.o
		gcc base_struct.o -o prog
base_struct.o:	base_struct.c
				gcc -c base_struct.c base_struct.h
testSDL.o:	testSDL.c
			gcc -c testSDL.c



clean: 
	rm -f ${PROG}
	rm -f *.o

