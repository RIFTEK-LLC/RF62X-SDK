
.. _rf62x_more_description:

*******************************************************************************
Дополнительная информация
*******************************************************************************

.. _rf62x_more_description_params:

PARAMETERS
===============================================================================

Description of device parameters. All device parameters are readable.
Those parameters that cannot be written without authorization as
manufacturer have "awrite" access type. If no minimum value is specified
for a parameter, the minimum value corresponds to the minimum value of
the parameter type. If no maximum value is specified, it corresponds to
the maximum value of the parameter type.

The main elements of the parameter description: 

|  -  **Access** - describes the availability of the parameter for reading and writing. 
|     -  read - parameter is readable, 
|     -  write - parameter is writable by user, 
|     -  awrite - parameter is writable after authorization as a manufacturer 

|  -  **Type** - the data type of the parameter. - uint32\_t - unsigned integer, 32 bits,
|     - uint64\_t - unsigned integer, 64 bits, 
|     - int32\_t - signed integer, 32 bits, 
|     - int64\_t - signed integer, 64 bits, 
|     - float\_t - floating point, 32 bits, 
|     - double\_t - floating point, 64 bits, 
|     - u32\_arr\_t - array of unsigned integer, 32 bits, 
|     - u64\_arr\_t - array of unsigned integer, 64 bits, 
|     - i32\_arr\_t - array of signed integer, 32 bits, 
|     - i64\_arr\_t - array of signed integer, 64 bits, 
|     - flt\_array\_t - array of floating point, 32 bits, 
|     - dbl\_array\_t - array of floating point, 64 bits, 
|     - string\_t - string, ending with "0", the maximum length of the string is specified in the parameter description

|  -  **Min value** - minimum parameter value, writing a value less than this is not allowed. If no minimum
|     value is specified, it is defined by the type of parameter. 

|  -  **Max value** - maximum parameter value, writing a value greater than this is
|     not allowed. If no maximum value is specified, it is defined by the type
|     of parameter. 

|  -  **Step** - step with which it is allowed to change the
|     parameter value. Values ​​that do not match the step will not be set. If
|     no step is specified, any parameter change is allowed. 

|  -  **Enum** - enumeration of valid parameter values. Values ​​that do not match the
|     enumeration will not be set. 

|  -  **Default value** - default value of the parameter, set by the manufacturer 
|     or after switching on the device (depending on the parameter).

User
-------------------------------------------------------------------------------

|  -  **user\_general\_deviceState** - Current device state - combination
|     of enum values. The device changes the value of this parameter when
|     initializing the equipment, transferring important data over the
|     network (e.g. firmware), updating the firmware and in other cases. In
|     all modes except DEV\_STATE\_NORMAL, the device can pause the
|     transfer of profiles and other data not related to the current
|     operating mode.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: DEV\_STATE\_NORMAL
|     -  *Max value*: DEV\_STATE\_HARDWARE\_INIT
|     -  *Enum*:
|        -  DEV\_STATE\_NORMAL - the device operates in normal mode,
|        -  DEV\_STATE\_CALIB\_FILE\_RCV - the device receives a
|           calibration file,
|        -  DEV\_STATE\_CALIB\_FILE\_SND - the device is transfer
|           calibration file,
|        -  DEV\_STATE\_CALIB\_FILE\_SAVE - the device saves the
|           calibration file to the internal flash drive,
|        -  DEV\_STATE\_FIRMWARE\_RCV - device receives firmware,
|        -  DEV\_STATE\_FIRMWARE\_SND - the device is transfer firmware,
|        -  DEV\_STATE\_FIRMWARE\_SAVE - the device saves the firmware file
|           to the internal flash drive,
|        -  DEV\_STATE\_ETH\_INIT - the device initializes hardware and
|           software for ethernet connection,
|        -  DEV\_STATE\_DUMP\_DOWNLOAD - the device transfers dump data,
|        -  DEV\_STATE\_ETH\_EXCESS - required connection speed exceeds
|           current value for ethernet connection,
|        -  DEV\_STATE\_HARDWARE\_INIT - device initializes hardware
|     -  *Default value*: DEV\_STATE\_NORMAL

|  -  **user\_general\_deviceName** - User-defined scanner name. It is
|     displayed on the web page of the scanner and can be used to quickly
|     identify scanners.
|     -  *Access*: read/write
|     -  *Type*: string\_t
|     -  *Max len*: 128
|     -  *Default value*: "2D laser scanner"

|  -  **user\_general\_logSaveEnabled** - Allow automatic log saving after
|     device boot and after critical events. When this option is enabled,
|     it slightly (~ 100ms) increases the time until the device is ready
|     for operation.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_general\_logSize** - The current size (number of records) of
|     the device’s internal log file.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Default value*: 0

|  -  **user\_sysMon\_fpgaTemp** - The current temperature of the FPGA
|     (internal computing module) of the device.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_paramsChanged** - Device settings have been changed
|     but not saved.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_sysMon\_tempSens00** - Current temperature inside the device
|     case, measured by the sensor with address 00.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens00Max** - Maximum temperature fixed by sensor
|     with address 00.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens00Min** - Minimum temperature fixed by sensor
|     with address 00.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens01** - Current temperature inside the device
|     case, measured by the sensor with address 01.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens01Max** - Maximum temperature fixed by sensor
|     with address 01.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens01Min** - Minimum temperature fixed by sensor
|     with address 01.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens10** - Current temperature inside the device
|     case, measured by the sensor with address 10.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens10Max** - Maximum temperature fixed by sensor
|     with address 10.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens10Min** - Minimum temperature fixed by sensor
|     with address 10.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens11** - Current temperature inside the device
|     case, measured by the sensor with address 11.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens11Max** - Maximum temperature fixed by sensor
|     with address 11.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sysMon\_tempSens11Min** - Minimum temperature fixed by sensor
|     with address 11.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Min value*: -100
|     -  *Max value*: +100
|     -  *Default value*: 0
|     -  *Units*: °C

|  -  **user\_sensor\_syncSource** - Measurement synchronization source.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: SYNC\_INTERNAL
|     -  *Max value*: SYNC\_SOFTWARE
|     -  *Enum*:
|        -  SYNC\_INTERNAL - start of measurements from the device's
|           internal generator,
|        -  SYNC\_EXTERNAL - start of measurements from an external source,
|        -  SYNC\_SOFTWARE - start of measurements by software request
|     -  *Default value*: SYNC\_INTERNAL

|  -  **user\_sensor\_framerate** - Frame rate of the CMOS-sensor, sets the
|     measurement frequency. The value to be written should not exceed the
|     value of the parameter **user\_sensor\_maxFramerate**.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 1
|     -  *Max value*: 20000
|     -  *Default value*: 490
|     -  *Units*: Hz

|  -  **user\_sensor\_maxFramerate** - Maximum frame rate (measurement
|     frequency) for the current operation mode.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: 1
|     -  *Max value*: 20000
|     -  *Default value*: 490
|     -  *Units*: Hz

|  -  **user\_sensor\_exposureControl** - CMOS-sensor exposure control
|     method.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: EXPOSE\_AUTO
|     -  *Max value*: EXPOSE\_MULTI\_3
|     -  *Enum*:
|        -  EXPOSE\_AUTO - automatic exposure control based on profile
|           analysis,
|        -  EXPOSE\_FIXED - exposure time is user-defined,
|        -  EXPOSE\_MULTI\_2 - mode with 2 exposures, used to obtain a
|           profile on surfaces with different levels of reflection,
|        -  EXPOSE\_MULTI\_3 - mode with 3 exposures, used to obtain a
|           profile on surfaces with different levels of reflection
|     -  *Default value*: EXPOSE\_FIXED

