#! /usr/bin/bash

# When true will stop script
ALL_DONE=0;
VERBOSE=1;

function tell(){
    if [ $VERBOSE ]; then 
        echo "[$(basename $0)] $@";
    fi
} 

function create_dir() {
    n=1;
    dirname=$([ $n -lt 10 ] && echo "0$n" || "$n" );
    while  ! mkdir $dirname 2>/dev/null; do
        n=$((n + 1));
        [ $n -gt 25 ] && { ALL_DONE=1; break; }
        dirname=$([ $n -lt 10 ] && echo "0$n" || echo "$n" );
    done
   [ $ALL_DONE -ne 1 ] && tell "created $dirname" || tell "Congratulations, you are done!"
} 

function fill_dir() {
   [ $ALL_DONE -eq 1 ] && return;  
    echo -n "#include <iostream>
#include <string>

using namespace std;
int main(int argc, char** argv) {

}
" > $dirname/main.cc 
    tell "added $dirname/main.cc";

    echo -n "CC := g++
LINKERFLAGS := -lm
CCFLAGS := -Wall -Wextra -Wpedantic -Werror 

all: main.out

main.out: main.o
	\${CC} \${LINKERFLAGS} main.o -o main.out

main.o: main.cc
	\${CC} -c \${CCFLAGS} main.cc

clean:
	rm *.o
	rm main.out

run: all
	./main.out infile.txt outfile.txt

    " > $dirname/Makefile

    tell "added $dirname/Makefile";
    touch $dirname/infile.txt;
    tell "added $dirname/infile.txt";
    touch $dirname/outfile.txt; 
    tell "added $dirname/outfile.txt";
}

create_dir;
fill_dir;
