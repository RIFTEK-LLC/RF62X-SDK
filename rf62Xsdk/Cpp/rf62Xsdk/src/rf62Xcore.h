#pragma once

#include"rf62Xtypes.h"

#include <vector>
#include <memory>

#if (defined _WIN32 && defined RF627_LIBRARY)
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif

namespace SDK {
namespace CORES {
namespace RF62X {


/**
 * @brief version - Return info about CORE version
 * @return SDK version
 */
API_EXPORT std::string version();

/**
 * @brief init - Initialize CORE library
 * Must be called once before further calls to any library functions
 * @return true if success.
 */
API_EXPORT bool init();

/**
 * @brief cleanup - Cleanup resources allocated with core_init() function
 */
API_EXPORT void cleanup();

}
}
}
