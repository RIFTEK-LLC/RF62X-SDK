//#if (defined _WIN32 && !defined __MINGW32__)
#if (defined _WIN32)



#ifndef __MINGW32__
//#include <WinSock2.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#endif
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
//#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char BYTE;
typedef int BOOL;
typedef int SOCKET;
typedef struct sockaddr SOCKADDR;
#define SOCKET_ERROR (-1)
#define TRUE 1
#define FALSE 0
#endif

int GetAdaptersCount();

const char* GetAdapterAddress(int index);
const char* GetAdapterMasks(int index);

#if (defined _WIN32)
BOOL WinSockInit();

void WinSockDeinit();

BOOL EnumAdapterAddresses();
#else
BOOL EnumAdapterAddresses();
#endif

void FreeAdapterAddresses();

BOOL MatchIP(const char* ip1, const char* ip2, const char* mask);

char* GetCompatibleInterface(const char* RemoteIP, const char* SubnetMask);

BOOL MatchUDP(u_long testIP, u_long hostIP);

u_long GetUDPCompatibleInterface(u_long HostIP);

void DumpInterfaces();

