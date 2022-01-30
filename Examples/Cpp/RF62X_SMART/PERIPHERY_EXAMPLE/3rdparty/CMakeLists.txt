cmake_minimum_required(VERSION 3.13)



###############################################################################
## 3RD-PARTY
## dependencies for the project
###############################################################################
project(3rdparty LANGUAGES CXX)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
###############################################################################
# set rf627sdk path variable
set(RF62XSDK_DIR "../../../../../RF62X-Wrappers/Cpp")
# add subdirectory of rf627sdk lib
add_subdirectory(${RF62XSDK_DIR} RF62X-SDK)

