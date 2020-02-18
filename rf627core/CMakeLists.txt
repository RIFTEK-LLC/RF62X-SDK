cmake_minimum_required(VERSION 3.10.2)

project(rf627core LANGUAGES C CXX VERSION 1.0.1 DESCRIPTION "rf627sdk win64-mingw dll" )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD 99)

# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_vector/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_vector/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_string/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_string/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/platform_methods/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/platform_methods/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/endian_conv/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/endian_conv/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protocols/rf627protocol/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protocols/rf627protocol/*.c
    )

file(GLOB HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_vector/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_string/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/platform_methods/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/endian_conv/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protocols/rf627protocol/*.h
    )


add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX  "")
#if(CMAKE_SIZEOF_VOID_P EQUAL 4)
#    set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX "_x32")
#    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_x32d")
#else()
#    set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX "_x64")
#    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_x64d")
#endif()


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_vector/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/custom_string/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/platform_methods/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utils/endian_conv/
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protocols/rf627protocol/
    )


if(MINGW AND (CMAKE_SIZEOF_VOID_P EQUAL 4))
    set(RUNTIME_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/MinGW_32)
    set(LIBRARY_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/MinGW_32)
elseif(MINGW AND NOT (CMAKE_SIZEOF_VOID_P EQUAL 4))
    set(RUNTIME_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/MinGW_64)
    set(LIBRARY_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/MinGW_64)
elseif(MSVC14 AND (CMAKE_SIZEOF_VOID_P EQUAL 4))
    set(RUNTIME_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/MSVC14_32)
    set(LIBRARY_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/MSVC14_32)
elseif(MSVC14 AND NOT (CMAKE_SIZEOF_VOID_P EQUAL 4))
    set(RUNTIME_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/MSVC14_64)
    set(LIBRARY_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/MSVC14_64)
endif(MINGW AND (CMAKE_SIZEOF_VOID_P EQUAL 4))

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    COMPONENT developer
    RUNTIME DESTINATION ${RUNTIME_DESTINATION}
    LIBRARY DESTINATION ${LIBRARY_DESTINATION}
    )

install(FILES ${HEADERS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/include)
