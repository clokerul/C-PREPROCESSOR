#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#define HASHMAP_KEY_NOT_FOUND 0
#define HASHMAP_KEY_FOUND 1

typedef struct Mapping{
    char key[50], value[50];
} T_Mapping;

typedef struct HashMap{
    T_Mapping *entry;
    struct HashMap *next;
} T_HashMap;

// Returns a hashmap
T_HashMap* hashmap_init();

// Puts a value into the hashmap
void hashmap_put(T_HashMap* map, char *key, char* value);

/***
 * @param *value will point towards the value of the key if existent else, won t be modified
 * @return HASHMAP_KEY_NOT_FOUND or HASHMAP_KEY_FOUND
 */
int hashmap_get(T_HashMap* map, char *key, char** value);

// Will delete the hashmap and free the memory
void hashmap_delete(T_HashMap* map);

void hashmap_print(T_HashMap* map);

#endif