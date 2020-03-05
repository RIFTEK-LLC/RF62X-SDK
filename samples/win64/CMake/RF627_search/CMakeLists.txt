cmake_minimum_required(VERSION 3.5)


##
## PROJECT
## name and version
##
project(RF627_search LANGUAGES CXX)


##
## CONFIGURATION
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set rf627sdk path variable
set(RF62XSDK_DIR "../../../../wrappers/cpp/CMake/rf62Xsdk")
# add subdirectory of rf627sdk lib
add_subdirectory(${RF62XSDK_DIR} CMAKE_CURRENT_SOURCE_DIR)

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

target_link_libraries(${PROJECT_NAME} rf62Xsdk)

