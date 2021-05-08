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
int _ifs_cnt = 0;

int GetAdaptersCount()
{
    return _ifs_cnt;
}

const char* GetAdapterAddress(int index)
{
    if (index >= 0 && index < _ifs_cnt) {
        return _ifs[index];
    }
    return NULL;
}

#if (defined _WIN32)
BOOL WinSockInit()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD( 2, 2 );
    if (WSAStartup( wVersionRequested, &wsaData ) != 0) {
        return FALSE;
    }
    return TRUE;
}

void WinSockDeinit()
{
    WSACleanup();
}

BOOL EnumAdapterAddresses()
{
    PIP_ADAPTER_ADDRESSES adapter_addresses, aa;
    PIP_ADAPTER_UNICAST_ADDRESS ua;
    DWORD rv, size;

    _ifs_cnt = 0;
    memset(_ifs, 0, sizeof(_ifs));

    rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &size);
    if (rv != ERROR_BUFFER_OVERFLOW) {
        return FALSE;
    }
    adapter_addresses = (PIP_ADAPTER_ADDRESSES)malloc(size);

    rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);
    if (rv != ERROR_SUCCESS) {
        free(adapter_addresses);
        return FALSE;
    }

    for (aa = adapter_addresses; aa != NULL; aa = aa->Next) {
        if (aa->OperStatus != IfOperStatusUp) continue;
        for (ua = aa->FirstUnicastAddress; ua != NULL; ua = ua->Next) {
            if (ua->Address.lpSockaddr->sa_family != AF_INET) continue;
            _ifs[_ifs_cnt] = (char*)malloc(64);
            memset(_ifs[_ifs_cnt], 0, 64);
            sprintf(_ifs[_ifs_cnt++], "%u.%u.%u.%u",
                    (BYTE)(ua->Address.lpSockaddr->sa_data[2]),
                    (BYTE)(ua->Address.lpSockaddr->sa_data[3]),
                    (BYTE)(ua->Address.lpSockaddr->sa_data[4]),
                    (BYTE)(ua->Address.lpSockaddr->sa_data[5]));
        }
    }

    free(adapter_addresses);
    return TRUE;
}
#else
BOOL EnumAdapterAddresses()
{
    struct ifaddrs *addrs,*tmp;

    getifaddrs(&addrs);
    tmp = addrs;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            _ifs[_ifs_cnt] = (char*)malloc(64);
            memset(_ifs[_ifs_cnt], 0, 64);
            sprintf(_ifs[_ifs_cnt++], "%u.%u.%u.%u", (BYTE)(tmp->ifa_addr->sa_data[2]), (BYTE)(tmp->ifa_addr->sa_data[3]), (BYTE)(tmp->ifa_addr->sa_data[4]), (BYTE)(tmp->ifa_addr->sa_data[5]));
        }
        tmp = tmp->ifa_next;
    }

    freeifaddrs(addrs);
    return TRUE;
}
#endif

void FreeAdapterAddresses()
{
    for(int i=0; i<_ifs_cnt; i++) {
        if (_ifs[i]) {
            free(_ifs[i]);
            _ifs[i] = NULL;
        }
    }
    _ifs_cnt = 0;
}

BOOL MatchIP(const char* ip1, const char* ip2, const char* mask)
{
    unsigned long nip1, nip2, nmask;
    nip1 = inet_addr(ip1);
    nip2 = inet_addr(ip2);
    nmask = mask ? inet_addr(mask) : inet_addr("255.255.255.0");
    nip1&=nmask;
    nip2&=nmask;
    if (nip1 == nip2)
        return TRUE;
    else
        return FALSE;
}

//BOOL MatchIP(u_long ip1, u_long ip2, u_long mask)
//{
//    ip1&=mask;
//    ip2&=mask;
//    if (ip1 == ip2)
//        return TRUE;
//    else
//        return FALSE;
//}

char* GetCompatibleInterface(const char* RemoteIP, const char* SubnetMask)
{
    for (int i=0; i<_ifs_cnt; i++)
    {
        if (MatchIP(_ifs[i], RemoteIP, SubnetMask))
            return _ifs[i];
    }
    return NULL;
}

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

BOOL MatchUDP(u_long testIP, u_long hostIP)
{
    u_long mul = testIP | hostIP;
    if (mul == hostIP)
        return TRUE;
    else
        return FALSE;
}

u_long GetUDPCompatibleInterface(u_long HostIP)
{
    for (int i=0; i<_ifs_cnt; i++)
    {
        if (MatchUDP(inet_addr(_ifs[i]), HostIP))
            return inet_addr(_ifs[i]);
    }
    return htonl(INADDR_ANY);
}

void DumpInterfaces()
{
    printf("detected network interfaces(%d):\n", _ifs_cnt);
    for (int i=0; i<_ifs_cnt; i++) {
        puts(_ifs[i]);
    }
}

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
