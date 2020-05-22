#include "rf62Xcore.h"
#include <memory>
#include <iostream>

extern "C"{
#include <rf62X_core.h>
}

#ifdef _WIN32
#include <Ws2tcpip.h>
#include <winsock.h>
#else
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdint.h>
typedef unsigned char BYTE;
typedef int BOOL;
typedef int SOCKET;
typedef struct sockaddr SOCKADDR;
#define INVALID_SOCKET -1
#define SOCKET_ERROR (-1)
#define TRUE 1
#define FALSE 0
#endif

/** @brief Allocates an array in memory with elements initialized to 0.
 *
 * @param num - number of elements to allocate.
 * @param size - size of each element.
 * @return
 * - On success: returns a pointer to the allocated space.
 * - On error: NULL
 */
void* platform_calloc(rfSize num, rfSize size)
{
    return calloc(num, size);
}

/**
 * @brief malloc_t - ptr to function whish allocates memory block
 * Allocates a block of size bytes of memory, returning a pointer
 * to the beginning of the block.
 * @param size - Size of the memory block, in bytes.
 * @return On success, a pointer to the memory block allocated by the function.
 * If the function failed to allocate the requested block of memory, a null
 * pointer is returned.
 */
void* platform_malloc(rfSize size)
{
    return malloc(size);
}

/**
 * @brief realloc_t - ptr to function whish reallocates memory block
 * Changes the size of the memory block pointed to by ptr. The function may move
 * the memory block to a new location (whose address is returned by the function).
 * @param ptr - Pointer to a memory block previously allocated.
 * @param newsize - New size for the memory block, in bytes.
 * @return A pointer to the reallocated memory block, which may be either the
 * same as ptr or a new location.
 */
void* platform_realloc(void *ptr, rfSize newsize)
{
    return realloc(ptr, newsize);
}

/** @brief Deallocates or frees a memory block.
 *
 * @param data - Previously allocated memory block to be freed.
 */
void platform_free(void* data)
{
    free(data);
}

/**
 * @brief memset_t - ptr to function whish fills block of memory
 * Sets the first num bytes of the block of memory pointed by ptr to the
 * specified value (interpreted as an unsigned char).
 * @param memptr - Pointer to the block of memory to fill.
 * @param val - Value to be set.
 * @param num - Number of bytes to be set to the value.
 *              rfSize is an unsigned integral type.
 * @return ptr is returned.
 */
void* platform_memset(void* memptr, rfInt val, rfSize num)
{
    return memset(memptr, val, num);
}
/**
 * @brief memcpy_t - ptr to function whish copies block of memory
 * Copies the values of num bytes from the location pointed to by source
 * directly to the memory block pointed to by destination.
 * @param destination - Pointer to the destination array where the content is to
 *                      be copied, type-casted to a pointer of type void*.
 * @param source - Pointer to the source of data to be copied, type-casted to a
 *                 pointer of type const void*.
 * @param num - Number of bytes to copy. rfSize is an unsigned integral type.
 * @return destination is returned.
 */
void* platform_memcpy(void* destination, const void* source, rfSize num)
{
    return memcpy(destination, source, num);
}

/**
 * @brief memcmp_t - ptr to function whish compare two blocks of memory
 * Compares the first num bytes of the block of memory pointed by ptr1 to the
 * first num bytes pointed by ptr2, returning zero if they all match or a value
 * different from zero representing which is greater if they do not.
 * @param ptr1 - Pointer to block of memory.
 * @param ptr2 - Pointer to block of memory.
 * @param num - Number of bytes to compare.
 * @return  0 - if the contents of both memory blocks are equal,
 *         <0 - if the first byte that does not match in both memory blocks has
 * a lower value in ptr1 than in ptr2.
 *         >0 - if the first byte that does not match in both memory blocks has
 * a greater value in ptr1 than in ptr2.
 */
rfInt platform_memcmp(const void * ptr1, const void * ptr2, size_t num )
{
    return memcmp(ptr1, ptr2, num);
}

memory_platform_dependent_methods_t memory_methods = {
    platform_calloc,
    platform_malloc,
    platform_realloc,
    platform_free,

    platform_memset,
    platform_memcpy,
    platform_memcmp
};

/** @brief Method for outputting debugging information
 */
rfInt platform_printf(const rfChar* msg, ...)
{
    return printf("%s", msg);
}


iostream_platform_dependent_methods_t iostream_methods = {
    platform_printf,
    platform_printf,
    platform_printf
};

/** @brief The modbusHtoN_long_t function converts a u_long from host to TCP/IP
 *         network byte order (which is big-endian).
 *
 * @param hostlong - A 32-bit number in host byte order.
 * @return: The modbusHtoN_long_t function returns the value in TCP/IP's network
 *          byte order.
 */
