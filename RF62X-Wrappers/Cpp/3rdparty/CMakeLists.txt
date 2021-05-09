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
# set rf627core path variable
set(RF62XCORE_DIR "../../../RF62X-Core")
# add subdirectory of rf627core lib
add_subdirectory(${RF62XCORE_DIR} RF62X-Core)
