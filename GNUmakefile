CC = gcc

build: main.o hashmap.o line_args.o
	gcc -Wall -o so-cpp main.o hashmap.o line_args.o

main.o: main.c
hashmap.o: hashmap.c
line_args.o: line_args.c


clean:
	rm so-cpp