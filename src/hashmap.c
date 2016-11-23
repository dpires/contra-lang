#include "hashmap.h"
#include "vector.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "darray.h"
#include "MurmurHash3.h"


void
HashMap_resize(HashMap *hashmap)
{
    DArray *new_buckets = DArray_create(hashmap->buckets->capacity * 2);
    int new_entries = 0;
    int i;    
    for (i=0; i<hashmap->buckets->size; i++) {
        Vector *bucket = DArray_get(hashmap->buckets, i);
        if (bucket) {
            int j;
            for (j=0; j<bucket->size; j++) {
                HashMapNode *node = Vector_get(bucket, j);
                int bucket_index = HashMap_find_bucket_index(hashmap, node->key);
                Vector *bucket = DArray_get(new_buckets, bucket_index);
                if (!bucket) {
                    bucket = Vector_create(10);
                    Vector_add(bucket, node);
                    new_entries++;
                    DArray_set(new_buckets, bucket, bucket_index);
                } else {
                    int i;
                    for (i=0; i<bucket->size; i++) {
                        HashMapNode *in = Vector_get(bucket, i);
                        if (strcmp((char *)in->key, (char*)node->key)==0) {
                            Vector_set(bucket, node, i);
                            return;
                        }
                    }
                    Vector_add(bucket, node);
                    new_entries++;
                }
            }
        }
    }
    DArray_destroy(hashmap->buckets);
    hashmap->buckets = new_buckets;
    hashmap->entries = new_entries;
}

HashMap *
HashMap_create()
{
    HashMap *map = malloc(sizeof(HashMap));
    map->buckets = DArray_create(61);
    map->entries = 0;
    return map;
}

HashMap *
HashMap_deepCopy(HashMap *hashmap)
{
    HashMap *copy = HashMap_create();
    HashMapIterator *it = HashMap_getIterator(hashmap);
    HashMapNode *node;
    while ((node = HashMapIterator_getNext(it)) != NULL) {
        HashMap_put(copy, strdup(node->key), strdup((char *)node->value));
    }
    HashMapIterator_destroy(it);
    return copy;
}


void
HashMap_put(HashMap *hashmap, char *key, void *value)
{
    HashMapNode *node = malloc(sizeof(HashMapNode));
    node->key = key;
    node->value = value;
    if (hashmap->entries > 5)
        HashMap_resize(hashmap);

    int bucket_index = HashMap_find_bucket_index(hashmap, key);
    Vector *bucket = HashMap_find_bucket(hashmap, key);
    if (!bucket) {
        bucket = Vector_create(10);
        Vector_add(bucket, node);
        hashmap->entries++;
        DArray_set(hashmap->buckets, bucket, bucket_index);
    } else {
        int i;
        for (i=0; i<bucket->size; i++) {
            HashMapNode *in = Vector_get(bucket, i);
            if (strcmp((char *)in->key, (char*)node->key)==0) {
                Vector_set(bucket, node, i);
                return;
            }
        }
        Vector_add(bucket, node);
        hashmap->entries++;
    }
}

void
HashMap_remove(HashMap *hashmap, char *key)
{
    Vector *bucket = HashMap_find_bucket(hashmap, key);
    if (bucket) {
        int i;
        for (i=0; i<bucket->size; i++) {
            HashMapNode *in = Vector_get(bucket, i);
            if (strcmp((char *)in->key, key)==0) {
                Vector_remove(bucket, i);
                free(in);
                hashmap->entries--;
                return;
            }
        }
    }
}


int
HashMap_size(HashMap *hashmap)
{
    return HashMap_entries(hashmap);
}

int
HashMap_entries(HashMap *hashmap)
{
    return hashmap->entries;
}

int
HashMap_find_bucket_index(HashMap *hashmap, char *key)
{
    uint32_t hash_v;
    uint32_t seed = 42;	
    int len = strlen(key);
    MurmurHash3_x86_32(key, len, seed, &hash_v);
    int bucket_index = hash_v % hashmap->buckets->size;
    return bucket_index;
}

Vector *
HashMap_find_bucket(HashMap *hashmap, char *key)
{
    int bucket_index = HashMap_find_bucket_index(hashmap, key);
    Vector *bucket = DArray_get(hashmap->buckets, bucket_index);
    return bucket;
}

void *
HashMap_get(HashMap *hashmap, char *key)
{
    Vector *bucket = HashMap_find_bucket(hashmap, key);
    if (!bucket) {
        return NULL;
    }

    int i;
    for (i=0; i<bucket->size; i++) {
        HashMapNode *node = Vector_get(bucket, i);
        if (strcmp(node->key, key) == 0)
            return node->value;
    }    
     
    return NULL;
}

int
HashMap_containsKey(HashMap *hashmap, char *key)
{
	if (HashMap_get(hashmap, key) != NULL)
            return 1;

	return 0;
}

void
HashMap_destroy(HashMap *hashmap)
{
    int i;
    for (i=0; i<hashmap->buckets->size; i++) {
        Vector *c = DArray_get(hashmap->buckets, i);
        if (c) {
            int j;
            for (j=0; j<c->size;j++) {
                HashMapNode *node = Vector_remove(c, j);
                free(node);
            }
            Vector_destroy(c);
        }
    }

    DArray_destroy(hashmap->buckets);
    free(hashmap);
}

void
HashMap_iterate_k(HashMap *hashmap, void (*iterator)(void *key))
{
    int i;
    for (i=0; i<hashmap->buckets->size; i++) {
        Vector *bucket = DArray_get(hashmap->buckets, i);
        if (bucket) {
            int j;
            for (j=0; j<bucket->size; j++) {
                HashMapNode *node = Vector_get(bucket, j);
                iterator(node->key);
            }
        }
    }
}

void
HashMap_iterate_kv(HashMap *hashmap, void (*iterator)(void *key, void *value))
{
    int i;
    for (i=0; i<hashmap->buckets->size; i++) {
        Vector *bucket = DArray_get(hashmap->buckets, i);
        if (bucket) {
            int j;
            for (j=0; j<bucket->size; j++) {
                HashMapNode *node = Vector_get(bucket, j);
                iterator(node->key, node->value);
            }
        }
    }
}

HashMapIterator *
HashMap_getIterator(HashMap *hashmap)
{
    HashMapIterator *it = malloc(sizeof(HashMapIterator));
    it->map = hashmap;
    it->index = 0;
    it->bucket_index = 0;
    it->next = NULL;
    return it;
}

HashMapNode *
HashMapIterator_getNext(HashMapIterator *it)
{
    for (; it->index<it->map->buckets->size; it->index++) {
        Vector *bucket = DArray_get(it->map->buckets, it->index);
        if (bucket) {
            for (; it->bucket_index<bucket->size; it->bucket_index++) {
                HashMapNode *node = Vector_get(bucket, it->bucket_index);
                it->next = node;
                it->bucket_index++;
                return it->next;
            }
        }
        it->bucket_index=0;
    }
    return NULL;
}

void
HashMapIterator_reset(HashMapIterator *it)
{
    it->index = 0;
    it->bucket_index = 0;
    it->next = NULL;
}

void
HashMapIterator_destroy(HashMapIterator *it)
{
    free(it);
}
