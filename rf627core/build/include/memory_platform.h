#ifndef MEMORY_PLATFORM_H
#define MEMORY_PLATFORM_H
#include "platform_types.h"

/** @brief Allocates an array in memory with elements initialized to 0.
 *
 * @param num - number of elements to allocate.
 * @param size - size of each element.
 * @return
 * - On success: returns a pointer to the allocated space.
 * - On error: NULL
 */
typedef void* (*calloc_t)(rfSize num, rfSize size);

/**
 * @brief malloc_t - ptr to function whish allocates memory block
 * Allocates a block of size bytes of memory, returning a pointer
 * to the beginning of the block.
 * @param size - Size of the memory block, in bytes.
 * @return On success, a pointer to the memory block allocated by the function.
 * If the function failed to allocate the requested block of memory, a null
 * pointer is returned.
 */
typedef void* (*malloc_t)(rfSize size);

/**
 * @brief realloc_t - ptr to function whish reallocates memory block
 * Changes the size of the memory block pointed to by ptr. The function may move
 * the memory block to a new location (whose address is returned by the function).
 * @param ptr - Pointer to a memory block previously allocated.
 * @param newsize - New size for the memory block, in bytes.
 * @return A pointer to the reallocated memory block, which may be either the
 * same as ptr or a new location.
 */
typedef void* (*realloc_t)(void *ptr, rfSize newsize);

/** @brief Deallocates or frees a memory block.
 *
 * @param data - Previously allocated memory block to be freed.
 */
typedef void (*free_t)(void* data);

/**
 * @brief memset_t - ptr to function whish fills block of memory
 * Sets the first num bytes of the block of memory pointed by ptr to the
 * specified value (interpreted as an unsigned rfChar).
 * @param memptr - Pointer to the block of memory to fill.
 * @param val - Value to be set.
 * @param num - Number of bytes to be set to the value.
 *              rfSize is an unsigned rfIntegral type.
 * @return ptr is returned.
 */
typedef void* (*memset_t)(void* memptr, rfInt val, rfSize num);
/**
 * @brief memcpy_t - ptr to function whish copies block of memory
 * Copies the values of num bytes from the location pointed to by source
 * directly to the memory block pointed to by destination.
 * @param destination - Pointer to the destination array where the content is to
 *                      be copied, type-casted to a pointer of type void*.
 * @param source - Pointer to the source of data to be copied, type-casted to a
 *                 pointer of type const void*.
 * @param num - Number of bytes to copy. rfSize is an unsigned rfIntegral type.
 * @return destination is returned.
 */
typedef void* (*memcpy_t)(void* destination, const void* source, rfSize num);

/**
 * @brief memcmp_t - ptr to function whish compare two blocks of memory
 * Compares the first num bytes of the block of memory pointed by ptr1 to the
 * first num bytes pointed by ptr2, returning zero if they all match or a value
 * different from zero representing which is greater if they do not.
 * @param ptr1 - Pointer to block of memory.
 * @param ptr2 - Pointer to block of memory.
 * @param num - Number of bytes to compare.
 * @return  0 - if the contents of both memory blocks are equal,
 *         <0 - if the first byte that does not match in both memory blocks has
 * a lower value in ptr1 than in ptr2.
 *         >0 - if the first byte that does not match in both memory blocks has
 * a greater value in ptr1 than in ptr2.
 */
typedef rfInt (*memcmp_t)(const void * ptr1, const void * ptr2, rfSize num );


/** @brief Structure with user-provided platform-specific methods
 */
typedef struct
{
    calloc_t rf_calloc;
    malloc_t rf_malloc;
    realloc_t rf_realloc;
    free_t rf_free;

    memset_t rf_memset;
    memcpy_t rf_memcpy;
    memcmp_t rf_memcmp;

}memory_platform_dependent_methods_t;
extern memory_platform_dependent_methods_t memory_platform;

/**
 * @brief init_memory_platform - function for init memmory
 * @param methods
 */
void init_memory_platform(memory_platform_dependent_methods_t* methods);

#endif //MEMORY_PLATFORM_H
