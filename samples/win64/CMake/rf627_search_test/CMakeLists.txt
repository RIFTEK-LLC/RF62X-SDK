cmake_minimum_required(VERSION 3.5)

project(rf627_search_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories("${RF627SDK_DIR}/include")
if(MINGW)
link_directories(${PROJECT_NAME} ${RF627SDK_DIR}/bin/MinGW_64)
elseif(MSVC)
link_directories(${PROJECT_NAME} ${RF627SDK_DIR}/lib/MinGW_64)
endif(MINGW)

file(GLOB SOURCES *.h *.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RF627SDK_DIR}/bin/MinGW_64/"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

target_link_libraries(${PROJECT_NAME} rf627core)
if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif(MINGW)
target_link_libraries(${PROJECT_NAME} iphlpapi)




