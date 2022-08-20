CC = gcc
CC_FLAGS = -Wall -Werror -std=c11 -g
CC_LIBS = -lm
CC_SRC = ppm.c

all: main run

main: ${CC_SRC}
	${CC} ${CC_FLAGS} ${CC_LIBS} ${CC_SRC} -o main

run: main
	./main 

clean:
	rm main
	rm test.ppm
