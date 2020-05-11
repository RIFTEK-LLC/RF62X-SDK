find_package(Doxygen REQUIRED)

# set rf627sdk path variable
set(RF62XCORE_DIR "../rf62Xwrappers/Cpp/rf62Xsdk")
set(RF62XCORE_DIR "../rf62Xcore")

# Find all the public headers
file(GLOB RF62X_CORE_HEADERS ${RF62XCORE_DIR}/src/*.h)
set (HEADERS ${RF62X_CORE_HEADERS})

message( ${HEADERS} )

#This will be the main output of our command
set(DOXYGEN_INDEX_FILE ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html)

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source_ru
                   MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/source_ru/Doxyfile
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
