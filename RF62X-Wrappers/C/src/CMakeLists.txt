cmake_minimum_required(VERSION 3.13)



###############################################################################
## LIBRARY-PROJECT
## name and version
###############################################################################
project(RF62X-SDK VERSION 2.7.3 LANGUAGES C)



###############################################################################
## SETTINGS
## basic project settings before use
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD 99)
# Enabling export of all symbols to create a dynamic library
set(ENABLE_EXPORTS 1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")



###############################################################################
## TARGET
## create target and add include path
###############################################################################
# create glob files for *.h, *.c
file (GLOB_RECURSE H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB_RECURSE C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
# concatenate the results (glob files) to variable
set  (SOURCES ${C_FILES} ${H_FILES})
# create lib from src
if (NOT TARGET ${PROJECT_NAME})
    SET(TARGET_OBJECTS_LIST
        $<TARGET_OBJECTS:RF62X-Core>
        $<TARGET_OBJECTS:RF62X-Protocol>
        $<TARGET_OBJECTS:mpack>
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
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)



###############################################################################
## LINK LIBRARIES
## linking all dependencies
###############################################################################
find_package (Threads)
target_link_libraries (${PROJECT_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${PROJECT_NAME} PUBLIC RF62X-Core)
if(MINGW)
    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32)
    target_link_libraries(${PROJECT_NAME} PUBLIC iphlpapi)
endif(MINGW)


