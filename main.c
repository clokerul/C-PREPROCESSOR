#include <stdio.h>
#include "hashmap.h"

int main(int argc, char *argv[]) {
    
    int a;
   
    T_HashMap* map = hashmap_init();
    char *value = NULL;
    printf("HI\n");
    hashmap_put(map, "lala", "band");
    hashmap_get(map, "lala", &value);
    printf("%s\n", value);
    
    return 0;
}