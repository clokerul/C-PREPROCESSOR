#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libraries.h"

void process_value(char **value, T_HashMap *symbol_map);

int main(int argc, char *argv[]) {
   
    // Init PHASE
    T_HashMap* symbol_map = hashmap_init();
    T_LineArguments *line_args = (T_LineArguments*) malloc (1 * sizeof(T_LineArguments));
    FILE *main_file, *out_file = stdout;
    char line[300], *token, *delimitators = "\t ()[]{}<>=+-*/!&|^.,:;.";
    int read = 0;
    int skip_else = 0, reenter_if = 0;
    if (line_args == NULL) { exit (12);};

    init_lineargs(line_args);
    process_arguments(symbol_map, line_args, argc, argv);

    // Open input stream
    if (line_args->infile[0] != '\0') {
        main_file = fopen(line_args->infile, "r");
        if (main_file == NULL) {
            exit(-1);
        }
    }
    else 
        main_file = stdin;

    // Open output stream
    if (line_args->outfile[0] != '\0') {
        out_file = fopen(line_args->outfile, "wr");
        if (out_file == NULL) {
            exit(-1);
        }
    }
    
    while (fgets(line, 300, main_file) != NULL) {
        read = strlen(line);

        // Handles directives
        if (line[0] == '#') {
            if (line[read - 1] == '\n')
                line[read - 1] = '\0'; // Get rid of \n

            token = strtok(line, " ");

            // Handles #define directives
            if (strcmp(token, "#define") == 0) {
                char *symbol = strtok(NULL, " "),
                    *value = symbol + strlen(symbol) + 1;

                // Multiline case
                while (value[strlen(value) - 1] == '\\') {
                    char multiline_define[300];
                    value[strlen(value) - 1] = '\0';
                    fgets(multiline_define, 300, main_file);
                    strcat(value, strtok(multiline_define, "\t"));
                    value[strlen(value) - 1] = '\0';
                }

                if (value != NULL) {
                    process_value(&value, symbol_map);
                }
                hashmap_put(symbol_map, symbol, value);

                if (value != NULL)
                    free(value);
            } else if (strcmp(token, "#undef") == 0) {
                char *symbol = strtok(NULL, " ");
                hashmap_delete_value(&symbol_map, symbol);
            } else if (strcmp(token, "#if") == 0) {
                reenter_if = 1;
                while (reenter_if) {
                    char *symbol = strtok(NULL, " "), value[50];
                    int non_valid_if = 0;
                    
                    if (hashmap_get(symbol_map, symbol, value) == HASHMAP_KEY_FOUND) {
                        if (atoi(value) == 0) {
                            non_valid_if = 1;
                        }
                    } else {
                        if (atoi(symbol) == 0) {
                            non_valid_if = 1;
                        }
                    }
                    if (non_valid_if == 1) {
                        while (fgets(line, 300, main_file) != NULL) {
                            if (line[strlen(line) - 1] == '\n')
                                line[strlen(line) - 1] = '\0';

                            char *end_token = strtok(line, " ");
                            if (!strcmp("#else", end_token) || strcmp("#endif", end_token) == 0) {
                                reenter_if = 0;
                                break;
                            }
                            if (!strcmp("#elif", end_token)) {
                                reenter_if = 1;
                                break;
                            }
                        }
                    }
                    else {
                        skip_else = 1;
                        reenter_if = 0;
                    }
                }
            } else if (strcmp(token, "#ifdef") == 0) {
                char *symbol = strtok(NULL, " "), value[50];
                int found = 1;
                
                // IFDEF SHOULD BE IGNORED
                if (hashmap_get(symbol_map, symbol, value) == HASHMAP_KEY_NOT_FOUND) {
                    found = 0;
                    while (fgets(line, 300, main_file) != NULL) {
                        if (strcmp("#else\n", line) == 0 || strcmp("#endif\n", line) == 0) {
                            break;
                        }
                    }
                }

                if (found == 1) {
                    skip_else = 1;
                }
            } else if (strcmp(token, "#ifndef") == 0) {
                char *symbol = strtok(NULL, " "), value[50];
                int found = 0;
                
                // IFNDEF SHOULD BE IGNORED
                if (hashmap_get(symbol_map, symbol, value) == HASHMAP_KEY_FOUND) {
                    found = 1;
                    while (fgets(line, 300, main_file) != NULL) {
                        if (strcmp("#else\n", line) == 0 || strcmp("#endif\n", line) == 0) {
                            break;
                        }
                    }
                }

                if (found == 0) {
                    skip_else = 1;
                }
            } else if ((strcmp(token, "#else") == 0 || strcmp(token, "#elif") == 0) && skip_else == 1) {
                while (fgets(line, 300, main_file) != NULL) {
                    if (strcmp("#endif\n", line) == 0) {
                        break;
                    }
                }
                skip_else = 0;
            }
        } else {
            char line_copy[300], *token, *iterator;
            int iter_num = 0;
            if ((strchr("\t\n", line[0]) && strlen(line) < 3) || (strlen(line) == 5 && line[0] == ' ' && line[3] == ' ')) continue;

            strcpy(line_copy, line);
            iterator = line_copy;

            token = strtok(line_copy, delimitators);

            if (token == NULL) {
                fprintf(out_file, "%s", line);
            }

            while (token != NULL) {
                char value_in_map[50];

                while ((char*)(iterator + iter_num) != (char*)(token + 0)) {
                    if (strchr(delimitators, line_copy[iter_num]) != NULL)
                        fprintf(out_file, "%c", line[iter_num]);
                    iter_num++;
                }

                if (token[0] == '"') {
                    fprintf(out_file, "%s", token);
                    token = strtok(NULL, delimitators);
                    continue;
                }

                if (hashmap_get(symbol_map, token, value_in_map) == HASHMAP_KEY_FOUND) {
                    fprintf(out_file, "%s", value_in_map);
                } else {
                    fprintf(out_file, "%s", token);
                }

                token = strtok(NULL, delimitators);
            }
        }
    }
    hashmap_delete(symbol_map);

    fclose(main_file);
    fclose(out_file);
    free(line_args);

    return 0;
}

// Processes imbricated defines
void process_value(char **value, T_HashMap *symbol_map) {
    char new_value[50] = "", copy_value[50], *token, value_in_map[50];
    char *allocated_string;

    strcpy(copy_value, *value);
    token = strtok(copy_value, " ");
    while (token != NULL) {       
        if (hashmap_get(symbol_map, token, value_in_map) == HASHMAP_KEY_FOUND) {
            strcat(new_value, value_in_map);
        } else {
            strcat(new_value, token);
        }
        token = strtok(NULL, " ");
        if (token != NULL)
            strcat(new_value, " ");
    } 

    allocated_string = (char*) malloc (50* sizeof(char));
    if (allocated_string == NULL) { exit (12);};
    strcpy(allocated_string, new_value);
    *value = allocated_string;
}