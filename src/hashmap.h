#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "vector.h"
#include "darray.h"
     
typedef struct HashMapNode {
    char *key;
    void *value;
} HashMapNode;


typedef struct HashMap {
    DArray *buckets;
    int entries;
} HashMap;


HashMap *
HashMap_create();

HashMap *
HashMap_deepCopy(HashMap *hashmap);

int
HashMap_size(HashMap *hashmap);

int
HashMap_entries(HashMap *hashmap);

void
HashMap_put(HashMap *hashmap, char *key, void *value);

void
HashMap_remove(HashMap *hashmap, char *key);

void *
HashMap_get(HashMap *hashmap, char *key);

int
HashMap_containsKey(HashMap *hashmap, char *key);

void
HashMap_destroy(HashMap *hashmap);

void
HashMap_iterate_kv(HashMap *hashmap, void (*iterator)(void *key, void *value));

void
HashMap_iterate_k(HashMap *hashmap, void (*iterator)(void *key));

int
HashMap_find_bucket_index(HashMap *hashmap, char *key);

Vector *
HashMap_find_bucket(HashMap *hashmap, char *key);

typedef struct HashMapIterator {
    HashMap *map;
    int index;
    int bucket_index;
    HashMapNode *next;
} HashMapIterator;

HashMapIterator *
HashMap_getIterator(HashMap *hashmap);

HashMapNode *
HashMapIterator_getNext(HashMapIterator *it);

void
HashMapIterator_reset(HashMapIterator *it);

void
HashMapIterator_destroy(HashMapIterator *it);

#endif
