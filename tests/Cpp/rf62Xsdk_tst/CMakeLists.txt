cmake_minimum_required(VERSION 3.5)


##
## PROJECT
## name and version
##
project(rf62Xsdk_tst LANGUAGES CXX)


##
## CONFIGURATION
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create glob files for *.h, *.cpp
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
# concatenate the results (glob files) to variable
set(SOURCES ${TEST_SOURCES})


##
## TARGET
## create target and add include path
##
add_executable(${PROJECT_NAME} ${TEST_SOURCES})
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} rf62Xsdk)
target_link_libraries(${PROJECT_NAME} gtest)



