#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_CAP 640000
#define CHUNK_LIST_CAP 1024

#define NOT_IMPLEMENTED                                                        \
    do                                                                         \
    {                                                                          \
        fprintf(                                                               \
            stderr, "%s:%d: TODO: %s is not implemented yet\n", __FILE__,      \
            __LINE__, __func__                                                 \
        );                                                                     \
        abort();                                                               \
    } while (0)

typedef struct
{
    char* start;
    size_t size;
} Chunk;

typedef struct
{
    size_t count;
    Chunk chunks[CHUNK_LIST_CAP];
} Chunk_List;

void chunk_list_dump(const Chunk_List* list)
{
    printf("Chunks (%zu):\n", list->count);

    for (size_t i = 0; i < list->count; ++i)
    {
        printf(
            "  start: %p, size: %zu\n", list->chunks[i].start,
            list->chunks[i].size
        );
    }
}

int chunk_start_compar(const void* a, const void* b)
{
    const Chunk* a_chunk = a;
    const Chunk* b_chunk = b;

    return a_chunk->start - b_chunk->start;
}

int chunk_list_find(const Chunk_List* list, void* start)
{
    Chunk key = {.start = start};

    Chunk* result = bsearch(
        &key, list->chunks, list->count, sizeof(list->chunks[0]),
        chunk_start_compar
    );

    if (result != 0)
    {
        assert(list->chunks <= result);
        return (result - list->chunks) / sizeof(list->chunks[0]);
    }
    else
    {
        return -1;
    }
}

void chunk_list_insert(Chunk_List* list, void* start, size_t size)
{
    assert(list->count < CHUNK_LIST_CAP);
    list->chunks[list->count].start = start;
    list->chunks[list->count].size = size;

    for (size_t i = list->count;
         i > 0 && list->chunks[i].start < list->chunks[i - 1].start; --i)
    {
        const Chunk t = list->chunks[i];
        list->chunks[i] = list->chunks[i - 1];
        list->chunks[i - 1] = t;
    }

    list->count += 1;
}

void chunk_list_remove(Chunk_List* list, size_t index)
{
    (void)list;
    (void)index;

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
    void* start = heap + heap_size;
    heap_size += size;

    chunk_list_insert(&alloced_chunks, start, size);

    return start;
}

void heap_free(void* start)
{
    if (start == NULL)
    {
        return;
    };

    const int index = chunk_list_find(&alloced_chunks, start);
    assert(index >= 0);

    chunk_list_insert(
        &freed_chunks, alloced_chunks.chunks[index].start,
        alloced_chunks.chunks[index].size
    );
    chunk_list_remove(&alloced_chunks, (size_t)index);
}

void heap_collect() { NOT_IMPLEMENTED; }

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        void* p = heap_alloc(i);
        if (i % 2 == 0)
        {
            heap_free(p);
        }
    }

    chunk_list_dump(&alloced_chunks);

    return 0;
}
