cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(RF62XSDK-EXAMPLES LANGUAGES CXX)



###############################################################################
## CONFIGURATION
## project configuration
###############################################################################
# Enable examples for rf62X scanners v2.x.x
SET(RF62X_SMART_EXAMPLES                                ON CACHE BOOL "" FORCE)
# Enable examples for rf627 scanners v1.x.x
SET(RF627_OLD_EXAMPLES                                  OFF CACHE BOOL "" FORCE)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################
if (RF62X_SMART_EXAMPLES)
    add_subdirectory(RF62X_SMART)
endif()
if (RF627_OLD_EXAMPLES)
    add_subdirectory(RF627_OLD)
endif()

