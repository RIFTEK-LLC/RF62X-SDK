cmake_minimum_required(VERSION 3.13)



###############################################################################
## 3RD-PARTY
## dependencies for the project
###############################################################################
project(3rdparty LANGUAGES C)



###############################################################################
## SETTINGS
## basic 3rd-party settings before use
###############################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_RF62XCORE_3RDPARTY_)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)



###############################################################################
## CONFIGURATION
## 3rd-party submodules configuration
###############################################################################
SET(${PARENT}_SMART_PROTOCOL                            ON CACHE BOOL "" FORCE)
if (${PARENT}_SMART_PROTOCOL)
    # library src
    SET(${PARENT}_SMART_PROTOCOL_LIB                    ON CACHE BOOL "" FORCE)
    # Examples
    SET(${PARENT}_SMART_PROTOCOL_EXAMPLES               OFF CACHE BOOL  "" FORCE)
endif()


###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
###############################################################################
SET(PROTOCOL_OLD "protocols/rf627protocol/")
SET(CUSTOM_STRING "utils/custom_string/")
SET(CUSTOM_VECTOR "utils/custom_vector/")
SET(ENDIAN_CONV "utils/endian_conv/")
SET(PLATFORM_METHODS "utils/platform_methods/")

if(${PARENT}_SMART_PROTOCOL)
    SET(PROTOCOL_SMART "protocols/smart-protocol/")
    add_subdirectory(${PROTOCOL_SMART} smart-protocol)
endif()

add_subdirectory(${PROTOCOL_OLD} rf627protocol)
add_subdirectory(${CUSTOM_STRING} custom_string)
add_subdirectory(${CUSTOM_VECTOR} custom_vector)
add_subdirectory(${ENDIAN_CONV} endian_conv)
add_subdirectory(${PLATFORM_METHODS} platform_methods)