rfUint32 platform_htonl(rfUint32 hostlong)
{
    return htonl(hostlong);
}

/** @brief The modbusHtoN_long_t function converts a u_long from TCP/IP network
 * order to host byte order (which is little-endian on Intel processors).
 *
 * @param netlong - A 32-bit number in TCP/IP network byte order.
 * @return: The modbusNtoH_long_t function returns the value supplied in the netlong parameter with the byte order reversed.
 */
rfUint32 platform_ntohl(rfUint32 netlong)
{
    return ntohl(netlong);
}

/** @brief The modbusHtoN_short_t function converts a u_short from host to TCP/IP network byte order (which is big-endian).
 *
 * @param hostlong - A 16-bit number in host byte order.
 * @return: The modbusHtoN_short_t function returns the value in TCP/IP's network byte order.
 */
rfUint16 platform_htons(rfUint16 hostshort)
{
    return htons(hostshort);
}

/** @brief The modbusHtoN_short_t function converts a u_short from TCP/IP network byte order to host byte order
 *
 * @param netshort - A 16-bit number in TCP/IP network byte order.
 * @return: The modbusNtoH_short_t function returns the value in host byte order.
 */
rfUint16 platform_ntohs(rfUint16 netshort)
{
    return ntohs(netshort);
}

/** @brief Pointer to TCP socket creation function
 *
 * @param af - The address family specification.
 * @param type - The type specification for the new socket.
 * @param protocol - The protocol to be used.
 * @return
 * - On success: If no error occurs, modbusCreateTcpSocket_t returns a descriptor referencing the new socket
 * - On error: NULL
 */
void* platform_create_udp_socket()
{
    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    // Close socket in case fail initialization
    if (s == INVALID_SOCKET) {
        std::cout << "open socket error" << std::endl;
        return nullptr;
    }
    return (void*)s;
}

/** @brief Pointer to the function that sets a socket option.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param level - The level at which the option is defined.
 * @param optname - The socket option for which the value is to be set.
 * @param optval - A pointer to the buffer in which the value for the requested option is specified.
 * @param optlen - The size, in bytes, of the buffer pointed to by the optval parameter.
 *  @return
 * - On success: If no error occurs, modbusSetSocketOption_t returns zero
 * - On error: -1
 */
rfInt8 platform_set_broadcast_socket_option(void* socket)
{

    int retVal;
    std::size_t sock = reinterpret_cast<std::size_t>(socket);
    if (sock == INVALID_SOCKET) {
        return -1;
    }

#if defined(linux) || defined(__linux) || defined(__linux__)
    int trueflag = 1;
    retVal = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof trueflag);
    if (retVal < 0)
    {
        return -1;
    }
#else
    const char trueflag = 1;
    retVal = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof(trueflag));
    if (retVal < 0) {
        return -1;
    }

#endif
    return retVal;
}

/** @brief Pointer to the function that sets a socket option.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param level - The level at which the option is defined.
 * @param optname - The socket option for which the value is to be set.
 * @param optval - A pointer to the buffer in which the value for the requested option is specified.
 * @param optlen - The size, in bytes, of the buffer pointed to by the optval parameter.
 *  @return
 * - On success: If no error occurs, modbusSetSocketOption_t returns zero
 * - On error: -1
 */
rfInt8 platform_set_reuseaddr_socket_option(void* socket)
{
    int retVal;
    std::size_t sock = reinterpret_cast<std::size_t>(socket);
    if (sock == INVALID_SOCKET) {
        return -1;
    }

#if defined(linux) || defined(__linux) || defined(__linux__)
    int trueflag = 1;
#else
    const char trueflag = 1;
#endif
    retVal = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof(trueflag));
    if (retVal < 0) {
        return -1;
    }


    return retVal;
}

/** @brief Pointer to the function that sets a socket option.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param level - The level at which the option is defined.
 * @param optname - The socket option for which the value is to be set.
 * @param optval - A pointer to the buffer in which the value for the requested option is specified.
 * @param optlen - The size, in bytes, of the buffer pointed to by the optval parameter.
 *  @return
 * - On success: If no error occurs, modbusSetSocketOption_t returns zero
 * - On error: -1
 */
rfInt8 platform_set_socket_option(
        void* socket, rfInt32 level, rfInt32 optname,
        const rfChar* optval, rfInt32 optlen)
{
    int retVal;
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    retVal = setsockopt(s, level, optname, optval, optlen);
    return retVal;
}

/** @brief Pointer to the function that sets a timeout for socket receive.
 *
 * @param socket - A descriptor that identifies a socket.
 * @param msec - The timeout in millisec.
 *  @return
 * - On success: If no error occurs, returns zero
 * - On error: -1
 */
