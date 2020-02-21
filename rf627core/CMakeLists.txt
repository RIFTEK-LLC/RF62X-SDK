cmake_minimum_required(VERSION 3.10.2)


##
## PROJECT
## name and version
##
project(rf627core LANGUAGES C VERSION 1.1.0 DESCRIPTION "rf627core library" )


##
## CONFIGURATION
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD 99)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# create glob files for *.h, *.c
file(GLOB C_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/endian_conv/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_vector/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_string/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/platform_methods/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protocols/rf627protocol/*.c
    )
file(GLOB H_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/endian_conv/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_vector/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_string/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/platform_methods/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protocols/rf627protocol/*.h
    )
# concatenate the results (glob files) to variable
set  (SOURCES ${C_FILES} ${H_FILES})


##
## TARGET
## create target and add include path
##
add_library(${PROJECT_NAME} STATIC ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX  "")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/endian_conv/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_vector/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_string/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/platform_methods/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protocols/rf627protocol/
    )


##
## INSTALL
## install header files, generate .lib or .dll file.
##
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    COMPONENT developer
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/
    )

install(FILES ${H_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/include)
