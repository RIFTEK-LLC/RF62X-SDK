cmake_minimum_required(VERSION 3.13)



################################################################################
## PROJECT
## name and version
################################################################################
project(RF62X-SDK LANGUAGES CXX)



################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
################################################################################
add_subdirectory(3rdparty)
add_subdirectory(src)

