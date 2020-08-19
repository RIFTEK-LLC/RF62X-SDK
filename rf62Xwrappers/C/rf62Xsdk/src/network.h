//#if (defined _WIN32 && !defined __MINGW32__)
#if (defined _WIN32)



#ifndef __MINGW32__
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#endif
#include <ws2tcpip.h>
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

/**************************************************
 */
char* _ifs[64];
int _ifs_cnt;

int GetAdaptersCount();

const char* GetAdapterAddress(int index);

#if (defined _WIN32)
BOOL WinSockInit();

void WinSockDeinit();

BOOL EnumAdapterAddresses();
#else
BOOL EnumAdapterAddresses();
#endif

void FreeAdapterAddresses();

BOOL MatchIP(const char* ip1, const char* ip2, const char* mask);

//BOOL MatchIP(u_long ip1, u_long ip2, u_long mask)
//{
//    ip1&=mask;
//    ip2&=mask;
//    if (ip1 == ip2)
//        return TRUE;
//    else
//        return FALSE;
//}

char* GetCompatibleInterface(const char* RemoteIP, const char* SubnetMask);

//u_long GetCompatibleInterface(u_long RemoteIP, u_long SubnetMask)
//{
//    if (RemoteIP)
//    {
//        for (int i=0; i<_ifs_cnt; i++)
//        {
//            if (MatchIP(inet_addr(_ifs[i]), RemoteIP, SubnetMask))
//                return inet_addr(_ifs[i]);
//        }
//    }
//    return htonl(INADDR_ANY);
//}

BOOL MatchUDP(u_long testIP, u_long hostIP);

u_long GetUDPCompatibleInterface(u_long HostIP);

void DumpInterfaces();

//BOOL BindToCompatibleInterface(SOCKET s, in_addr* addr, u_long netMask)
//{
//    u_long local_ip = INADDR_ANY;
//    u_long net_mask = netMask;
//    sockaddr_in sin_loc;
//    memset(&sin_loc, 0, sizeof(sockaddr_in));
//    sin_loc.sin_family = PF_INET;
//    local_ip = GetCompatibleInterface(addr->s_addr, net_mask);
//    sin_loc.sin_addr.s_addr = local_ip;
//    return (bind(s, reinterpret_cast<SOCKADDR*>(&sin_loc), sizeof(sin_loc)) != SOCKET_ERROR);
//}

/**************************************************
 */
