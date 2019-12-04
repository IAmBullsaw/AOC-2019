CC := g++
LINKERFLAGS := -lm
CCFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -Werror

all: main.out

main.out: main.o
	${CC} ${LINKERFLAGS} main.o -o main.out

main.o: main.cc
	${CC} -c ${CCFLAGS} main.cc

clean:
	rm *.o
	rm main.out

run: all
	./main.out infile.txt outfile.txt

