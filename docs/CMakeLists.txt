find_package(Doxygen REQUIRED)

##
## PROJECT
## name and version
##
project(Docs LANGUAGES CXX)


# set rf627sdk path variable
set(RF62XCORE_DIR "../rf62Xcore")
set(RF62XSDK_DIR "../rf62Xwrappers")

# Find all the public headers
file(GLOB_RECURSE RF62X_CORE_HEADERS
    ${RF62XSDK_DIR}/*.cs
    ${RF62XCORE_DIR}/*.h
    ${RF62XSDK_DIR}/*.h
    )

set(DOXYGEN_INPUT_CORE_DIR ${RF62XCORE_DIR})
set(DOXYGEN_INPUT_SDK_DIR ${RF62XSDK_DIR})
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/source_ru/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_SOURCE_DIR}/source_ru/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${RF62X_CORE_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})


# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

find_package(Sphinx REQUIRED)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/source_ru)
set(SPHINX_BUILD ${CMAKE_CURRENT_SOURCE_DIR}/build/sphinx)

add_custom_target(Sphinx_html ALL
                  COMMAND ${SPHINX_EXECUTABLE} -b html
                  # Tell Breathe where to find the Doxygen output
                  -Dbreathe_projects.rf62Xcore=${DOXYGEN_OUTPUT_DIR}/xml/
                  ${SPHINX_SOURCE} ${SPHINX_BUILD}_html
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT "Generating documentation with Sphinx")

add_custom_target(Sphinx_latex ALL
                  COMMAND ${SPHINX_EXECUTABLE} -b latex
                  # Tell Breathe where to find the Doxygen output
                  -Dbreathe_projects.rf62Xcore=${DOXYGEN_OUTPUT_DIR}/xml/
                  ${SPHINX_SOURCE} ${SPHINX_BUILD}_latex
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT "Generating documentation with Sphinx")
