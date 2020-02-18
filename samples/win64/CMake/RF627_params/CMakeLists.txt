cmake_minimum_required(VERSION 3.5)

project(RF627_params LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(RF627SDK_DIR "D:/Work/C/rf627sdk/wrappers/cpp/CMake/rf627sdk/build/")
set(RF627CORE_DIR "D:/Work/C/rf627sdk/rf627core/build/")

# include *.h rf627sdk files from directory
include_directories("${RF627SDK_DIR}/include")

SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")

# find rf627sdk lib in paths and copy full file name to RF627SDK_LIBRARY
find_library(
    RF627SDK_LIBRARY
    rf627sdk
    PATHS ${RF627SDK_DIR}/bin/MinGW_64
    )
# find rf627core lib in paths and copy full file name to RF627SDK_LIBRARY
find_library(
    RF627CORE_LIBRARY
    rf627core
    PATHS ${RF627SDK_DIR}/bin/MinGW_64
    )

message(STATUS "TEST library = [" ${RF627SDK_LIBRARY} "]")

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_executable(${PROJECT_NAME} ${SOURCES})

# copy rf627sdk lib from directory to project build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${RF627SDK_LIBRARY} ${PROJECT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${RF627CORE_LIBRARY} ${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${RF627SDK_LIBRARY})
if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif(MINGW)
target_link_libraries(${PROJECT_NAME} iphlpapi)
