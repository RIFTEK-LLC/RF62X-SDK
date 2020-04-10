# Changelog

## [Unreleased]

## [1.3.0] - 2020-04-10
### Added
- Added the ability to get information about the device from the hello package 
(does not require the connection to the device):
  - General information:
    * Device name
    * Serial number
    * IP address
    * MAC address
    * Profile port
    * Service port
  - Working ranges:
    * Zsmr
    * Zmr
    * Xsmr
    * Xemr
  - Versions:
    * Firmware
    * Hardware
- Added new methods of getting additional information about scanners to examples of searching.
- Added new methods of setting scanner's parameter to examples with parameterization.

### Changed
- Changed returned value type of core_version() function from uint32_t to char*
- Changed returned value type of sdk_version() function from uint32_t to std::string


### Removed

### Fixed