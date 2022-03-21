#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#define HASHMAP_KEY_NOT_FOUND 0
#define HASHMAP_KEY_FOUND 1
#define MY_DEBUG_FLAG 0

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
int hashmap_get(T_HashMap* map, char *key, char value[50]);

// Will delete the hashmap and free the memory
void hashmap_delete(T_HashMap* map);

// Will delete the value from hashmap, freeing the memory in process
void hashmap_delete_value(T_HashMap** map_pointer, char *key);

void hashmap_print(T_HashMap* map);

#endif