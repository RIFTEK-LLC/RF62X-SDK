cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(RF62X_SMART_EXAMPLES LANGUAGES C)



###############################################################################
## CONFIGURATION
## project configuration
###############################################################################

## CONSOLE APPLICATIONS
# Search scanners and get hello-info
SET(RF62X_SMART_SEARCH_EXAMPLE                          ON  CACHE BOOL "" FORCE)
# Get profiles and write to file
SET(RF62X_SMART_PROFILE_EXAMPLE                         ON  CACHE BOOL "" FORCE)
# Get frames and write to bmp
SET(RF62X_SMART_FRAME_EXAMPLE                           ON  CACHE BOOL "" FORCE)
# Get/Set scanner's parameters
SET(RF62X_SMART_PARAMETER_EXAMPLE                       ON  CACHE BOOL "" FORCE)
# Get dump profiles
SET(RF62X_SMART_DUMP_EXAMPLE                            ON  CACHE BOOL "" FORCE)

## WIDGETS APPLICATIONS
# Getting profiles and displaying in profile-widget
SET(RF62X_SMART_PROFILE_VIEWER                          OFF CACHE BOOL "" FORCE)
# Getting frames and displaying in frame-widget
SET(RF62X_SMART_FRAME_VIEWER                            OFF CACHE BOOL "" FORCE)
# Getting/Setting scanner's parameters-widget
SET(RF62X_SMART_PARAMETERS_VIEWER                       OFF CACHE BOOL "" FORCE)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################

## CONSOLE APPLICATIONS
# Search scanners and get hello-info
if (RF62X_SMART_SEARCH_EXAMPLE)
    add_subdirectory(SEARCH_EXAMPLE)
endif()
# Get profiles and write to file
if (RF62X_SMART_PROFILE_EXAMPLE)
    add_subdirectory(PROFILE_EXAMPLE)
endif()
# Get frames and write to bmp
if (RF62X_SMART_FRAME_EXAMPLE)
    add_subdirectory(FRAME_EXAMPLE)
endif()
# Get/Set scanner's parameters
if (RF62X_SMART_PARAMETER_EXAMPLE)
    add_subdirectory(PARAMETER_EXAMPLE)
endif()
# Get dump profiles
if (RF62X_SMART_DUMP_EXAMPLE)
    add_subdirectory(DUMP_EXAMPLE)
endif()

## WIDGETS APPLICATIONS
# Getting profiles and displaying in profile-widget
if (RF62X_SMART_PROFILE_VIEWER)
    add_subdirectory(PROFILE_VIEWER)
endif()
# Getting frames and displaying in frame-widget
if (RF62X_SMART_FRAME_VIEWER)
    add_subdirectory(FRAME_VIEWER)
endif()
# Getting/Setting scanner's parameters-widget
if (RF62X_SMART_PARAMETERS_VIEWER)
    add_subdirectory(PARAMETERS_VIEWER)
endif()
