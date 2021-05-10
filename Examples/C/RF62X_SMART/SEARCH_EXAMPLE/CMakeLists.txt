cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(RF62XSmartSearchExample LANGUAGES C)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################
#3rdparty
add_subdirectory(3rdparty)
#src
add_subdirectory(src)
