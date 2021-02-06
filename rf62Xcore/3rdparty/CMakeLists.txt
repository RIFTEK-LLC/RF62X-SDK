cmake_minimum_required(VERSION 3.13)



###############################################################################
## 3RD-PARTY
## dependencies for the project
###############################################################################
project(3rdparty LANGUAGES C)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
###############################################################################
SET(PROTOCOL_OLD "protocols/rf627protocol/")
SET(PROTOCOL_SMART "protocols/smart-protocol/")
SET(CUSTOM_STRING "utils/custom_string/")
SET(CUSTOM_VECTOR "utils/custom_vector/")
SET(ENDIAN_CONV "utils/endian_conv/")
SET(PLATFORM_METHODS "utils/platform_methods/")

add_subdirectory(${PROTOCOL_OLD} rf627protocol)
add_subdirectory(${PROTOCOL_SMART} smart-protocol)
add_subdirectory(${CUSTOM_STRING} custom_string)
add_subdirectory(${CUSTOM_VECTOR} custom_vector)
add_subdirectory(${ENDIAN_CONV} endian_conv)
add_subdirectory(${PLATFORM_METHODS} platform_methods)

