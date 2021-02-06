cmake_minimum_required(VERSION 3.13)



###############################################################################
## EXECUTABLE-PROJECT
## name and version
###############################################################################
project(RF62X_search LANGUAGES C)



###############################################################################
## SETTINGS
## basic project settings before use
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD 99)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")



###############################################################################
## TARGET
## create target and add include path
###############################################################################
# create glob files for *.h, *.cpp
file (GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
# concatenate the results (glob files) to variable
set  (SOURCES ${C_FILES} ${H_FILES})
# create executable from src
add_executable(${PROJECT_NAME} ${SOURCES})



###############################################################################
## LINK LIBRARIES
## linking all dependencies
###############################################################################
target_link_libraries(${PROJECT_NAME} rf62Xsdk)

