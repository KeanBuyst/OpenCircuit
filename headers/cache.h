#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Cache {
    void* data;
    size_t size;
    size_t capacity;
    size_t elem_size;
} Cache;

Cache CacheInit(size_t capacity,size_t elem_size);
void CacheAdd(Cache* cache,void* element);
void CacheFree(Cache* cache);
void* CacheGet(Cache* cache,size_t index);