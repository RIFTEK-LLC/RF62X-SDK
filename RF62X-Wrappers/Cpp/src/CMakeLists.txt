cmake_minimum_required(VERSION 3.13)



################################################################################
## LIBRARY-PROJECT
## name and version
################################################################################
project(RF62X-SDK VERSION 2.27.3 LANGUAGES CXX)



################################################################################
## SETTINGS
## basic project settings before use
################################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
file (GLOB_RECURSE IN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h.in)
configure_file(${IN_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/rf62Xversion.h)



################################################################################
## TARGET
## create target and add include path
################################################################################
# create glob files for *.h, *.cpp
file (GLOB_RECURSE H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})
# create lib from src
if (NOT TARGET ${PROJECT_NAME})
    SET(TARGET_OBJECTS_LIST
        $<TARGET_OBJECTS:RF62X-Core>
        $<TARGET_OBJECTS:RF62X-Protocol>
        $<TARGET_OBJECTS:mpack>
        $<TARGET_OBJECTS:sandbox>
        $<TARGET_OBJECTS:udpport>
        $<TARGET_OBJECTS:RF627-Protocol>
        $<TARGET_OBJECTS:custom_string>
        $<TARGET_OBJECTS:custom_vector>
        $<TARGET_OBJECTS:endian_conv>
        $<TARGET_OBJECTS:platform_methods>)
    if (MSVC)
        SET(TARGET_OBJECTS_LIST ${TARGET_OBJECTS_LIST}
            $<TARGET_OBJECTS:libpthreads4w>
            $<TARGET_OBJECTS:getopt>)
    endif()
    add_library(${PROJECT_NAME} STATIC ${SOURCES} ${TARGET_OBJECTS_LIST})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



################################################################################
## LINK LIBRARIES
## linking all dependencies
################################################################################
find_package (Threads)
target_link_libraries (${PROJECT_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${PROJECT_NAME} PRIVATE RF62X-Core)
target_link_libraries(${PROJECT_NAME} PUBLIC SettingsModel)
if(MINGW)
    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32)
    target_link_libraries(${PROJECT_NAME} PUBLIC iphlpapi)
endif(MINGW)
