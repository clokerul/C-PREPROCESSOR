#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

T_HashMap* hashmap_init() {
    T_HashMap *map = (T_HashMap*) malloc(1 * sizeof(T_HashMap));
    if (map == NULL) { exit (12);};
    map->next = NULL;
    map->entry = NULL;
    return map;
}

int hashmap_get(T_HashMap* map, char *key, char value[50]) {
    if (map == NULL || map->entry == NULL) return HASHMAP_KEY_NOT_FOUND;

    T_HashMap *iter = map;
    while (iter != NULL && iter->entry != NULL) {
        if (strcmp(iter->entry->key, key) == 0) {
            strcpy(value, iter->entry->value);
            #if MY_DEBUG_FLAG
            printf("Found symbol %s -> %s", key, value);
            #endif
            return HASHMAP_KEY_FOUND;
        }
        iter = iter->next;
    }

    return HASHMAP_KEY_NOT_FOUND;
}

void hashmap_delete_value(T_HashMap** map_pointer, char *key) {
    #if MY_DEBUG_FLAG
    printf("Deleting value %s from map\n", key);
    #endif

    T_HashMap *map = *map_pointer;

    if (map == NULL || map->entry == NULL) return;
    if (strcmp(map->entry->key, key) == 0) {
        *map_pointer = map->next;
        free(map->entry);
        free(map);
        return;
    }

    T_HashMap *iter = map;
    while (iter->next != NULL && iter->next->entry != NULL) {
        if (strcmp(iter->next->entry->key, key) == 0) {
            T_HashMap *free_me = iter->next;
            iter->next = free_me->next;
            free(free_me->entry);
            free(free_me);
            return;
        }
        iter = iter->next;
    }

    return;
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
        if ( iter->entry == NULL) { exit (12);};
        iter->next = hashmap_init();
    }

    strcpy(iter->entry->key, key);

    if (value != NULL)
        strcpy(iter->entry->value, value);
    else
        strcpy(iter->entry->value, "");


    #if MY_DEBUG_FLAG
    printf("hasmap_put: values added %s -> %s\n", key, value);
    #endif
}

void hashmap_print(T_HashMap* map) {
    #if MY_DEBUG_FLAG
    printf("Printing hashmap:\n");
    #endif
    T_HashMap *iter = map;

    while (iter != NULL && iter->entry != NULL) {
        #if MY_DEBUG_FLAG
        printf("[%s - > %s]\n", iter->entry->key, iter->entry->value);
        #endif
        iter = iter->next;
    }
}

void hashmap_delete(T_HashMap* map) {
    if (map == NULL) return;

    T_HashMap *this = map, *next = map->next;

    while (this != NULL) {
        free(this->entry);
        free(this);
        this = next;
        if (next != NULL)
            next = next->next;
    }
}