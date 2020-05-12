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

# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")


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

# set rf627sdk path variable
set(RF62XSDK_DIR "../../../../rf62Xwrappers/Cpp/rf62Xsdk")
# add subdirectory of rf627sdk lib
add_subdirectory(${RF62XSDK_DIR} rf62Xsdk)
target_link_libraries(${PROJECT_NAME} rf62Xsdk)