|  -  **user\_sensor\_exposure1** - Frame exposure time in EXPOSE\_AUTO and
|     EXPOSE\_FIXED modes.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 3000
|     -  *Max value*: 300000000
|     -  *Step*: 100
|     -  *Default value*: 300000
|     -  *Units*: ns

|  -  **user\_sensor\_exposure2** - Frame #2 exposure time in
|     EXPOSE\_MULTI\_2 mode.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 3000
|     -  *Max value*: 300000000
|     -  *Step*: 100
|     -  *Default value*: 300000
|     -  *Units*: ns

|  -  **user\_sensor\_exposure3** - Frame #3 exposure time in
|     EXPOSE\_MULTI\_2 mode.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 3000
|     -  *Max value*: 300000000
|     -  *Step*: 100
|     -  *Default value*: 300000
|     -  *Units*: ns

|  -  **user\_sensor\_maxExposure** - Maximum frame exposure time in the
|     current device mode.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 3000
|     -  *Max value*: 300000000
|     -  *Step*: 100
|     -  *Default value*: 300000
|     -  *Units*: ns

|  -  **user\_sensor\_defectivePixels** - Array of coordinates [X1, Y1, X2,
|     Y2, ... X15, Y15] of the sensor's defective pixels.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 4096
|     -  *Max elements*: 32,
|     -  *Default value*: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
|        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

|  -  **user\_sensor\_doubleSpeedEnabled** - Turns on and off the sensor's
|     double frame rate mode. Enabling this mode allows almost double the
|     frequency of measurements (profiles per second) by reducing accuracy
|     in the Z-axis.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_sensor\_edrType** - Enable CMOS-sensor operation in the
|     extended dynamic range. Allows get a quality profile on light and
|     dark surfaces.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: EDR\_DISABLE
|     -  *Max value*: EDR\_COLUMN
|     -  *Enum*:
|        -  EDR\_DISABLE - extended dynamic range mode disabled,
|        -  EDR\_COLUMN - different exposure mode for even and odd columns
|     -  *Default value*: EDR\_DISABLE

|  -  **user\_sensor\_edrColumnDivider** - Exposure time divider for odd
|     columns. This parameter controls the sensitivity to very bright areas
|     of the profile.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 2
|     -  *Max value*: 32
|     -  *Default value*: 2

|  -  **user\_roi\_enabled** - Turns on and off the mode of obtaining
|     measurements in the region of interest.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_roi\_active** - Indicates the status of the ROI in automatic
|     positioning mode. In the automatic position control mode, if the
|     profile is not detected, the activity switches to the FALSE state,
|     when the profile is detected, the parameter switches to the TRUE
|     state. In manual positioning mode, the parameter is always TRUE.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_roi\_posMode** - ROI position control mode.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: ROI\_POSITION\_MANUAL
|     -  *Max value*: ROI\_POSITION\_AUTO
|     -  *Enum*:
|        -  ROI\_POSITION\_MANUAL - ROI position is set by the user,
|        -  ROI\_POSITION\_AUTO - ROI automatic position control with
|           profile holding in the center
|     -  *Default value*: ROI\_POSITION\_MANUAL

|  -  **user\_roi\_pos** - Current position of the upper edge of the ROI in
|     the sensor lines.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 1280
|     -  *Default value*: 100
|     -  *Units*: lines

|  -  **user\_roi\_maxPos** - Maximum position of the upper limit of the
|     ROI in the current operating mode of the device.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Max value*: 1280
|     -  *Default value*: 1180
|     -  *Units*: lines

|  -  **user\_roi\_size** - Sets the size of the area in the lines where
|     the profile is searched and processed.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 8
|     -  *Max value*: 488
|     -  *Step*: 8
|     -  *Default value*: 64
|     -  *Units*: lines

|  -  **user\_roi\_reqProfSize** - Minimum required number of profile
|     points for activating an ROI in ROI\_POSITION\_AUTO mode.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 1280
|     -  *Step*: 64
|     -  *Default value*: 320
|     -  *Units*: points

|  -  **user\_roi\_zsmr** - ROI start position in mm.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Max value*: 10000
|     -  *Default value*: 0
|     -  *Units*: mm

|  -  **user\_roi\_zemr** - ROI end position in mm.
|     -  *Access*: read
|     -  *Type*: float\_t
|     -  *Max value*: 10000
|     -  *Default value*: 0
|     -  *Units*: mm

|  -  **user\_network\_speed** - Current Ethernet connection speed. The
|     connection speed is changed by writing to this parameter. In case of
|     auto-negotiation, writing is ignored.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: LINK\_SPEED\_10MBIT
|     -  *Max value*: LINK\_SPEED\_1GBIT
|     -  *Enum*:
|        -  LINK\_SPEED\_10MBIT - the connection speed is 10 Mbs, currently
|           almost unused,
|        -  LINK\_SPEED\_100MBIT - the connection speed is 100 Mbs,
|        -  LINK\_SPEED\_1GBIT - the connection speed is 1000 Mbs
|     -  *Default value*: LINK\_SPEED\_1GBIT
|     -  *Units*: Mbps

|  -  **user\_network\_requiredSpeed** - The required Ethernet connection
|     speed in the current device operation mode. Depends on the number of
|     profiles per second, the number of points in the profile, etc.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: 1
|     -  *Max value*: 10000
|     -  *Default value*: 1
|     -  *Units*: Mbps

|  -  **user\_network\_autoNeg** - Turns on and off the automatic
|     negotiation of the Ethernet connection speed.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: TRUE

|  -  **user\_network\_ip** - The network address of the device.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 4,
|     -  *Default value*: [192, 168, 1, 30]

|  -  **user\_network\_mask** - Subnet mask for the device.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 4,
|     -  *Default value*: [255, 255, 255, 0]

|  -  **user\_network\_gateway** - Gateway address.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 4,
|     -  *Default value*: [192, 168, 1, 1]

|  -  **user\_network\_hostIP** - The network address of the device to
|     which profiles and calculation results are sent using the UDP
|     protocol.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 4,
|     -  *Default value*: [192, 168, 1, 2]

|  -  **user\_network\_hostPort** - The port number on the device to which
|     profiles and calculation results are sent over the UDP protocol.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 50001

|  -  **user\_network\_webPort** - Port number to access the Web page.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 80

|  -  **user\_network\_servicePort** - Port number for service protocol.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 50011

|  -  **user\_streams\_udpEnabled** - Enabling and disabling the profile
|     stream, transmitted via the UDP protocol (sending to the network
|     address, set by the user\_network\_hostIP parameter and the port, set
|     by the user\_network\_hostPort parameter).
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_streams\_format** - The format of the transmitted profiles.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: DATA\_FORMAT\_RAW\_PROFILE
|     -  *Max value*: DATA\_FORMAT\_PROFILE
|     -  *Enum*:
|        -  DATA\_FORMAT\_RAW\_PROFILE - the position of the points in the
|           profile is transferred without applying calibration data, in
|           subpixel values. Used for debugging and setting up the device,
|           allows to compare the image, generated by the CMOS-sensor and
|           the calculated profile position,
|        -  DATA\_FORMAT\_PROFILE - the position of the points in the
|           profile is transmitted in discretes, the main format for the
|           operation of the device
|     -  *Default value*: DATA\_FORMAT\_PROFILE

|  -  **user\_streams\_pointsCount** - The number of points in the profile
|     that the device calculates and transmits.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 648
|     -  *Max value*: 1296
|     -  *Step*: 648
|     -  *Default value*: 648
|     -  *Units*: points

|  -  **user\_streams\_includeIntensity** - Enable or disable the transfer
|     of brightness points in the profile. The brightness values ​​are
|     transferred after the profile data in the format of 1 byte per point,
|     0 - black ... 255 - white.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_streams\_udpPacketsCounter** - Internal counter of
|     transmitted UDP packets with profiles. It can be used to control the
|     loss of packets with profiles.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Default value*: 0

