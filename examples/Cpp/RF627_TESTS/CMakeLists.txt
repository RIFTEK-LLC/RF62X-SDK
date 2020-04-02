cmake_minimum_required(VERSION 3.5)


##
## PROJECT
## name and version
##
project(RF627_TESTS LANGUAGES CXX)


# set rf627sdk path variable
set(RF62XSDK_DIR "../../../wrappers/Cpp/rf62Xsdk")
# add subdirectory of rf627sdk lib
add_subdirectory(${RF62XSDK_DIR} 3rdparty)

# add subdirectories of examples
add_subdirectory(RF627_search)
add_subdirectory(RF627_profile)
add_subdirectory(RF627_params)


