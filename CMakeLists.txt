cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(RF62X-SDK)



###############################################################################
## SETTINGS
## basic project settings before use
###############################################################################
# If this project is used as a submodule, the variable should be overridden
# to "OFF" in the top-level application (to disable forced cache rewriting)
option(${PARENT}_SUBMODULE_CACHE_OVERWRITE "Enable forced cache rewriting" ON)
if (${PARENT}_SUBMODULE_CACHE_OVERWRITE)
    SET(REWRITE_FORCE "FORCE")
else()
    SET(REWRITE_FORCE "")
endif()



###############################################################################
## CONFIGURATION
## project configuration
###############################################################################
# Select a wrapper programming language (C99, C++, C#, Python)
SET(${PARENT}_WRAPPER_LANGUAGE     "C++"       CACHE STRING "" ${REWRITE_FORCE})

# Enable sdk examples
SET(${PARENT}_RF62X_SDK_EXAMPLES    ON         CACHE BOOL   "" ${REWRITE_FORCE})



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################
# Add sdk-library
if(${${PARENT}_WRAPPER_LANGUAGE} STREQUAL "C99")
    add_subdirectory(RF62X-Wrappers/C)
endif()
if(${${PARENT}_WRAPPER_LANGUAGE} STREQUAL "C++")
    add_subdirectory(RF62X-Wrappers/Cpp)
    # Examples
    if (${PARENT}_RF62X_SDK_EXAMPLES)
        add_subdirectory(Examples/Cpp)
    endif()
endif()
if(${${PARENT}_WRAPPER_LANGUAGE} STREQUAL "C#")
    add_subdirectory(RF62X-Wrappers/CSharp)
endif()
if(${${PARENT}_WRAPPER_LANGUAGE} STREQUAL "Python")
    add_subdirectory(RF62X-Wrappers/Python)
endif()


###############################################################################
## ADDITIONAL SETTINGS
## additional options and project settings
###############################################################################
# List of possible WRAPPER_LANGUAGE values
SET(WRAPPER_LANGUAGE_VALUES "C99;C++;C#;Python"
    CACHE INTERNAL "" ${REWRITE_FORCE})
# to display WRAPPER_LANGUAGE in combobox format
SET_PROPERTY(CACHE ${PARENT}_WRAPPER_LANGUAGE
    PROPERTY STRINGS ${WRAPPER_LANGUAGE_VALUES})


