cmake_minimum_required(VERSION 3.13)



###############################################################################
## 3RD-PARTY
## dependencies for the project
###############################################################################
project(3rdparty LANGUAGES CXX)



###############################################################################
## SETTINGS
## basic 3rd-party settings before use
###############################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_RF62X_SDK_)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)



###############################################################################
## CONFIGURATION
## 3rd-party submodules configuration
###############################################################################
SET(${PARENT}_SETTINGS_MODEL_SUBMODULE ON CACHE BOOL "" FORCE)
if (${PARENT}_SETTINGS_MODEL_SUBMODULE)
    SET(${PARENT}_SETTINGS_MODEL                         ON CACHE BOOL "" FORCE)
    SET(${PARENT}_SETTINGS_MODEL_EXAMPLES               OFF CACHE BOOL "" FORCE)
endif()


###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
###############################################################################
# set rf627core path variable
set(RF62XCORE_DIR "../../../RF62X-Core")
# add subdirectory of rf627core lib
add_subdirectory(${RF62XCORE_DIR} RF62X-Core)

if (${PARENT}_SETTINGS_MODEL_SUBMODULE)
    add_subdirectory(SettingsModel)
endif()
