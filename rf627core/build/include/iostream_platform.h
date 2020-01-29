#ifndef IOSTREAM_PLATFORM_H
#define IOSTREAM_PLATFORM_H
#include "platform_types.h"

/** @brief Method for outputting debugging information
 */
typedef rfInt(*trace_info_t)(const rfChar* msg, ...);


/** @brief Method for outputting alert information
 */
typedef rfInt(*trace_warning_t)(const rfChar* msg, ...);


/** @brief Method for outputting error information
 */
typedef rfInt(*trace_error_t)(const rfChar* msg, ...);

/** @brief Structure with user-provided platform-specific methods
 */
typedef struct
{
    trace_info_t trace_info;
    trace_warning_t trace_warning;
    trace_error_t trace_error;
}iostream_platform_dependent_methods_t;
extern iostream_platform_dependent_methods_t iostream_platform;

/**
 * @brief init_iostream_platform - function for init iostream
 * @param methods
 */
void init_iostream_platform(iostream_platform_dependent_methods_t* methods);

#endif //IOSTREAM_PLATFORM_H
