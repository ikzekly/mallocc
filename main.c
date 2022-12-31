#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_CAP 640000
#define HEAP_ALLOCED_CAP 1024
#define HEAP_FREED_CAP 1024

#define NOT_IMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: TODO: %s is not implemented yet\n", __FILE__, __LINE__, __func__); \
        abort(); \
    } while(0)

typedef struct
{
    void* start;
    size_t size;
} Chunk;

typedef struct
{
    size_t count;
    Chunk chunks[HEAP_ALLOCED_CAP];
} Chunk_List;

void chunk_list_dump(const Chunk_List *list)
{
    printf("Chunks (%zu):\n", list->count);

    for (size_t i = 0; i < list->count; ++i)
    {
        printf(
            "  start: %p, size: %zu\n",
	    list->chunks[i].start,
            list->chunks[i].size
        );
    }
}

int chunk_list_find(const Chunk_List *list, void* ptr)
{
    (void) list;
    (void) ptr;

    NOT_IMPLEMENTED;
    return -1;
}

void chunk_list_insert(const Chunk_List *list, void* ptr, size_t size)
{
    (void) list;
    (void) ptr;
    (void) size;

    NOT_IMPLEMENTED;
}

void chunk_list_remove(Chunk_List *list, size_t index)
{
    (void) list;
    (void) index;

    NOT_IMPLEMENTED;
}

char heap[HEAP_CAP] = {0};
size_t heap_size = 0;

Chunk_List alloced_chunks = {0};
Chunk_List freed_chunks = {0};

void* heap_alloc(size_t size)
{

    if (size <= 0)
    {
        return NULL;
    };

    assert(heap_size + size <= HEAP_CAP);
    void* ptr = heap + heap_size;
    heap_size += size;

    chunk_list_insert(&alloced_chunks, ptr, size);

    return ptr;
}

void heap_free(void* ptr)
{
    (void) ptr;

    NOT_IMPLEMENTED;
}

void heap_collect()
{
    NOT_IMPLEMENTED;
}

int main()
{
    for (int i = 0; i < 100; ++i)
    {
        void* p = heap_alloc(i);

        if (i % 2 == 0)
        {
            heap_free(p);
        }
    }

    return 0;
}
