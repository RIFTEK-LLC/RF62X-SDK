cmake_minimum_required(VERSION 3.5)


##
## PROJECT
## name and version
##
project(RF627_TESTS LANGUAGES CXX)


##
## CONFIGURATION
##
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

# set rf627sdk path variable
set(RF62XSDK_DIR "../../../rf62Xsdk/Cpp/rf62Xsdk")

# add subdirectory of rf627sdk lib
add_subdirectory(${RF62XSDK_DIR} rf62Xsdk)

# add subdirectories of examples
add_subdirectory(RF627_search)
add_subdirectory(RF627_profile)
add_subdirectory(RF627_params)