|  -  **user\_processing\_threshold** - Threshold of profile points
|     detection. Smaller values of the parameter allow detect the profile
|     at a lower brightness of the signal, which may cause false detections
|     on flare and reflections. Higher parameter values require higher
|     signal brightness, but provide confident detection of the profile
|     position.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 100
|     -  *Default value*: 2
|     -  *Units*: %

|  -  **user\_processing\_profPerSec** - The number of processed profiles
|     per second.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Max value*: 20000
|     -  *Default value*: 490
|     -  *Units*: pps

|  -  **user\_processing\_medianMode** - Enable and width of median profile
|     filtering. The median filter allows remove random outliers and fill
|     the gaps in the profile with a width of up to half the size of the
|     filter.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 15
|     -  *Enum*:
|        -  0 - the filter is disabled,
|        -  3 - the filter is enabled, filter size is 3 points,
|        -  5 - the filter is enabled, filter size is 5 points,
|        -  7 - the filter is enabled, filter size is 7 points,
|        -  9 - the filter is enabled, filter size is 9 points,
|        -  11 - the filter is enabled, filter size is 11 points,
|        -  13 - the filter is enabled, filter size is 13 points,
|        -  14 - the filter is enabled, filter size is 15 points,
|     -  *Default value*: 0

|  -  **user\_processing\_bilateralMode** - Bilateral filter allows smooth
|     the values ​​of the points of the profile, while maintaining its
|     sharp changes.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 15
|     -  *Enum*:
|        -  0 - the filter is disabled,
|        -  3 - the filter is enabled, filter size is 3 points,
|        -  5 - the filter is enabled, filter size is 5 points,
|        -  7 - the filter is enabled, filter size is 7 points,
|        -  9 - the filter is enabled, filter size is 9 points,
|        -  11 - the filter is enabled, filter size is 11 points,
|        -  13 - the filter is enabled, filter size is 13 points,
|        -  14 - the filter is enabled, filter size is 15 points,
|     -  *Default value*: 0

|  -  **user\_processing\_peakMode** - Profile peak detection mode for
|     position calculation. Used to ignore reflections and highlights.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: PEAK\_MODE\_INTENSITY
|     -  *Max value*: PEAK\_MODE\_NUMBER\_4
|     -  *Enum*:
|        -  PEAK\_MODE\_INTENSITY - the position of the profile points is
|           calculated at maximum intensity,
|        -  PEAK\_MODE\_FIRST - the position of the profile points is
|           calculated from the first overstepping of the detection
|           threshold,
|        -  PEAK\_MODE\_LAST - the position of the profile points is
|           calculated from the last overstepping of the detection
|           threshold,
|        -  PEAK\_MODE\_NUMBER\_2 - when calculating the position of
|           profile points, the advantage is given to peak #2,
|        -  PEAK\_MODE\_NUMBER\_3 - when calculating the position of
|           profile points, the advantage is given to peak #3,
|        -  PEAK\_MODE\_NUMBER\_4 - when calculating the position of
|           profile points, the advantage is given to peak #4
|     -  *Default value*: PEAK\_MODE\_INTENSITY

|  -  **user\_processing\_flip** - Profile reflection mode. Reflection
|     applies only if **user\_streams\_format** is set to
|     DATA\_FORMAT\_PROFILE.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FLIP\_MODE\_OFF
|     -  *Max value*: FLIP\_MODE\_XZ
|     -  *Enum*:
|        -  FLIP\_MODE\_OFF - no reflections,
|        -  FLIP\_MODE\_X - reflection along the X axis,
|        -  FLIP\_MODE\_Z - reflection along the Z axis,
|        -  FLIP\_MODE\_XZ - reflection along the X and Z axis
|     -  *Default value*: FLIP\_MODE\_OFF

|  -  **user\_laser\_enabled** - Switching the laser radiation on and off.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_laser\_value** - Sets the brightness of the laser radiation.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 100
|     -  *Step*: 5
|     -  *Default value*: 0
|     -  *Units*: %

|  -  **user\_trigger\_sync\_source** - Selection of inputs and their
|     combinations for synchronization of measurements.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: TRIG\_SOURCE\_IN1
|     -  *Max value*: TRIG\_SOURCE\_IN1\_AND\_IN2
|     -  *Enum*:
|        -  TRIG\_SOURCE\_IN1 - trigger measurements on an event at input
|           1,
|        -  TRIG\_SOURCE\_IN2 - trigger measurements on an event at input
|           2,
|        -  TRIG\_SOURCE\_IN1\_OR\_IN2 - trigger measurements on an event
|           at input 1 **or** input 2,
|        -  TRIG\_SOURCE\_IN1\_AND\_IN2 - trigger measurements on an event
|           at input 1 **and** input 2
|     -  *Default value*: TRIG\_SOURCE\_IN1

|  -  **user\_trigger\_sync\_strictEnabled** - Enable or disable strict
|     synchronization mode. When this mode is enabled, synchronization
|     events that occurred during a frame exposure will be ignored and the
|     next measurement will only be triggered by the synchronization event,
|     when the sensor has finished exposing the previous frame. In this
|     case, if the synchronization event rate is slightly higher than the
|     maximum frame rate of the sensor, the number of profiles per second
|     will be lower than the maximum frame rate due to the stroboscopic
|     effect. If the mode is off and there were synchronization events
|     during the exposure, the next measurement will start as soon as the
|     sensor finishes exposing the previous frame. In any situation, the
|     encoder value in the profile will be recorded at the middle of the
|     frame exposure.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_trigger\_sync\_divider** - The synchronization event divider.
|     Does not affect the encoder counter.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 1
|     -  *Max value*: 8192
|     -  *Default value*: 1

|  -  **user\_trigger\_sync\_delay** - The value of the delay in the start
|     of measurement (start of frame exposure) relative to the
|     synchronization event.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 700
|     -  *Max value*: 100000000
|     -  *Step*: 100
|     -  *Default value*: 700
|     -  *Units*: ns

|  -  **user\_trigger\_sync\_value** - The value of the internal
|     measurement start counter. Shows the number of measurements taken.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Default value*: 0

|  -  **user\_trigger\_counter\_type** - Type of encoder counter (internal
|     pulse counter) at synchronization inputs.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: TRIG\_COUNTER\_UNIDIR
|     -  *Max value*: TRIG\_COUNTER\_BIDIR
|     -  *Enum*:
|        -  TRIG\_COUNTER\_UNIDIR - unidirectional counter, that does not
|           take into account the phase of the signals at inputs 1 and 2,
|        -  TRIG\_COUNTER\_BIDIR - bidirectional counter, that takes into
|           account the phase of the signals at inputs 1 and 2, and can
|           both increase and decrease
|     -  *Default value*: TRIG\_COUNTER\_UNIDIR

|  -  **user\_trigger\_counter\_maxValue** - The maximum value of the
|     encoder counter, upon reaching which it is reset to the 0.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 1
|     -  *Max value*: 4294967295‬
|     -  *Default value*: 4294967295‬

|  -  **user\_trigger\_counteraser\_resetTimerEnabled** - Enabling and
|     disabling the timer for automatically resetting the encoder counter
|     to 0. If the timer is enabled, then if no synchronization events
|     during the time, specified by the
|     **user\_trigger\_counter\_resetTimerValue** parameter, the encoder
|     counter will be reset to 0.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_trigger\_counter\_resetTimerValue** - Timeout value until the
|     encoder counter value is automatically reset to 0.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 100
|     -  *Max value*: 4294967295‬
|     -  *Step*: 1000
|     -  *Default value*: 4294967295‬
|     -  *Units*: ns

|  -  **user\_trigger\_counter\_value** - Encoder counter value. This is an
|     internal event counter at inputs 1 and 2.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Default value*: 0

|  -  **user\_trigger\_counter\_dir** - The ratio of the phases of the
|     signals at inputs 1 and 2. Determines the direction of movement if
|     using a movement system.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Default value*: 0

