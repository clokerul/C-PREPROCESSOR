#ifndef _LINE_ARGS_H_
#define _LINE_ARGS_H_
#include "hashmap.h"

typedef struct LineArguments {
    char source_directors[50][50], infile[50], outfile[50];
    int last_directory;
} T_LineArguments;

void init_lineargs(T_LineArguments *line_args);
void process_arguments(T_HashMap *map, T_LineArguments *line_args, int argc, char *argv[]);
void print_line_arguments(T_LineArguments *args);


#endif