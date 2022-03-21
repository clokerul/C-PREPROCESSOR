#include "line_args.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_lineargs(T_LineArguments *line_args) {
    line_args->infile[0] = '\0';
    line_args->outfile[0] = '\0';
    line_args->last_directory = 0;
}

void read_symbol(char *symbol, char key_value[][50]) {
    int i, j;

    // Extract the key
    for (i = 0; symbol[i] != '\0' && symbol[i] != '='; ++i) {
        key_value[0][i] = symbol[i];
    }
    key_value[0][i] = '\0';

    // jump over '='
    if (symbol[i] == '=') i++;

    // Extract the value
    for (j = i; symbol[j] != '\0'; ++j) {
        key_value[1][j - i] = symbol[j];
    }
    key_value[1][j - i] = '\0';
}

void process_arguments(T_HashMap *map, T_LineArguments *line_args, int argc, char *argv[]) {
    
    int i = 1;
    char flag = 0, infile_flag = 0;

    while (i < argc) {
        if (argv[i][0] == '-') {
            char key_value[2][50], argument[50];
            int last_directory;

            // Case of bad input
            if (i + 1 >= argc)
                break;

            flag = argv[i][1];

            if (flag == 'D' || flag == 'I' || flag == 'o') {
                if (argv[i][2] == '\0') {
                    strcpy(argument, argv[i + 1]);
                    i++;
                } else {
                    strcpy(argument, argv[i] + 2);
                }
            }

            switch (flag) {
            case 'D':
                
                read_symbol(argument, key_value);
                hashmap_put(map, key_value[0], key_value[1]);
                break;
            case 'I':   // add new directory
                
                last_directory = line_args->last_directory;
                strcpy(line_args->source_directors[last_directory], argument);
                line_args->last_directory++;
                break;
            case 'o':   // outfile
                
                strcpy(line_args->outfile, argument);
                break;
            
            default:
                break;
            }
        } else {
            if (infile_flag == 0) {
                strcpy(line_args->infile, argv[i]);
                infile_flag++;
            } else if (infile_flag == 1) {
                strcpy(line_args->outfile, argv[i]);
                infile_flag++;
            } else {
                    
                exit(-1);
            }
        }
        i++;
    }
}

void print_line_arguments(T_LineArguments *args) {      
    int i;
    for (i = 0; i < args->last_directory; ++i) {
        printf("%d ", i);
        printf("%s\n", args->source_directors[i]);
    }
}