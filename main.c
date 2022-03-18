#include <stdio.h>
#include <stdlib.h>
#include "project_utils/libraries.h"

int main(int argc, char *argv[]) {
   
    T_HashMap* symbol_map = hashmap_init();
    T_LineArguments *line_args = (T_LineArguments*) malloc (1 * sizeof(T_LineArguments));

    init_lineargs(line_args);

    process_arguments(symbol_map, line_args, argc, argv);
    print_line_arguments(line_args);
    hashmap_print(symbol_map);

    //free(line_args);

    return 0;
}