|  -  **user\_input1\_enabled** - Turning the input 1 on and off. If the
|     input is turned off, then all signals will be ignored.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_input1\_mode** - Input 1 operation mode. Defines which signal
|     change is a synchronization event for a given input.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: IN1\_MODE\_RISE\_OR\_FALL
|     -  *Max value*: IN1\_MODE\_LVL0
|     -  *Enum*:
|        -  IN1\_MODE\_RISE\_OR\_FALL - the synchronization event is both
|           the transition from low to high state (edge of the pulse) and
|           from high to low state (fall of the pulse),
|        -  IN1\_MODE\_RISE - the synchronization event is only the
|           transition from low to high state (edge of the pulse),
|        -  IN1\_MODE\_FALL - the synchronization event is only the
|           transition from high to low (fall of the pulse),
|        -  IN1\_MODE\_LVL1 - the synchronization event is a high level at
|           the input, measures starts from the internal generator,
|        -  IN1\_MODE\_LVL0 - the synchronization event is a low level at
|           the input, measures starts from the internal generator
|     -  *Default value*: IN1\_MODE\_RISE\_OR\_FALL

|  -  **user\_input2\_enabled** - Turning the input 2 on and off. If the
|     input is turned off, then all signals will be ignored.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Default value*: FALSE

|  -  **user\_input2\_mode** - Input 2 operation mode. Defines which signal
|     change is a synchronization event for a given input.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: IN2\_MODE\_RISE\_OR\_FALL
|     -  *Max value*: IN2\_MODE\_LVL0
|     -  *Enum*:
|        -  IN2\_MODE\_RISE\_OR\_FALL - the synchronization event is both
|           the transition from low to high state (edge of the pulse) and
|           from high to low state (fall of the pulse),
|        -  IN2\_MODE\_RISE - the synchronization event is only the
|           transition from low to high state (edge of the pulse),
|        -  IN2\_MODE\_FALL - the synchronization event is only the
|           transition from high to low (fall of the pulse),
|        -  IN2\_MODE\_LVL1 - the synchronization event is a high level at
|           the input, measures starts from the internal generator,
|        -  IN2\_MODE\_LVL0 - the synchronization event is a low level at
|           the input, measures starts from the internal generator
|     -  *Default value*: IN2\_MODE\_RISE\_OR\_FALL

|  -  **user\_input3\_enabled** - Turning the input 3 on and off. If the
|     input is turned off, then all signals will be ignored.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_input3\_mode** - Input 3 operation mode. This input is mainly
|     used to reset the encoder counter value.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: IN3\_MODE\_RISE
|     -  *Max value*: IN3\_MODE\_FALL
|     -  *Enum*:
|        -  IN3\_MODE\_RISE - reset the encoder counter value at the rising
|           edge of the pulse at the input,
|        -  IN3\_MODE\_FALL - reset the encoder counter value at the
|           falling edge of the pulse at the input
|     -  *Default value*: IN3\_MODE\_RISE

|  -  **user\_input1\_samples** - An array of signal values ​​at input 1.
|     The parameter is a time scan of the signals at input 1. Every 2 bits
|     indicate the state of the signal at a certain point in time. Value
|     0b00 - low signal level, 0b01 - state changed (pulses), 0b10 -
|     reserved, 0b11 - high level.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max elements*: 6,
|     -  *Default value*: [0, 0, 0, 0, 0, 0]

|  -  **user\_input2\_samples** - An array of signal values ​​at input 2.
|     The parameter is a time scan of the signals at input 2. Every 2 bits
|     indicate the state of the signal at a certain point in time. Value
|     0b00 - low signal level, 0b01 - state changed (pulses), 0b10 -
|     reserved, 0b11 - high level.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max elements*: 6,
|     -  *Default value*: [0, 0, 0, 0, 0, 0]

|  -  **user\_input3\_samples** - An array of signal values ​​at input 3.
|     The parameter is a time scan of the signals at input 3. Every 2 bits
|     indicate the state of the signal at a certain point in time. Value
|     0b00 - low signal level, 0b01 - state changed (pulses), 0b10 -
|     reserved, 0b11 - high level.
|     -  *Access*: read/write
|     -  *Type*: u32\_arr\_t
|     -  *Max elements*: 6,
|     -  *Default value*: [0, 0, 0, 0, 0, 0]

|  -  **user\_output1\_enabled** - Turning output 1 on and off. When turned
|     off, the output is low. In the on state, the signal is set by the
|     parameters **user\_output1\_mode** and **user\_output1\_pulseWidth**.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_output1\_mode** - Output 1 mode. Sets which signal will be
|     output.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: OUT\_MODE\_EXPOSE\_START
|     -  *Max value*: OUT\_MODE\_IN3\_REPEATER
|     -  *Enum*:
|        -  OUT\_MODE\_EXPOSE\_START - impulse at the moment the frame
|           starts to be exposed for the next measurement,
|        -  OUT\_MODE\_EXPOSE\_TIME - pulse during the exposure of the
|           frame for the next measurement,
|        -  OUT\_MODE\_IN1\_REPEATER - input 1 repeater, regardless of
|           whether the input is on or off,
|        -  OUT\_MODE\_IN2\_REPEATER - input 2 repeater, regardless of
|           whether the input is on or off,
|        -  OUT\_MODE\_IN3\_REPEATER - input 3 repeater, regardless of
|           whether the input is on or off
|     -  *Default value*: OUT\_MODE\_EXPOSE\_START

|  -  **user\_output1\_pulseWidth** - Pulse width when
|     **user\_output1\_mode** parameter has value OUT\_MODE\_EXPOSE\_START.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: 10
|     -  *Max value*: 1000000
|     -  *Step*: 10
|     -  *Default value*: 1000
|     -  *Units*: ns

|  -  **user\_output2\_enabled** - Turning output 2 on and off. When turned
|     off, the output is low. In the on state, the signal is set by the
|     parameters **user\_output2\_mode** and **user\_output2\_pulseWidth**.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_output2\_mode** - Output 2 mode. Sets which signal will be
|     output.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: OUT\_MODE\_EXPOSE\_START
|     -  *Max value*: OUT\_MODE\_IN3\_REPEATER
|     -  *Enum*:
|        -  OUT\_MODE\_EXPOSE\_START - impulse at the moment the frame
|           starts to be exposed for the next measurement,
|        -  OUT\_MODE\_EXPOSE\_TIME - pulse during the exposure of the
|           frame for the next measurement,
|        -  OUT\_MODE\_IN1\_REPEATER - input 1 repeater, regardless of
|           whether the input is on or off,
|        -  OUT\_MODE\_IN2\_REPEATER - input 2 repeater, regardless of
|           whether the input is on or off,
|        -  OUT\_MODE\_IN3\_REPEATER - input 3 repeater, regardless of
|           whether the input is on or off
|     -  *Default value*: OUT\_MODE\_EXPOSE\_START

|  -  **user\_output2\_pulseWidth** - Pulse width when
|     **user\_output2\_mode** parameter has value OUT\_MODE\_EXPOSE\_START.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: 10
|     -  *Max value*: 1000000
|     -  *Step*: 10
|     -  *Default value*: 1000
|     -  *Units*: ns

|  -  **user\_dump\_enabled** - Enabling profile recording in the internal
|     memory of the device - forming a dump. The recording will be stopped
|     when the maximum dump capacity is reached, either when
|     **user\_dump\_capacity** is reached or when FALSE is written to this
|     parameter. Before starting the dump recording,
|     user\_trigger\_sync\_value and user\_trigger\_counter\_value counters
|     will be reset to 0.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_dump\_capacity** - User-defined number of profiles to be
|     dumped. Upon reaching this value, the recording will automatically
|     stop and the value of the **user\_dump\_enabled** parameter will
|     become FALSE.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: 1
|     -  *Max value*: 80000
|     -  *Default value*: 80000
|     -  *Units*: profiles

