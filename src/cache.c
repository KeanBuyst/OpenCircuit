#include "cache.h"

// Initializes a new cache with the specified capacity and element size
Cache CacheInit(size_t capacity, size_t elem_size) {
    Cache cache;
    cache.data = malloc(capacity * elem_size);
    if (cache.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    cache.size = 0;
    cache.capacity = capacity;
    cache.elem_size = elem_size;
    return cache;
}

// Adds an element to the cache
void CacheAdd(Cache* cache, void* element) {
    if (cache->size == cache->capacity) {
        cache->capacity *= 2;
        void* new_data = realloc(cache->data, cache->capacity * cache->elem_size);
        if (new_data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        cache->data = new_data;
    }
    memcpy((char*)cache->data + cache->size * cache->elem_size, element, cache->elem_size);
    cache->size++;
}

// Frees the memory allocated for the cache
void CacheFree(Cache* cache) {
    free(cache->data);
    cache->data = NULL;
    cache->size = 0;
    cache->capacity = 0;
    cache->elem_size = 0;
}

void* CacheGet(Cache* cache,size_t index){
    return cache->data + index * cache->elem_size;
}