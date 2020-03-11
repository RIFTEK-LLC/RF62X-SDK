#ifndef ENDIANCONV_H
#define ENDIANCONV_H

#include "platform_types.h"

/** @file endianconv.h
 * @brief Responsible for Endianess conversion
 */

typedef enum {
    kEndianessUnknown = -1,
    kEndianessLittle = 0,
    kEndianessBig = 1
} rf_endianess;

/**
 * read/write arbitrary bits macros
 */
#define get_mask(index, size) \
    (((1 << (size)) - 1) << (index))
#define read_from(data, index, size) \
    (((data) & get_mask((index), (size))) >> (index))
#define write_to(data, index, size, value) \
    ((data) = ((data) & (~get_mask((index), (size)))) | ((value) << (index)))

/**
 * @brief get_rfInt8_from_packet. Reads rfInt8 from *buffer and
 *        converts little endian to host.
 * @param buffer - Pointer to the buffer array.
 *        This pointer will be incremented by 1;
 * @return Extracted 8 bit rfInteger value
 */
rfInt8  get_rfInt8_from_packet (rfUint8** buffer_address);

/**
 * @brief get_rfUint8_from_packet. Reads rfUint8 from *buffer and
 *        converts little endian to host.
 * @param buffer - Pointer to the buffer array.
 *        This pointer will be incremented by 1;
 * @return Extracted 8 bit rfInteger value
 */
rfUint8 get_rfUint8_from_packet(rfUint8** buffer_address);

/**
 * @brief get_rfChar_from_packet. Reads rfChar from *buffer_address and
 *        converts little endian to host.
 * @param buffer_address - Pointer to the buffer_address.
 *        This pointer will be incremented by 1;
 * @return Extracted 8 bit rfInteger value
 */
rfChar  get_rfChar_from_packet (rfUint8** buffer_address);

/**
 * @brief get_rfByte_from_packet. Reads rfByte from *buffer_address and
 *        converts little endian to host.
 * @param buffer_address - Pointer to the buffer_address .
 *        This pointer will be incremented by 1;
 * @return Extracted 8 bit rfInteger value
 */
rfByte  get_rfByte_from_packet (rfUint8** buffer_address);

/**
 * @brief get_rfBool_from_packet. Reads rfBool from *buffer_address and
 *        converts little endian to host.
 * @param buffer_address - Pointer to the buffer_address.
 *        This pointer will be incremented by 1;
 * @return Extracted 8 bit rfInteger value
 */
rfBool  get_rfBool_from_packet (rfUint8** buffer_address);

/**
 * @brief get_rfInt16_from_packet. Reads rfInt16 from *buffer_address and
 *        converts little endian to host.
 * @param buffer_address - Pointer to the buffer_address.
 *        This pointer will be incremented by 2;
 * @return Extracted 16 bit rfInteger value
 */