|  -  **user\_dump\_size** - The current number of profiles in the dump.
|     Before starting dump recording, this value is reset to 0. During dump
|     recording, this value increases.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Max value*: 80000
|     -  *Default value*: 0
|     -  *Units*: profiles

|  -  **user\_dump\_timeStamp** - The time stamp of the dump. Setted by the
|     device when the dump recording starts.
|     -  *Access*: read
|     -  *Type*: uint64\_t
|     -  *Default value*: 0
|     -  *Units*: ticks

|  -  **user\_dump\_view3d\_motionType** - Type of movement system on which
|     the device is installed. The value of the parameter is used to
|     correctly draw the dump as a 3D model.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: MOTION\_TYPE\_LINEAR
|     -  *Max value*: MOTION\_TYPE\_RADIAL
|     -  *Enum*:
|        -  MOTION\_TYPE\_LINEAR - linear motion system,
|        -  MOTION\_TYPE\_RADIAL - radial motion system
|     -  *Default value*: MOTION\_TYPE\_LINEAR

|  -  **user\_dump\_view3d\_ySource** - Source of the Y-axis coordinates.
|     The value of the parameter is used to correctly draw the dump as a 3D
|     model.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: Y\_AXIS\_SYSTEM\_TIME
|     -  *Max value*: Y\_AXIS\_MEASURES\_COUNTER
|     -  *Enum*:
|        -  Y\_AXIS\_SYSTEM\_TIME - internal device timer,
|        -  Y\_AXIS\_STEP\_COUNTER - parameter
|           **user\_trigger\_counter\_value**,
|        -  Y\_AXIS\_MEASURES\_COUNTER - measurements counter
|     -  *Default value*: Y\_AXIS\_SYSTEM\_TIME

|  -  **user\_dump\_view3d\_yStep** - The value of a single step in the
|     Y-axis.
|     -  *Access*: read/write
|     -  *Type*: double\_t
|     -  *Max value*: 10000
|     -  *Default value*: 0.0005
|     -  *Units*: mm

|  -  **user\_dump\_view3d\_paintMode** - 3D model coloring mode. This
|     parameter is used when drawing a 3D model in the WEB-interface.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: PAINT\_MODE\_HEIGHTMAP
|     -  *Max value*: PAINT\_MODE\_INTENSITY
|     -  *Enum*:
|        -  PAINT\_MODE\_HEIGHTMAP - coloring according to the height map,
|        -  PAINT\_MODE\_INTENSITY - intensity mapping, parameter
|           **user\_streams\_includeIntensity** must be set to TRUE,
|     -  *Default value*: PAINT\_MODE\_HEIGHTMAP

|  -  **user\_dump\_view3d\_decimation** - Profiles decimation when drawing
|     a 3D model. This parameter is used when drawing a 3D model in the
|     WEB-interface.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: DUMP\_VIEW3D\_DECIM\_1
|     -  *Max value*: DUMP\_VIEW3D\_DECIM\_200
|     -  *Enum*:
|        -  DUMP\_VIEW3D\_DECIM\_1 - all dump profiles are displayed,
|        -  DUMP\_VIEW3D\_DECIM\_2 - step to display dump profiles 2,
|        -  DUMP\_VIEW3D\_DECIM\_5 - step to display dump profiles 5,
|        -  DUMP\_VIEW3D\_DECIM\_10 - step to display dump profiles 10,
|        -  DUMP\_VIEW3D\_DECIM\_20 - step to display dump profiles 20,
|        -  DUMP\_VIEW3D\_DECIM\_50 - step to display dump profiles 50,
|        -  DUMP\_VIEW3D\_DECIM\_100 - step to display dump profiles 100,
|        -  DUMP\_VIEW3D\_DECIM\_200 - step to display dump profiles 200,
|     -  *Default value*: DUMP\_VIEW3D\_DECIM\_1

|  -  **user\_eip\_tcpPort** - The port number that the device listens for
|     incoming TCP connections via EthernetIP.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 44818

|  -  **user\_eip\_udpPort** - The port number that the device listens for
|     UDP packets with EthernetIP data.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 2222

|  -  **user\_compatibility\_rf625Enabled** - Enable or disable
|     compatibility mode with the obsolete RF625 scanner. When enabling
|     compatibility mode, UDP profile stream will be suspended.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

|  -  **user\_compatibility\_rf625TCPPort** - Port number for incoming TCP
|     connections via RF625 protocol.
|     -  *Access*: read/write
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 620

Factory
-------------------------------------------------------------------------------

|  -  **fact\_general\_firmwareVer** - Device firmware version [Major,
|     Minor, Patch].
|     -  *Access*: read
|     -  *Type*: u32\_arr\_t
|     -  *Max elements*: 3,
|     -  *Default value*: [1, 0, 0]

|  -  **fact\_general\_hardwareVer** - Device hardware version.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Default value*: 403051520

|  -  **fact\_general\_deviceType** - Device type identifier.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 627

|  -  **fact\_general\_serial** - Device serial number.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Default value*: 0

|  -  **fact\_general\_pcbSerial** - Device PCB serial number.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Default value*: 0

|  -  **fact\_general\_lifeTime** - Total device runtime in UNIX format.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 1577846300
|     -  *Default value*: 0
|     -  *Units*: s

|  -  **fact\_general\_workTime** - Device uptime in UNIX format.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 1577846300
|     -  *Default value*: 0
|     -  *Units*: s

|  -  **fact\_general\_startsCount** - Total number of device starts.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 8760
|     -  *Default value*: 0
|     -  *Units*: times

|  -  **fact\_general\_customerID** - Device customer identifier. The
|     identifier of the company that purchased / ordered the device.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Default value*: 0
|     -  *Units*: id

|  -  **fact\_general\_fpgaFreq** - FPGA project clock frequency for this
|     device.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 10000000
|     -  *Max value*: 500000000
|     -  *Default value*: 10000000
|     -  *Units*: Hz

|  -  **fact\_general\_smr** - Start of measuring range in Z axis in mm.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 10000
|     -  *Default value*: 80
|     -  *Units*: mm

|  -  **fact\_general\_mr** - Size of the measuring range in Z axis in mm.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 10000
|     -  *Default value*: 130
|     -  *Units*: mm

|  -  **fact\_general\_xsmr** - The size along the X axis of the measuring
|     range at the beginning of the range.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 10000
|     -  *Default value*: 40
|     -  *Units*: mm

|  -  **fact\_general\_xemr** - The size along the X axis of the measuring
|     range at the end of the range.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 10000
|     -  *Default value*: 40
|     -  *Units*: mm

|  -  **fact\_general\_pixDivider** - Divider to obtain the subpixel
|     position of profile points in the uncalibrated data transfer mode
|     (parameter **user\_streams\_format** is set to
|     DATA\_FORMAT\_RAW\_PROFILE).
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 32

|  -  **fact\_general\_profDivider** - Divider to obtain the subpixel
|     position of profile points in the calibrated data transfer mode
|     (parameter **user\_streams\_format** is set to
|     DATA\_FORMAT\_PROFILE).
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 16384

|  -  **fact\_general\_oemDevName** - Device name assigned by the OEM
|     customer.
|     -  *Access*: read/awrite
|     -  *Type*: string\_t
|     -  *Max len*: 128
|     -  *Default value*: "Laser scanner"

|  -  **fact\_general\_authStatus** - Authorization status for changing the
|     factory settings of the device.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Min value*: AUTH\_STATUS\_USER
|     -  *Max value*: AUTH\_STATUS\_FACTORY
|     -  *Enum*:  
|        -  AUTH\_STATUS\_USER - authorized as a user, factory settings
|           cannot be changed,
|        -  AUTH\_STATUS\_FACTORY - authorized as a manufacturer, factory
|           settings can be changed
|     -  *Default value*: AUTH\_STATUS\_USER

