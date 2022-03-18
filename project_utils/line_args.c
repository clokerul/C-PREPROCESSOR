#include "line_args.h"
#include <stdio.h>
#include <string.h>

void init_lineargs(T_LineArguments *line_args) {
    line_args->infile[0] = '\0';
    line_args->outfile[0] = '\0';
    line_args->last_directory = 0;
}

void read_symbol(char *symbol, char key_value[][50]) {
    int i, j;

    for (i = 0; symbol[i] != '\0' && symbol[i] != '='; ++i) {
        key_value[0][i] = symbol[i];
    }
    key_value[0][i] = '\0';

    for (j = i + 1; symbol[j] != '\0'; ++j) {
        key_value[1][j - i - 1] = symbol[j];
    }
}

void process_arguments(T_HashMap *map, T_LineArguments *line_args, int argc, char *argv[]) {
    
    int i = 0, flag_active = 0;
    char flag = 0;

    while (i < argc) {
        // If this is a flag
        if (argv[i][0] == '-') {
            flag = argv[i][1];
            flag_active = 1;
        } else {
            flag_active = 0;
        }

        // Before was a flag
        if (flag_active == 1) {
            char key_value[2][50];
            int last_directory;

            switch (flag) {
            case 'D':
                printf("Flag D detected with %s\n", argv[i]);
                read_symbol(argv[i], key_value);
                hashmap_put(map, key_value[0], key_value[1]);
                break;
            case 'I':   // add new directory
                printf("Flag I detected with %s\n", argv[i]);
                last_directory = line_args->last_directory;
                strcpy(line_args->source_directors[last_directory], argv[i]);
                line_args->last_directory++;
                break;
            case 'o':   // outfile
                printf("Flag o detected with %s", argv[i]);
                strcpy(line_args->outfile, argv[i]);
                break;
            
            default:
                break;
            }
            flag_active = 0;
        }
        i++;
    }
}

void print_line_arguments(T_LineArguments *args) {
    printf("Directories:\n");
    for (int i = 0; i < args->last_directory; ++i) {
        printf("%d", i);
        printf("%s\n", args->source_directors[i]);
    }

    printf("Infile: %s\n", args->infile);
    printf("Outfile: %s\n", args->outfile);
}