CC = gcc
CC_FLAGS = -Wall -Werror -std=c11
CC_SRC = ppm.c 

all: main run

main: ${CC_SRC}
	${CC} ${CC_FLAGS} ${CC_SRC} -o main

run: main
	./main >test.ppm

clean:
	rm main
	rm test.ppm