rfInt16  get_rfInt16_from_packet (rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief get_rfUint16_from_packet. Reads rfUint16 from *buffer_address and
 *        converts little endian to host.
 * @param buffer_address - Pointer to the buffer_address.
 *        This pointer will be incremented by 2;
 * @return Extracted 16 bit rfInteger value
 */
rfUint16 get_rfUint16_from_packet(rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief get_rfInt32_from_packet. Reads rfInt32 from *buffer_address and
 *        converts little endian to host.
 * @param buffer_address - Pointer to the buffer_address.
 *        This pointer will be incremented by 4;
 * @return Extracted 32 bit rfInteger value
 */
rfInt32  get_rfInt32_from_packet (rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief get_rfUint32_from_packet. Reads rfUint32 from *buffer_address and
 *        converts little endian to host.
 * @param buffer_address - Pointer to the buffer_address.
 *        This pointer will be incremented by 4;
 * @return Extracted 32 bit rfInteger value
 */
rfUint32 get_rfUint32_from_packet(rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief get_array_from_packet. Reads num bytes from source_buffer to
 *        destination_buffer.
 * @param destination_buffer - Pointer to the destination buffer.
 *        This pointer will be incremented by Num;
 * @param source_buffer_address - Pointer to the source buffer_address
 * @param num - count of bytes to read from array
 * @return count of readed bytes
 */
rfSize get_array_from_packet(
        rfUint8* destination_buffer, rfUint8** source_buffer_address, rfSize num);


/**
 * @brief add_rfInt8_to_packet. Write an rfInt8 to the buffer.
 * @param data - value to be written
 * @param buffer_address - pointer to the buffer_address. This pointer will
 *        be incremented by 1!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfInt8_to_packet (rfInt8 data, rfUint8** buffer_address);

/**
 * @brief add_rfUint8_to_packet. Write an rfUint8 to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 1!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfUint8_to_packet(rfUint8 data, rfUint8** buffer_address);

/**
 * @brief add_rfChar_to_packet. Write an rfChar to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 1!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfChar_to_packet (rfChar data, rfUint8** buffer_address);

/**
 * @brief add_rfByte_to_packet. Write an rfByte to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 1!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfByte_to_packet (rfByte data, rfUint8** buffer_address);

/**
 * @brief add_rfBool_to_packet. Write an rfBool to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 1!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfBool_to_packet (rfBool data, rfUint8** buffer_address);

/**
 * @brief add_rfInt16_to_packet. Write an rfInt16 to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 2!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfInt16_to_packet (
        rfInt16 data, rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief add_rfUint16_to_packet. Write an rfUint16 to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 2!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfUint16_to_packet(
        rfUint16 data, rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief add_rfrfInt32o_packet. Write an rfInt32 to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 4!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfInt32_to_packet (
        rfInt32 data, rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief add_rfrfUint32o_packet. Write an rfUint32 to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 4!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfUint32_to_packet(
        rfUint32 data, rfUint8** buffer_address, rf_endianess endian);



#ifdef _SUPPORT_64BIT_DATATYPES

/**
 * @brief get_rfUint64_from_packet. Reads rfUint64 from *buffer and
 *        converts little endian to host.
 * @param buffer - Pointer to the buffer array.
 *        This pointer will be incremented by 8;
 * @return Extracted 32 bit rfInteger value
 */
rfUint64 get_rfUint64_from_packet(rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief get_rfUint64_from_packet. Reads rfUint64 from *buffer and
 *        converts little endian to host.
 * @param buffer - Pointer to the buffer array.
 *        This pointer will be incremented by 8;
 * @return Extracted 32 bit rfInteger value
 */
rfUint64 get_rfInt64_from_packet(rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief add_rfUint64_to_packet. Write an rfUint64 to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 8!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfUint64_to_packet(
        rfUint64 data, rfUint8** buffer_address, rf_endianess endian);

/**
 * @brief add_rfUint64_to_packet. Write an rfUint64 to the buffer.
 * @param data - value to be written
 * @param buffer - buffer pointer to the buffer array. This pointer will
 *        be incremented by 8!
 * @return Length in bytes of the encoded packet
 */
rfSize add_rfInt64_to_packet(
        rfInt64 data, rfUint8** buffer_address, rf_endianess endian);

#endif



/** Identify if we are running on a big or little endian system and set
 * variable.
 */
void determine_endianess(void);

/** @brief Return the endianess identified on system startup
 * @return
 *    - -1 endianess has not been identified up to now
 *    - 0  little endian system
 *    - 1  big endian system
 */
rfInt8 get_endianess(void);


rfSize move_packet_n_bytes(
        rfInt n, rfUint8** packet_runner);

rfSize fill_next_n_packet_bytes_with(
        rfUint8 value, rfUint32 n, rfUint8** packet);

rfSize fill_next_n_packet_bytes_with_value_and_move_to_next_position(
        rfUint8 value, rfUint32 n, rfUint8** packet);

#endif // ENDIANCONV_H
