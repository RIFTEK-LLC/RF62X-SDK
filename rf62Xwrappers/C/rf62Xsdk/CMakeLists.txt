cmake_minimum_required(VERSION 3.5)


##
## PROJECT
## name and version
##
project(rf62Xsdk VERSION 1.0.1 LANGUAGES CXX C)


##
## CONFIGURATION
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD 99)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

# set rf627core path variable
set(RF62XCORE_DIR "../../../rf62Xcore")


# create glob files for *.h, *.cpp
file (GLOB_RECURSE H_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
      ${RF62XCORE_DIR}/*.h
      )

file (GLOB_RECURSE CPP_FILES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
     ${RF62XCORE_DIR}/*.c
     )
# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})


##
## TARGET
## create target and add include path
##
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX  "")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${RF62XCORE_DIR}/src/
    ${RF62XCORE_DIR}/3rdparty/utils/endian_conv/
    ${RF62XCORE_DIR}/3rdparty/utils/custom_vector/
    ${RF62XCORE_DIR}/3rdparty/utils/custom_string/
    ${RF62XCORE_DIR}/3rdparty/utils/platform_methods/
    ${RF62XCORE_DIR}/3rdparty/protocols/rf627protocol/
    )

if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
    target_link_libraries(${PROJECT_NAME} iphlpapi)
endif(MINGW)

##
## INSTALL
## install header files, generate .lib or .dll file.
##
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/
    CONFIGURATIONS DEBUG|RELEASE
    )
install(FILES ${H_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/include)
