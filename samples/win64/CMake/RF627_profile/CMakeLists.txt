cmake_minimum_required(VERSION 3.5)


##
## PROJECT
## name and version
##
project(RF627_profile LANGUAGES CXX)


##
## CONFIGURATION
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# set rf627sdk path variable
set(RF627SDK_DIR "../../../../wrappers/cpp/CMake/rf627sdk")
# set rf627core path variable
set(RF627CORE_DIR "../../../../rf627core")
# add subdirectory of rf627sdk lib
add_subdirectory(${RF627SDK_DIR} CMAKE_CURRENT_SOURCE_DIR)


# create glob files for *.h, *.cpp
file (GLOB H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})


##
## TARGET
## create target and add include path
##
add_executable(${PROJECT_NAME} ${SOURCES})

# find rf627sdk lib in paths and copy full file name to RF627SDK_LIBRARY
find_library(
    RF627SDK_LIBRARY
    rf627sdk
    PATHS ${RF627SDK_DIR}/build/bin/MinGW_64
    )
# find rf627core lib in paths and copy full file name to RF627SDK_LIBRARY
find_library(
    RF627CORE_LIBRARY
    rf627core
    PATHS ${RF627CORE_DIR}/build/bin/MinGW_64
    )

# copy rf627sdk lib from directory to project build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${RF627SDK_LIBRARY} ${PROJECT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${RF627CORE_LIBRARY} ${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} rf627sdk)
if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif(MINGW)
target_link_libraries(${PROJECT_NAME} iphlpapi)
