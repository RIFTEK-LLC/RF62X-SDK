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
char* _mfs[64];
int _mfs_cnt = 0;


int GetAdaptersCount()
{
    return _ifs_cnt;
}

int GetAdaptersMasksCount()
{
    return _mfs_cnt;
}

const char* GetAdapterAddress(int index)
{
    if (index >= 0 && index < _ifs_cnt) {
        return _ifs[index];
    }
    return NULL;
}

const char* GetAdapterMasks(int index)
{
    if (index >= 0 && index < _mfs_cnt) {
        return _mfs[index];
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

void print_adapter(PIP_ADAPTER_ADDRESSES aa)
{
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    WideCharToMultiByte(CP_ACP, 0, aa->FriendlyName, wcslen(aa->FriendlyName), buf, BUFSIZ, NULL, NULL);
    printf("adapter_name:%s\n", buf);
}

void print_addr(PIP_ADAPTER_UNICAST_ADDRESS ua)
{
    char buf[BUFSIZ];

    int family = ua->Address.lpSockaddr->sa_family;
    printf("\t%s ",  family == AF_INET ? "IPv4":"IPv6");

    memset(buf, 0, BUFSIZ);
    getnameinfo(ua->Address.lpSockaddr, ua->Address.iSockaddrLength, buf, sizeof(buf), NULL, 0,NI_NUMERICHOST);
    printf("%s\n", buf);
}

void print_prefix(PIP_ADAPTER_PREFIX_XP ua)
{
    char buf[BUFSIZ];

    int family = ua->Address.lpSockaddr->sa_family;
    printf("\t%s ",  family == AF_INET ? "IPv4":"IPv6");

    memset(buf, 0, BUFSIZ);
    getnameinfo(ua->Address.lpSockaddr, ua->Address.iSockaddrLength, buf, sizeof(buf), NULL, 0,NI_NUMERICHOST);
    printf("%s\n", buf);
}

BOOL EnumAdapterAddresses()
{

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    int dwRetVal = 0;
    int i;

    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return 1;
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return 1;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
//            printf("\tComboIndex: \t%d\n", pAdapter->ComboIndex);
//            printf("\tAdapter Name: \t%s\n", pAdapter->AdapterName);
//            printf("\tAdapter Desc: \t%s\n", pAdapter->Description);
//            printf("\tAdapter Addr: \t");
//            for (i = 0; i < pAdapter->AddressLength; i++) {
//                if (i == (pAdapter->AddressLength - 1))
//                    printf("%.2X\n", (int) pAdapter->Address[i]);
//                else
//                    printf("%.2X-", (int) pAdapter->Address[i]);
//            }
//            printf("\tIndex: \t%d\n", pAdapter->Index);
//            printf("\tType: \t");
//            switch (pAdapter->Type) {
//            case MIB_IF_TYPE_OTHER:
//                printf("Other\n");
//                break;
//            case MIB_IF_TYPE_ETHERNET:
//                printf("Ethernet\n");
//                break;
//            case MIB_IF_TYPE_TOKENRING:
//                printf("Token Ring\n");
//                break;
//            case MIB_IF_TYPE_FDDI:
//                printf("FDDI\n");
//                break;
//            case MIB_IF_TYPE_PPP:
//                printf("PPP\n");
//                break;
//            case MIB_IF_TYPE_LOOPBACK:
//                printf("Lookback\n");
//                break;
//            case MIB_IF_TYPE_SLIP:
//                printf("Slip\n");
//                break;
//            default:
//                printf("Unknown type %ld\n", pAdapter->Type);
//                break;
//            }

            PIP_ADDR_STRING IpList = &pAdapter->IpAddressList;
            while (IpList) {


            _ifs[_ifs_cnt] = (char*)malloc(64);
            memset(_ifs[_ifs_cnt], 0, 64);
            sprintf(_ifs[_ifs_cnt++], "%s",IpList->IpAddress.String);
//            printf("\tIP Address: \t%s\n", IpList->IpAddress.String);
            _mfs[_mfs_cnt] = (char*)malloc(64);
            memset(_mfs[_mfs_cnt], 0, 64);
            sprintf(_mfs[_mfs_cnt++], "%s",IpList->IpMask.String);
//            printf("\tIP Mask: \t%s\n", IpList->IpMask.String);
            IpList = IpList->Next;
            }

//            printf("\tGateway: \t%s\n", pAdapter->GatewayList.IpAddress.String);
//            printf("\t***\n");

//            if (pAdapter->DhcpEnabled) {
//                printf("\tDHCP Enabled: Yes\n");
//                printf("\t  DHCP Server: \t%s\n",
//                       pAdapter->DhcpServer.IpAddress.String);
//            } else
//                printf("\tDHCP Enabled: No\n");

//            if (pAdapter->HaveWins) {
//                printf("\tHave Wins: Yes\n");
//                printf("\t  Primary Wins Server:    %s\n",
//                       pAdapter->PrimaryWinsServer.IpAddress.String);
//                printf("\t  Secondary Wins Server:  %s\n",
//                       pAdapter->SecondaryWinsServer.IpAddress.String);
//            } else
//                printf("\tHave Wins: No\n");
            pAdapter = pAdapter->Next;
//            printf("\n");
        }
    } else {
        printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
    }

    if (pAdapterInfo)
            free(pAdapterInfo);

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
            sprintf(_ifs[_ifs_cnt++], "%u.%u.%u.%u",
                    (BYTE)(tmp->ifa_addr->sa_data[2]),
                    (BYTE)(tmp->ifa_addr->sa_data[3]),
                    (BYTE)(tmp->ifa_addr->sa_data[4]),
                    (BYTE)(tmp->ifa_addr->sa_data[5]));

            _mfs[_mfs_cnt] = (char*)malloc(64);
            memset(_mfs[_mfs_cnt], 0, 64);
            sprintf(_mfs[_mfs_cnt++], "%u.%u.%u.%u",
                    (BYTE)(tmp->ifa_netmask->sa_data[2]),
                    (BYTE)(tmp->ifa_netmask->sa_data[3]),
                    (BYTE)(tmp->ifa_netmask->sa_data[4]),
                    (BYTE)(tmp->ifa_netmask->sa_data[5]));
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

    for(int i=0; i<_mfs_cnt; i++) {
        if (_mfs[i]) {
            free(_mfs[i]);
            _mfs[i] = NULL;
        }
    }
    _mfs_cnt = 0;
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
