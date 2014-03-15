#DIRSDL=/users/prog1a/C/librairie/2011
DIRSDL=/home/robin_arch/cour/1ere_annee_phelma/info/sdl_phelma/

CC=g++
CFLAGS=-g -c -O2 -Wall -Wextra -std=c++11
LDFLAGS= 
CIBLE=use_case2

use_case2: use_case2.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

run : ${CIBLE}
	./${CIBLE}

all :

test: test.cpp

%.o:%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

clean:
	rm *.o test


