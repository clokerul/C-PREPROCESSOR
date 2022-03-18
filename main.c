#include <stdio.h>
#include <stdlib.h>
#include "project_utils/libraries.h"

int main(int argc, char *argv[]) {
   
    T_HashMap* symbol_map = hashmap_init();
    T_LineArguments *line_args = (T_LineArguments*) malloc (1 * sizeof(T_LineArguments));

    init_lineargs(line_args);

   /*
    TEST 1
    hashmap_put(symbol_map, "a", "asd");
    hashmap_put(symbol_map, "a", "b");
    hashmap_print(symbol_map);
    hashmap_delete(symbol_map);*/


    process_arguments(symbol_map, line_args, argc, argv);
    print_line_arguments(line_args);
    hashmap_print(symbol_map);
    hashmap_delete(symbol_map);

    free(line_args);

    return 0;
}