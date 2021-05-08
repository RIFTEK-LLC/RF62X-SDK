cmake_minimum_required(VERSION 3.13)



###############################################################################
## 3RD-PARTY
## dependencies for the project
###############################################################################
project(3rdparty LANGUAGES C)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
###############################################################################
# set rf627core path variable
set(RF62XCORE_DIR "../../../../rf62Xcore")
add_subdirectory(${RF62XCORE_DIR} rf62Xcore)
