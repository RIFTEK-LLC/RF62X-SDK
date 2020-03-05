#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include "platform_types.h"

typedef struct vector_ {
    void** data;
    rfSize size;
    rfSize count;
} vector_t;

/**
 * @brief vector_init - The vector type used in this library
 */
void vector_init(vector_t** vec);

/**
 * @brief vector_count - get count of vectors elements
 */
rfSize vector_count(vector_t* vec);

/**
 * @brief vector_add - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
void vector_add(vector_t* vec, void* value);

/**
 * @brief vector_set - set an element to the vector by id
 * @param vec - the vecto
 * @param i - index of element to set
 * @param value - the value to add
 * @return void
 */
void vector_set(vector_t* vec, rfSize i, void* value);

/**
 * @brief vector_get - get an element from the vector by id
 * @param vec - the vecto
 * @param i - index of element to set
 * @return a pointer to the element (or NULL)
 */
void* vector_get(vector_t* vec, rfSize i);

/**
 * @brief vector_empty - returns non-zero if the vector is empty
 * @param vec - the vector
 * @return non-zero if empty, zero if non-empty
 */
rfSize vector_empty(vector_t* vec);

/**
 * @brief vector_delete - removes the element at index i from the vector
 * @param vec - the vector
 * @param i - index of element to remove
 * @return void
 */
void vector_delete(vector_t* vec, rfSize i);

/**
 * @brief vector_free - frees all memory associated with the vector
 * @param vec - the vector
 * @return void
 */
void vector_free(vector_t* vec);

/**
 * @brief vector_begin - returns an iterator to first element of the vector
 * @param vec - the vector
 * @return a pointer to the first element (or NULL)
 */
void* vector_begin(vector_t* vec);

/**
 * @brief vector_end - returns an iterator to one past the last element of the vector
 * @param vec - the vector
 * @return a pointer to one past the last element (or NULL)
 */
void* vector_end(vector_t* vec);



#endif // CUSTOM_VECTOR_H
