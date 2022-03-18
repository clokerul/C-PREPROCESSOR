#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>

T_HashMap* hashmap_init() {
    T_HashMap *map = (T_HashMap*) malloc(1 * sizeof(T_HashMap));
    map->next = NULL;
    map->entry = NULL;
    return map;
}

int hashmap_get(T_HashMap* map, char *key, char* value) {
    if (map == NULL) return HASHMAP_KEY_NOT_FOUND;

    T_HashMap *iter = map;
    while (iter != NULL) {
        if (iter->entry->key == key) {
            value = iter->entry->value;
            return HASHMAP_KEY_FOUND;
        }
    }

    return HASHMAP_KEY_NOT_FOUND;
}

void hashmap_delete(T_HashMap* map) {
    if (map == NULL) return;

    T_HashMap *this = map, *next = map->next;

    while (this != NULL) {
        free(this->entry->key);
        free(this->entry->value);
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

    // Trying to find if the file already is existent
    char *existent_value;
    if (hashmap_get(map, key, existent_value) == HASHMAP_KEY_FOUND) {
        printf("Mapping %s->%s already exists in this hashmap! For entry %s->%s\n", key, existent_value, key, value);
    } else {
        T_HashMap *iter = map;
        while(iter->next != NULL) {}

        iter->entry = (T_Mapping*) malloc (1 * sizeof(T_Mapping));
        iter->next = hashmap_init();

        iter->entry->key = key;
        iter->entry->value = value;
    }
}