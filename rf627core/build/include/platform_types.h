#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H
#include <stdint.h>


/** @brief	Определения типов данных
 */
#ifndef NULL
#define NULL        ((void *)0) // NULL
#endif

typedef int8_t		rfInt8;		// 8-bit signed number
typedef int16_t		rfInt16;	// 16-bit signed number
typedef int32_t		rfInt32;	// 32-bit signed number

typedef uint8_t		rfUint8;	// 8-bit unsigned number
typedef uint16_t	rfUint16;	// 16-bit unsigned number
typedef uint32_t	rfUint32;	// 32-bit unsigned number

typedef char		rfChar;		// 8-bit signed number
typedef uint8_t		rfByte;		// 8-bit bit string
typedef uint8_t		rfBool;     // bool data types
typedef size_t      rfSize;     // size_t
typedef ssize_t     rfSsize;    // ssize_t
typedef int         rfInt;      // int
typedef float		rfFloat;	// IEEE 754 32-bit floating point number
typedef double		rfDouble;	// IEEE 754 64-bit floating point number

#define _SUPPORT_64BIT_DATATYPES
#ifdef _SUPPORT_64BIT_DATATYPES
typedef int64_t		rfInt64;	// 64-bit signed number
typedef uint64_t	rfUint64;	// 64-bit unsigned number
#endif /* _SUPPORT_64BIT_DATATYPES */


#endif //PLATFORM_TYPES_H
