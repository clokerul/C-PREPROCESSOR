#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

T_HashMap* hashmap_init() {
    T_HashMap *map = (T_HashMap*) malloc(1 * sizeof(T_HashMap));
    map->next = NULL;
    map->entry = NULL;
    return map;
}

int hashmap_get(T_HashMap* map, char *key, char** value) {
    if (map == NULL || map->entry == NULL) return HASHMAP_KEY_NOT_FOUND;

    T_HashMap *iter = map;
    while (iter != NULL) {
        if (iter->entry->key == key) {
            *value = iter->entry->value;
            return HASHMAP_KEY_FOUND;
        }
    }

    return HASHMAP_KEY_NOT_FOUND;
}

void hashmap_delete(T_HashMap* map) {
    if (map == NULL) return;

    T_HashMap *this = map, *next = map->next;

    while (this != NULL) {
        free(this->entry);
        this = next;
        if (next != NULL)
        next = next->next;
    }
}

void hashmap_put(T_HashMap* map, char *key, char* value) {
    // If map is null, initialize it
    if (map == NULL) {
        map = hashmap_init();
    }

    T_HashMap *iter = map;
    while(iter->next != NULL && strcmp(iter->entry->key, key)) { iter = iter->next;}

    if (iter->next == NULL) {
        iter->entry = (T_Mapping*) malloc (1 * sizeof(T_Mapping));
        iter->next = hashmap_init();
    }

    strcpy(iter->entry->key, key);
    strcpy(iter->entry->value, value);

    printf("hasmap_put: values added %s -> %s\n", key, value);
}

void hashmap_print(T_HashMap* map) {
    printf("Printing hashmap:\n");
    T_HashMap *iter = map;

    while (iter != NULL) {
        printf("[%s - > %s]\n", iter->entry->key, iter->entry->value);
        iter = iter->next;
    }
}