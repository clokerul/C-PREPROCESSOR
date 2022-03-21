CC = gcc

build: so-cpp.o hashmap.o line_args.o
	gcc -Wall -o so-cpp so-cpp.o hashmap.o line_args.o

so-cpp.o: so-cpp.c
hashmap.o: hashmap.c
line_args.o: line_args.c


clean:
	rm so-cpp
	rm *.o