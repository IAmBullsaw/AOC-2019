#! /usr/bin/bash

function create_dir() {
    n=1;
    all_done=0;
    dirname=$([ $n -lt 10 ] && echo "0$n" || "$n" );
    while  ! mkdir $dirname 2>/dev/null; do
        n=$((n + 1));
        [ $n -gt 25 ] && { all_done=1; break; }
        dirname=$([ $n -lt 10 ] && echo "0$n" || echo "$n" );
    done
   [ $all_done -ne 1 ] && echo "[$(basename $0)] created $dirname" || echo "[$(basename $0)] Congratulations, you are done!"
} 

function fill_dir() {
   [ $all_done -eq 1 ] && return;  
    echo -n "#include <iostream>
#include <string>

using namespace std;
int main(int argc, char* argv) {

}
" > $dirname/main.cc 
    echo "[$(basename $0)] added $dirname/main.cc"
    echo -n "CC := g++
LINKERFLAGS := -lm
CCFLAGS := -Wall -Wextra -Wpedantic -Werror 

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

    " > $dirname/Makefile
    echo "[$(basename $0)] added $dirname/Makefile"
}

create_dir;
fill_dir;
