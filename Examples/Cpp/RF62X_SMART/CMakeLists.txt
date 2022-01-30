cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(RF62X_2XX_EXAMPLES LANGUAGES CXX)



###############################################################################
## CONFIGURATION
## project configuration
###############################################################################

## CONSOLE APPLICATIONS
# Search scanners and get hello-info
SET(RF62X_2XX_SEARCH_EXAMPLE                          ON  CACHE BOOL "" FORCE)
# Get profiles and write to file
SET(RF62X_2XX_PROFILE_EXAMPLE                         ON  CACHE BOOL "" FORCE)
# Get frames and write to bmp
SET(RF62X_2XX_FRAME_EXAMPLE                           ON  CACHE BOOL "" FORCE)
# Get/Set scanner's parameters
SET(RF62X_2XX_PARAMETER_EXAMPLE                       ON  CACHE BOOL "" FORCE)
# Get dump profiles
SET(RF62X_2XX_DUMP_EXAMPLE                            ON  CACHE BOOL "" FORCE)
# Multithread example
SET(RF62X_2XX_MULTITHREAD_EXAMPLE                     ON  CACHE BOOL "" FORCE)
# Send custom command
SET(RF62X_2XX_CUSTOM_COMMAND_EXAMPLE                  ON  CACHE BOOL "" FORCE)
# Communication with peripherals
SET(RF62X_2XX_PERIPHERY_EXAMPLE                       ON  CACHE BOOL "" FORCE)


## WIDGETS APPLICATIONS
# Getting profiles and displaying in profile-widget
SET(RF62X_2XX_PROFILE_VIEWER                          OFF CACHE BOOL "" FORCE)
# Getting frames and displaying in frame-widget
SET(RF62X_2XX_FRAME_VIEWER                            OFF CACHE BOOL "" FORCE)
# Getting/Setting scanner's parameters-widget
SET(RF62X_2XX_PARAMETERS_VIEWER                       OFF CACHE BOOL "" FORCE)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################

## CONSOLE APPLICATIONS
# Search scanners and get hello-info
if (RF62X_2XX_SEARCH_EXAMPLE)
    add_subdirectory(SEARCH_EXAMPLE)
endif()
# Get profiles and write to file
if (RF62X_2XX_PROFILE_EXAMPLE)
    add_subdirectory(PROFILE_EXAMPLE)
endif()
# Get frames and write to bmp
if (RF62X_2XX_FRAME_EXAMPLE)
    add_subdirectory(FRAME_EXAMPLE)
endif()
# Get/Set scanner's parameters
if (RF62X_2XX_PARAMETER_EXAMPLE)
    add_subdirectory(PARAMETER_EXAMPLE)
endif()
# Get dump profiles
if (RF62X_2XX_DUMP_EXAMPLE)
    add_subdirectory(DUMP_EXAMPLE)
endif()
# Multithread example
if (RF62X_2XX_MULTITHREAD_EXAMPLE)
    add_subdirectory(MULTITHREAD_EXAMPLE)
endif()
# Send custom command example
if (RF62X_2XX_CUSTOM_COMMAND_EXAMPLE)
    add_subdirectory(CUSTOM_COMMAND_EXAMPLE)
endif()
# Communication with peripherals
if (RF62X_2XX_PERIPHERY_EXAMPLE)
    add_subdirectory(PERIPHERY_EXAMPLE)
endif()

## WIDGETS APPLICATIONS
# Getting profiles and displaying in profile-widget
if (RF62X_2XX_PROFILE_VIEWER)
    add_subdirectory(PROFILE_VIEWER)
endif()
# Getting frames and displaying in frame-widget
if (RF62X_2XX_FRAME_VIEWER)
    add_subdirectory(FRAME_VIEWER)
endif()
# Getting/Setting scanner's parameters-widget
if (RF62X_2XX_PARAMETERS_VIEWER)
    add_subdirectory(PARAMETERS_VIEWER)
endif()