rfInt8 platform_set_socket_recv_timeout(void* socket, rfInt32 msec)
{
#ifdef _WIN32
    DWORD t = msec;
#else
    timeval t;
    t.tv_sec = msec / 1000;
    t.tv_usec = (msec % 1000) * 1000;
#endif

    int retVal;
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    retVal = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&t, sizeof(t));
    if (retVal < 0) {
    return -1;
    }
    return retVal;
}

/** @brief Pointer to the function that establishes a connection to a specified socket
 *
 * @param socket - A descriptor identifying an unconnected socket.
 * @param name - A pointer to the SockAddr structure to which the connection should be established.
 * @param namelen - The length, in bytes, of the SockAddr structure pointed to by the name parameter.
 * @return
 * - On success: If no error occurs, modbusSocketConnect_t returns zero
 * - On error: -1
 */
rfUint8 platform_socket_connect(
        void* socket, rfUint32 dst_ip_addr, rfUint16 dst_port)
{
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    sockaddr_in addr = {0};
    addr.sin_addr.s_addr = htonl(dst_ip_addr);
    addr.sin_port = htons(dst_port);
    return connect(s, (sockaddr*)&addr, sizeof(sockaddr));
}

/** @brief Pointer to the function that associates a local address with a socket.
 *
 * @param socket - A descriptor identifying an unconnected socket.
 * @param name - A pointer to the SockAddr structure to which the connection should be established.
 * @param namelen - The length, in bytes, of the SockAddr structure pointed to by the name parameter.
 * @return
 * - On success: If no error occurs, modbusSocketBind_t returns zero
 * - On error: -1
 */
rfInt platform_socket_bind(
        void* socket, rfUint32 ip_addr, rfUint16 port)
{
    int retVal;
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip_addr);
    retVal = bind(s, (sockaddr*)&addr, sizeof(sockaddr));
    if (retVal < 0)
        return -1;
    return retVal;
}

/** @brief Pointer to the function that places a socket in a state in which it is listening for an incoming connection.
 *
 * @param socket - A descriptor identifying a bound, unconnected socket.
 * @param backlog - The maximum length of the queue of pending connections.
 * @return
 * - On success: If no error occurs, modbusSocketListen_t returns zero
 * - On error: -1
 */
rfUint8 platform_socket_listen(
        void* socket, rfInt32 backlog)
{
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    return listen(s, backlog);
}

/** @brief Pointer to the function that permits an incoming connection attempt on a socket.
 *
 * @param socket - A descriptor that identifies a socket that has been placed in a listening
 * 				  state with the modbusSocketListen_t function. The connection is actually
 * 				  made with the socket that is returned by accept.
 * @param name - An optional pointer to a buffer that receives the address of the connecting
 * 				entity, as known to the communications layer. The exact format of the addr
 * 				parameter is determined by the address family that was established when
 * 				the socket from the SockAddr structure was created.
 * @param addrlen - An optional pointer to an integer that contains the length of structure
 * 				   pointed to by the addr parameter.
 * @return
 * - On success: If no error occurs, modbusSocketAccept_t returns value is a handle for the
 * 				socket on which the actual connection is made
 * - On error  : NULL
 */
void* platform_socket_accept(
        void* socket, rfUint32* srs_ip_addr, rfUint16* srs_port)
{
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return nullptr;
    }

    SOCKET s_new;
    sockaddr_in addr = {0};
    socklen_t len = 0;
    s_new = accept(s, (sockaddr*)&addr, &len);
    *srs_ip_addr = ntohl(addr.sin_addr.s_addr);
    *srs_port = ntohs(addr.sin_port);
    return (void*)s_new;
}

/** @brief Pointer to the function that closes an existing socket.
 *
 * @param socket - A descriptor identifying the socket to close.
 * @return
 * - On success: If no error occurs, modbusCloseTcpSocket_t returns zero.
 * - On error: -1
 */
rfUint8 platform_close_socket(void* socket)
{
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }else
    {
#ifdef _WIN32
        return closesocket(s);
#else
        return close(s);
#endif
    }
    return -1;
}

/** @brief Pointer to the send function that sends data on a TCP connected socket
 *
 * @param socket - A descriptor identifying a connected socket.
 * @param buf - A pointer to a buffer containing the data to be transmitted.
 * @param len - The length, in bytes, of the data in buffer pointed to by the buf parameter.
 * @return
 * - On success: If no error occurs, send returns the total number of bytes sent, which can be less
 * 				than the number requested to be sent in the len parameter
 * - On error: -1
 */
rfInt platform_send_tcp_data(void* socket, const void *buf, rfSize len)
{
    if (!buf || !len) {
        return -1;
    }
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    return send(s, (char*)buf, len, 0);
}

