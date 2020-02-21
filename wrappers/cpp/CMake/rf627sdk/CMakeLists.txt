cmake_minimum_required(VERSION 3.5)


##
## PROJECT
## name and version
##
project(rf627sdk VERSION 1.0.1 LANGUAGES CXX)


##
## CONFIGURATION
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# set rf627core path variable
set(RF627CORE_DIR "../../../../rf627core")

# add subdirectory of rf627core lib
add_subdirectory(${RF627CORE_DIR} CMAKE_CURRENT_SOURCE_DIR)

# create glob files for *.h, *.cpp
file (GLOB H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})


##
## TARGET
## create target and add include path
##
add_library(${PROJECT_NAME} STATIC ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX  "")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    )

target_link_libraries(${PROJECT_NAME} rf627core)
if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif(MINGW)
target_link_libraries(${PROJECT_NAME} iphlpapi)


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
