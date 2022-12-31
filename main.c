#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define HEAP_CAP 640000
#define HEAP_ALLOCED_CAP 1024

typedef struct
{
    void* start;
    size_t size;
} Heap_Chunk;

char heap[HEAP_CAP] = {0};
size_t heap_size = 0;

Heap_Chunk heap_alloced[HEAP_ALLOCED_CAP] = {0};
size_t heap_alloced_size = 0;

void* heap_alloc(size_t size)
{

    if (size <= 0)
    {
        return NULL;
    };

    assert(heap_size + size <= HEAP_CAP);
    void* result = heap + heap_size;
    heap_size += size;

    const Heap_Chunk chunk = {
        .start = result,
        .size = size,
    };
    assert(heap_alloced_size < HEAP_ALLOCED_CAP);
    heap_alloced[heap_alloced_size++] = chunk;

    return result;
}

void heap_dump_alloced_chunks(void)
{
    printf("Allocated Chunks (%zu):\n", heap_alloced_size);

    for (size_t i = 0; i < heap_alloced_size; ++i)
    {
        printf(
            "  start: %p, size: %zu\n", heap_alloced[i].start,
            heap_alloced[i].size
        );
    }
}

void heap_free(void* ptr)
{
    assert(false && "TODO: heap_free is not implemented");
    (void)ptr;
}

void heap_collect()
{
    assert(false && "TODO: heap_collect is not implemented");
}

int main()
{
    for (int i = 0; i < 100; ++i)
    {
        heap_alloc(i);
    }

    heap_dump_alloced_chunks();

    return 0;
}