|  -  **fact\_sensor\_name** - Name of the sensor used in the device.
|     -  *Access*: read/awrite
|     -  *Type*: string\_t
|     -  *Max len*: 64
|     -  *Default value*: "TYPE 1"

|  -  **fact\_sensor\_width** - Number of pixels in the CMOS sensor.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 648
|     -  *Max value*: 648
|     -  *Default value*: 648
|     -  *Units*: pixels

|  -  **fact\_sensor\_height** - Number of lines in the CMOS sensor.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 488
|     -  *Max value*: 488
|     -  *Default value*: 488
|     -  *Units*: lines

|  -  **fact\_sensor\_pixFreq** - Pixel frequency for installed CMOS
|     sensor.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 1000000
|     -  *Max value*: 500000000
|     -  *Default value*: 40000000
|     -  *Units*: Hz

|  -  **fact\_sensor\_frmConstPart** - Constant part of the frame cycle.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 200
|     -  *Max value*: 200000
|     -  *Default value*: 3500
|     -  *Units*: ticks

|  -  **fact\_sensor\_frmPerLinePart** - Frame cycle part for each line.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 10
|     -  *Max value*: 100000
|     -  *Default value*: 160
|     -  *Units*: ticks

|  -  **fact\_sensor\_minExposure** - Minimum allowable exposure value.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 100000000
|     -  *Step*: 10
|     -  *Default value*: 3000
|     -  *Units*: ns

|  -  **fact\_sensor\_maxExposure** - Maximum allowable exposure value.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 300000000
|     -  *Step*: 10
|     -  *Default value*: 300000000
|     -  *Units*: ns

|  -  **fact\_sensor\_imgFlip** - Image reflection mode. Applies directly
|     to the image transmitted, by the CMOS sensor.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: FLIP\_MODE\_OFF
|     -  *Max value*: FLIP\_MODE\_XZ
|     -  *Enum*:
|        -  FLIP\_MODE\_OFF - no reflections,
|        -  FLIP\_MODE\_X - reflection along the X axis,
|        -  FLIP\_MODE\_Z - reflection along the Z axis,
|        -  FLIP\_MODE\_XZ - reflection along the X and Z axis
|     -  *Default value*: FLIP\_MODE\_OFF

|  -  **fact\_sensor\_analogGain** - CMOS sensor analog gain value.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 7
|     -  *Default value*: 5

|  -  **fact\_sensor\_digitalGain** - CMOS sensor digital gain value.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 55
|     -  *Default value*: 48

|  -  **fact\_sensor\_blackOdd** - Black level for odd lines.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 2300

|  -  **fact\_sensor\_blackEven** - Black level for even lines.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 2400

|  -  **fact\_network\_initRegs** - CMOS sensor registers values [regAddr,
|     regValue ...].
|     -  *Access*: read/awrite
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 64,
|     -  *Default value*: [41, 1, 83, 155, 58, 20, 59, 0, 60, 11, 69, 9,
|        80, 4, 97, 0, 98, 12, 101, 98, 102, 34, 103, 64, 106, 90, 107,
|        110, 108, 91, 109, 82, 110, 80, 117, 91]

|  -  **fact\_network\_macAddr** - Physical address of the device.
|     -  *Access*: read/awrite
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 6,
|     -  *Default value*: [0x00, 0x0A, 0x35, 0x01, 0x02, 0x03]

|  -  **fact\_network\_forceAutoNegTime** - The time after which the
|     auto-negotiation of the Ethernet connection will be forced if the
|     connection is not established.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 255
|     -  *Default value*: 5
|     -  *Units*: s

|  -  **fact\_network\_webSockServicePort** - Port number for the service
|     data transmission WEB-socket. Used by the Web-page.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 16384
|     -  *Max value*: 65535
|     -  *Default value*: 50002

|  -  **fact\_network\_webSockDataPort** - Port number for the large data
|     transmission WEB-socket. Used by the Web-page.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 16384
|     -  *Max value*: 65535
|     -  *Default value*: 50003

|  -  **fact\_network\_webSockMathPort** - Port number for the math data
|     transmission WEB-socket. Used by the Web-page.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: 16384
|     -  *Max value*: 65535
|     -  *Default value*: 50004

|  -  **fact\_laser\_waveLength** - The wavelength of the laser, installed
|     in the device.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 10000
|     -  *Default value*: 650
|     -  *Units*: nm

|  -  **fact\_laser\_minValue** - Minimum DAC value. At this value, the
|     laser stops emitting light.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 4095
|     -  *Default value*: 0

|  -  **fact\_laser\_maxValue** - Maximum DAC value. At this value, the
|     laser starts to emit light with maximum power.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 4095
|     -  *Default value*: 4095

|  -  **fact\_eip\_identity\_vendorID** - Identification number for the
|     manufacturer of an EtherNet/IP device.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Default value*: 1588

|  -  **fact\_eip\_identity\_deviceType** - The list of device types is
|     managed by ODVA and CI. It is used to identify the device profile
|     that a particular product is using.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Max value*: 65535
|     -  *Default value*: 0x2B

|  -  **fact\_eip\_identity\_productCode** - Product identifier according
|     to developer documentation.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Default value*: 627

|  -  **fact\_eip\_identity\_rev** - The Revision attribute, which consists
|     of major and minor revisions, identifies the revision of the item the
|     Identity Object is representing.
|     -  *Access*: read
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 2,
|     -  *Default value*: [1, 0]

|  -  **fact\_eip\_identity\_status** - Represents the current status of
|     the entire device. Its value changes as the state of the device
|     changes.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Enum*:
|        -  Owned - the device (or an object within the device) has an
|           owner,
|        -  Configured - the application of the device has been configured
|           to do something different than the “out–of–box” default,
|        -  Minor Recoverable Fault - the device detected a problem with
|           itself, which is thought to be recoverable. The problem does
|           not cause the device to go into one of the faulted states,
|        -  Minor Unrecoverable Fault- the device detected a problem with
|           itself, which is thought to be unrecoverable. The problem does
|           not cause the device to go into one of the faulted states,
|        -  Major Recoverable Fault - the device detected a problem with
|           itself, which caused the device to go into the “Major
|           Recoverable Fault” state,
|        -  Major Unrecoverable Fault - the device detected a problem with
|           itself, which caused the device to go into the “Major
|           Unrecoverable Fault” state
|     -  *Default value*: 0

|  -  **fact\_eip\_tcpIntrf\_status** - is a bitmap that shall indicate the
|     status of the TCP/IP network interface.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Enum*:
|        -  No configured - The Interface Configuration attribute has not
|           been configured,
|        -  Configured - The Interface Configuration attribute contains
|           configuration obtained from BOOTP, DHCP or nonvolatile storage,
|        -  Hardware Configured - The IP address member of the Interface
|           Configuration attribute contains configuration, obtained from
|           hardware settings,
|        -  Mcast Pending - Indicates a pending configuration change in the
|           TTL Value and/or Mcast Config attributes,
|        -  Interface Configuration Pending - Indicates a pending
|           configuration change in the Interface Configuration attribute,
|        -  Address Conflict Detection Status - Indicates when an IP
|           address conflict has been detected by ACD
|     -  *Default value*: 0

|  -  **fact\_eip\_tcpIntrf\_capability** - is a bitmap that indicates the
|     device’s support for optional network configuration capability.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Enum*:
|        -  BOOTP Client - the device is capable of obtaining its network
|           configuration via BOOTP,
|        -  DNS Client - the device is capable of resolving host names by
|           querying a DNS server,
|        -  DHCP Client - the device is capable of obtaining its network
|           configuration via DHCP,
|        -  Configuration Settable - the Interface Configuration attribute
|           is settable,
|        -  Hardware Configurable - the IP Address member of the Interface
|           Configuration attribute can be obtained from hardware settings
|           (e.g., pushwheel, thumbwheel, etc.),
|        -  Interface Configuration Change Requires Reset - the device
|           requires a restart in order for a change to the Interface
|           Configuration attribute to take effect,
|        -  Address Conflict Detection Capable - the device is capable of
|           ACD
|     -  *Default value*: 0x14