/** @brief Pointer to the send function that sends data on a UDP socket
 *
 * @param socket - A descriptor identifying a socket.
 * @param buf - A pointer to a buffer containing the message to be sent.
 * @param len - The size of the message in bytes.
 * @param dest_addr - Points to a sockaddr_in structure containing the destination address.
 * @param addrlen - Specifies the length of the sockaddr_in structure pointed to by the dest_addr argument.
 * @return
 * - On success: If no error occurs, send returns the total number of bytes sent, which can be less
 * 				than the number requested to be sent in the len parameter
 * - On error: -1
 */
rfInt platform_send_udp_data(
        void* socket, const void *data, rfSize len,
        rfUint32 dest_ip_addr, rfUint16 dest_port)
{
    if (!data || !len) {
        return -1;
    }
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }


    sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(dest_port);
    addr.sin_addr.s_addr = htonl(dest_ip_addr);

    return sendto(s, (char*)data, len,
                  0, (sockaddr*)&addr, sizeof(sockaddr));
}

/**
 * @brief Pointer to the function that receive message from socket and capture address of sender.
 * @param sockfd - Specifies a socket descriptor from which data should be received.
 * @param buf - Specifies the buffer in which to place the message.
 * @param len - Specifies the length of the buffer area.
 * @param src_addr - Specifies a socket address structure to record the address of the message sender.
 * @param addrlen - Specifies the length of the sender's address.
 * @return If successful - the number of bytes received. On failure, it returns a value of -1
 */
rfInt platform_recv_from(
        void* socket, void *buf, rfSize len,
        rfUint32* srs_ip_addr, rfUint16* srs_port)
{
    int nret;
    socklen_t from_size;
    sockaddr_in from_addr;
    from_size = sizeof(from_addr);
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    nret = recvfrom(s, (char*)buf, (int)len, 0, (sockaddr*)&from_addr, (socklen_t*)&from_size);

    if (nret > 0)
    {
        if (srs_ip_addr != nullptr && srs_port != nullptr) {
            *srs_ip_addr = ntohl(from_addr.sin_addr.s_addr);
            *srs_port = ntohs(from_addr.sin_port);
        }
        return nret;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief Pointer to the function that receive message from socket and capture address of sender.
 * @param sockfd - Specifies a socket descriptor from which data should be received.
 * @param buf - Specifies the buffer in which to place the message.
 * @param len - Specifies the length of the buffer area.
 * @return If successful - the number of bytes received. On failure, it returns a value of -1
 */
rfInt platform_recv(void* socket, void *buf, rfSize len)
{
    rfInt nret;
    std::size_t s = reinterpret_cast<std::size_t>(socket);
    if (s == INVALID_SOCKET) {
        return -1;
    }

    nret = recv(s, (char*)buf, len, 0);

    if (nret > 0)
    {
        return nret;
    }
    else
    {
        return -1;
    }

}

network_platform_dependent_methods_t network_methods = {
    platform_htonl,
    platform_ntohl,
    platform_htons,
    platform_ntohs,

    platform_create_udp_socket,
    platform_set_broadcast_socket_option,
    platform_set_reuseaddr_socket_option,
    platform_set_socket_option,
    platform_set_socket_recv_timeout,
    platform_socket_connect,
    platform_socket_bind,
    platform_socket_listen,
    platform_socket_accept,
    platform_close_socket,

    platform_send_tcp_data,
    platform_send_udp_data,

    platform_recv_from,
    platform_recv
};

network_platform_dependent_settings_t adapter_settings =
{
    inet_addr("127.0.0.1"),
    inet_addr("255.255.255.0")
};


extern BOOL EnumAdapterAddresses();
extern void FreeAdapterAddresses();
extern int GetAdaptersCount();
extern const char* GetAdapterAddress(int index);
/* windows sockets tweaks */
extern BOOL WinSockInit();


std::string SDK::CORES::RF62X::version()
{
    /*
     * Get rf627 core version
     */
    return std::string(core_version());
}

bool SDK::CORES::RF62X::init()
{
#if (defined _WIN32)
    /*
     * Network Interface initialization.
     *
     * All processes (applications or DLLs) that call Winsock functions must
     * initialize the use of the Windows Sockets DLL before making other Winsock
     * functions calls. This also makes certain that Winsock is supported on the
     * system.
     */
    WinSockInit();
#endif

    /*
     * Cleaning detected network adapter.
     */
    FreeAdapterAddresses();
    /*
     * Retrieving addresses associated with adapters on the local computer.
     */
    EnumAdapterAddresses();

    /*
     * Initialization platform dependent methods and settings for win64 platform
     */
    init_platform_dependent_methods(
                &memory_methods, &iostream_methods,
                &network_methods, &adapter_settings);

    return true;
}
