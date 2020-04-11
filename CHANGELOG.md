# Changelog

## [Unreleased]

## [1.3.1] - 2020-04-11
### Added
- Google tests (Gtest) for SDK

### Changed

### Removed
- Removed dependency in core-lib from struct sockaddr_in and changed it to ip addr and port

### Fixed
- Fixed bug with request and response on hello packet
- Fixed ntoh and hton methods into core library

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