|  -  **fact\_eip\_tcpIntrf\_control** - is a bitmap used to control
|     network configuration options.
|     -  *Access*: read
|     -  *Type*: uint32\_t
|     -  *Enum*:
|        -  Static ip mode - The device shall use statically-assigned IP
|           configuration values,
|        -  BOOTP mode - The device shall obtain its interface
|           configuration values via BOOTP,
|        -  DHCP mode - The device shall obtain its interface configuration
|           values via DHCP
|        -  DNS Enable - the device shall resolve host names by querying a
|           DNS server
|     -  *Default value*: 0

|  -  **fact\_eip\_tcpIntrf\_phyLink** - identifies the object associated
|     with the underlying physical communications interface (e.g., an 802.3
|     interface).
|     -  *Access*: read
|     -  *Type*: u32\_arr\_t
|     -  *Max value*: 255
|     -  *Max elements*: 6
|     -  *Default value*: [0x20, 0xF6, 0x24, 0x01]

|  -  **fact\_eip\_tcpIntrf\_inactTimeout** - is used to enable TCP socket
|     cleanup (closing) when the defined number of seconds have elapsed
|     with no Encapsulation activity.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Max value*: 255
|     -  *Default value*: 120

|  -  **fact\_smart\_enabled** - Turn on and off the capabilities of a
|     smart device.
|     -  *Access*: read/awrite
|     -  *Type*: uint32\_t
|     -  *Min value*: FALSE
|     -  *Max value*: TRUE
|     -  *Default value*: FALSE

WEB API v1
===============================================================================

Using the easy-to-use WEB API, the user can get information about the
device, read or write the value of the parameter. Also, through the WEB
API, the device can execute some commands. A complete list of commands
supported through this access is given in the description of the
commands. The WEB API examples use the factory IP address of the device
and presented as they should be typed in the address bar of the browser.
If it has been changed by the user, the IP address of the device should
be used.

Quick device info
-------------------------------------------------------------------------------

|  -  **/hello** - Getting general information about the device in JSON
|     format.
|     -  *GET*:
|        -  192.168.1.30/hello

|  -  **/api/v1/config/commands** - Getting the list of commands, supported
|     by the device. The formalized description will contain the command
|     name, WEB API access capability, command identifier and access mode.
|     -  *GET*:
|        -  192.168.1.30/api/v1/config/commands

|  -  **/api/v1/config/returnCodes** - Getting a text description of the
|     codes of operation results and errors, returned by the device.
|     -  *GET*:
|        -  192.168.1.30/api/v1/config/returnCodes

Device parameters
-------------------------------------------------------------------------------

|  -  **/api/v1/config/params** - Getting general information about all
|     device parameters in JSON format. The formalized description of the
|     parameter will contain its name, type, access mode, index in the
|     parameter array, offset for binary data, parameter data size, current
|     value, default value, minimum and maximum values, parameter value
|     step, for arrays - the maximum number of elements.
|     -  *GET*:
|        -  192.168.1.30/api/v1/config/params

|  -  **/api/v1/config/params/values** - Reading and writing values ​​of
|     the device parameters. For reading it is possible to request specific
|     parameters by name or index. To write a parameter, it is necessary to
|     form a "PUT" request with the parameters "parameter\_name:value".
|     -  *GET*:
|        -  192.168.1.30/api/v1/config/params/values
|        -  192.168.1.30/api/v1/config/params/values?name=fact\_general\_hardwareVer&index=120
|     -  *PUT*:
|        -  192.168.1.30/api/v1/config/params/values?user\_sensor\_framerate=100&user\_sensor\_exposure1=100000

|  -  **/api/v1/sensor** - Reading and writing CMOS-sensor registers.
|     -  *GET*:
|        -  192.168.1.30/api/v1/sensor?reg=0x5B&val=0x003F
|        -  192.168.1.30/api/v1/sensor?index=0&reg=0x5B&val=0x003F
|     -  *PUT*:
|        -  192.168.1.30/api/v1/sensor?reg=0x5B&val=0x003F
|        -  192.168.1.30/api/v1/sensor?index=0&reg=0x5B&val=0x003F

Save, restore and reboot
-------------------------------------------------------------------------------

|  -  **/api/v1/config/params/save** - Saving the current values of the
|     device parameters in non-volatile memory in user area. Saved values
|     will be used when the device is switched on again.
|     -  *GET*:
|        -  192.168.1.30/api/v1/config/params/save

|  -  **/api/v1/config/params/restore/save** - Saving the current values of
|     the device parameters in the recovery area. These parameters will be
|     applied when parameters from the user area are damaged.
|     -  *GET*:
|        -  192.168.1.30/api/v1/config/params/restore/save

|  -  **/api/v1/config/params/restore/load** - Loading device parameter
|     values from the recovery area. The loaded values will be written to
|     the user area, the device will be automatically rebooted.
|     -  *GET*:
|        -  192.168.1.30/api/v1/config/params/restore/load

|  -  **/api/v1/reboot** - Reboot the device. The parameters will be loaded
|     from the user area (if they are not damaged).
|     -  *GET*:
|        -  192.168.1.30/api/v1/reboot

Log
-------------------------------------------------------------------------------

|  -  **/api/v1/log** - Getting a log of the device with full description
|     of records.
|     -  *GET*:
|        -  192.168.1.30/api/v1/log

|  -  **/api/v1/log/content** - Getting the device log in an abbreviated
|     form - is easier to read.
|     -  *GET*:
|        -  192.168.1.30/api/v1/log/content

Authorization
-------------------------------------------------------------------------------

|  -  **/api/v1/authorization** - Authorization on the device as a
|     manufacturer - allows editing factory parameters of the device. Using
|     the "GET" request, get a token for which generate a key and send to
|     the device in the "PUT" request.
|     -  *GET*:
|        -  192.168.1.30/api/v1/authorization
|     -  *PUT*:
|        -  192.168.1.30/api/v1/authorization?key=230d84e16c0dae529098f1f1bb.....

COMMANDS
===============================================================================

The commands transmitted to the device are intended for searching
devices in the network, reading and setting parameters, downloading
service data, firmware upgrade, receiving frames generated by
CMOS-sensor and other functions. The commands and their answers are
given in the service protocol (in the current revision, RF627 protocol).
The service protocol uses UDP packets sent to the device’s network
address (parameter **user\_network\_ip**) and the service port
(parameter **user\_network\_servicePort**).

.. _rf62x_more_description_commands:

General device commands
-------------------------------------------------------------------------------

|  -  **HELLO\_JSON\_REQUEST** - Search for devices on the network. In
|     answer to the command, JSON will be sent with a description of the
|     main parameters of the device.
|     -  *URI*: /hello
|     -  *CID*: 0x0010
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON

|  -  **PARAMS\_DESCRIPTION\_REQUEST** - Getting general information about
|     all device parameters in JSON format. The formalized description of
|     the parameter will contain its name, type, access mode, index in the
|     parameter array, offset for binary data, parameter data size, current
|     value, default value, minimum and maximum values, parameter value
|     step, for arrays - the maximum number of elements.
|     -  *URI*: /api/v1/config/params
|     -  *CID*: 0x0110
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON

|  -  **COMMANDS\_DESCRIPTION\_REQUEST** - Getting the list of commands,
|     supported by the device. The formalized description will contain the
|     command name, WEB API access capability, command identifier and
|     access mode.
|     -  *URI*: /api/v1/config/commands
|     -  *CID*: 0x0210
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON

|  -  **PARAMS\_VALUES\_JSON\_REQUEST** - Reading values ​​of the device
|     parameters. For reading it is possible to request specific parameters
|     by name or index.
|     -  *URI*: /api/v1/config/params/values
|     -  *CID*: 0x0310
|     -  *Access*: unlocked
|     -  *Command payload*: JSON [name:XXXX, name:XXXX, index:XXXX...]
|     -  *Answer payload*: JSON [name:value, name:value, name:value...]

|  -  **PARAMS\_VALUES\_JSON\_WRITE** - Writing values ​​of the device
|     parameters, it is necessary to send the parameters in form of pair
|     "parameter\_name:value".
|     -  *CID*: 0x1010
|     -  *Access*: unlocked
|     -  *Command payload*: JSON [name:value, name:value, index:value...]
|     -  *Answer payload*: JSON [name:OK, name:OK, name:OK...]

|  -  **PARAMS\_VALUES\_BIN\_REQUEST** - Reading parameter values in binary
|     form. Each parameter will be stacked according to its index and size.
|     -  *CID*: 0x0410
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: BIN

|  -  **RETURN\_CODES\_JSON\_REQUEST** - Getting a text description of the
|     codes of operation results and errors, returned by the device.
|     -  *URI*: /api/v1/config/returnCodes
|     -  *CID*: 0x2010
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON

|  -  **PARAMS\_SAVE** - Saving the current values of the device parameters
|     in non-volatile memory in user area. Saved values will be used when
|     the device is switched on again.
|     -  *URI*: /api/v1/config/params/save
|     -  *CID*: 0x0510
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON [result:OK]

|  -  **PARAMS\_RESTORE\_SAVE** - Saving the current values of the device
|     parameters in the recovery area. These parameters will be applied
|     when parameters from the user area are damaged.
|     -  *URI*: /api/v1/config/params/restore/save
|     -  *CID*: 0x0610
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON [result:OK]

|  -  **PARAMS\_RESTORE\_LOAD** - Loading device parameter values from the
|     recovery area. The loaded values will be written to the user area,
|     the device will be automatically rebooted.
|     -  *URI*: /api/v1/config/params/restore/load
|     -  *CID*: 0x0710
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON [result:OK]

|  -  **AUTHORIZATION\_REQUEST** - Authorization on the device as a
|     manufacturer - allows editing factory parameters of the device.
|     -  *URI*: /api/v1/authorization
|     -  *CID*: 0x2110
|     -  *Access*: unlocked
|     -  *Command payload*: no/key
|     -  *Answer payload*: JSON

Calibration file
-------------------------------------------------------------------------------

|  -  **CALIB\_FILE\_DATA\_WRITE** - Writing a fragment of a calibration
|     file into a device.
|     -  *CID*: 0x1052
|     -  *Access*: unlocked
|     -  *Command payload*: BIN (uint32\_t: offset; uint8\_t: data[])
|     -  *Answer payload*: no

|  -  **CALIB\_FILE\_CRC16\_REQUEST** - Getting the checksum of the
|     calibration file, uploaded to the device.
|     -  *CID*: 0x1252
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: BIN (uint16\_t: CRC)

|  -  **CALIB\_FILE\_SAVE** - Saving the calibration file in a non-volatile
|     memory of the device.
|     -  *CID*: 0x2052
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: no

Profiles request
-------------------------------------------------------------------------------

|  -  **PROFILE\_CAPTURE** - Command to start measurement. It is used only
|     in the software measurement start mode (parameter
|     **user\_sensor\_syncSource** = SYNC\_SOFTWARE). When the command is
|     received, the device starts the cycle of measurement, after that, the
|     profile is calculated and a standard package with the profile is
|     sent.
|     -  *CID*: 0x0459
|     -  *Access*: unlocked
|     -  *Command payload*: BIN (uint32\_t: count (max: 16777215))
|     -  *Answer payload*: no

|  -  **PROFILE\_REQUEST** - The command to read the last calculated
|     profile. The profile will be transferred in the payload of the
|     service protocol message.
|     -  *CID*: 0x0559
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: BIN

Dump request
-------------------------------------------------------------------------------

|  -  **DUMP\_CONTENT\_REQUEST** - Request the contents of the profile
|     dump.
|     -  *CID*: 0x2259
|     -  *Access*: unlocked
|     -  *Command payload*: BIN (uint32\_t: index; uint32\_t: count)
|     -  *Answer payload*: BIN

Frame request
-------------------------------------------------------------------------------

|  -  **FRAME\_REQUEST** - Request one frame of the image, exposed by the
|     CMOS sensor.
|     -  *CID*: 0x1083
|     -  *Access*: unlocked
|     -  *Command payload*: BIN (uint32\_t: index; uint32\_t: count)
|     -  *Answer payload*: BIN (uint32\_t: offset; uint8\_t: data[])

Log request
-------------------------------------------------------------------------------

|  -  **LOG\_PART\_REQUEST** - Request a part of the device log file with a
|     full description of the entries.
|     -  *URI*: /api/v1/log
|     -  *CID*: 0x0357
|     -  *Access*: unlocked
|     -  *Command payload*: JSON {index: XXX, count: XXX}
|     -  *Answer payload*: JSON

|  -  **LOG\_CONTENT\_REQUEST** - Request the device log in an abbreviated
|     form - is easier to read.
|     -  *URI*: /api/v1/log/content
|     -  *CID*: 0x0457
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: JSON

Internal non-volatile memory
-------------------------------------------------------------------------------

|  -  **FLASH\_ERASE** - Cleaning of the internal non-volatile memory of
|     the device (execution of the command may lead to inoperability of the
|     device). The command arguments are the start address of the erase
|     area and the size of the erase area. The address must be aligned to
|     65536 bytes and the size is a multiple of 65536 bytes.
|     -  *CID*: 0x005A
|     -  *Access*: locked
|     -  *Command payload*: BIN (uint32\_t: addr; uint32\_t: size}
|     -  *Answer payload*: no

|  -  **FLASH\_FIRMWARE\_READ** - Reading the firmware of the device.
|     -  *CID*: 0x1A5A
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: BIN (uint32\_t: offset; uint8\_t: data[])

|  -  **FLASH\_FIRMWARE\_WRITE** - Write device firmware.
|     -  *CID*: 0x205A
|     -  *Access*: unlocked
|     -  *Command payload*: BIN (uint32\_t: offset; uint8\_t: data[])
|     -  *Answer payload*: no

|  -  **FLASH\_FIRMWARE\_CRC16\_REQUEST** - Request the checksum of the
|     firmware that has been uploaded to the device. The request must be
|     made before writing the firmware to the internal non-volatile memory
|     of the device.
|     -  *CID*: 0x215A
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: BIN (uint16\_t: CRC)

|  -  **FLASH\_FIRMWARE\_SAVE** - Saving the loaded firmware to the
|     internal non-volatile memory of the device. A checksum (command
|     **FLASH\_FIRMWARE\_CRC16\_REQUEST**) must be requested before saving.
|     -  *CID*: 0x225A
|     -  *Access*: unlocked
|     -  *Command payload*: no
|     -  *Answer payload*: no

Device to Web-page notification
-------------------------------------------------------------------------------

|  -  **FLASH\_FIRMWARE\_SAVE** - With this command, the device notifies
|     the Web-page of various internal events: status changes, warnings,
|     errors.
|     -  *CID*: 0x1063
|     -  *Access*: locked
|     -  *Command payload*: JSON {time: XXX, type:
|        (NTF\_INFO/NTF\_WARN/NTF\_ERR), message: TEXT}
|     -  *Answer payload*: no

Periphery commands
-------------------------------------------------------------------------------

|  -  **PERIPHERY\_TRANSFER** - Transfer of data to and from connected
|     peripheral devices.
|     -  *CID*: 0x1080
|     -  *Access*: unlocked
|     -  *Command payload*: BIN
|     -  *Answer payload*: BIN


