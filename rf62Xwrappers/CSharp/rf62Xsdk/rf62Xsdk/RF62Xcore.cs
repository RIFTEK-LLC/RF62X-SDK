using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Net;
using System.Net.Sockets;


namespace SDK
{
    namespace CORES
    {
        unsafe static class RF62X
        {
            #region memory_platform
            public static unsafe class Memory
            {
                // Handle for the process heap. This handle is used in all calls to the
                // HeapXXX APIs in the methods below.
                private static readonly IntPtr s_heap = GetProcessHeap();

                // Allocates a memory block of the given size. The allocated memory is
                // automatically initialized to zero.
                public static void* Alloc(int size)
                {
                    void* result = HeapAlloc(s_heap, HEAP_ZERO_MEMORY, (UIntPtr)size);
                    if (result == null) throw new OutOfMemoryException();
                    return result;
                }

                // Copies count bytes from src to dst. The source and destination
                // blocks are permitted to overlap.
                public static void Copy(void* src, void* dst, int count)
                {
                    byte* ps = (byte*)src;
                    byte* pd = (byte*)dst;
                    if (ps > pd)
                    {
                        for (; count != 0; count--) *pd++ = *ps++;
                    }
                    else if (ps < pd)
                    {
                        for (ps += count, pd += count; count != 0; count--) *--pd = *--ps;
                    }
                }

                // Frees a memory block.
                public static void Free(void* block)
                {
                    if (!HeapFree(s_heap, 0, block)) throw new InvalidOperationException();
                }

                // Re-allocates a memory block. If the reallocation request is for a
                // larger size, the additional region of memory is automatically
                // initialized to zero.
                public static void* ReAlloc(void* block, int size)
                {
                    void* result = HeapReAlloc(s_heap, HEAP_ZERO_MEMORY, block, (UIntPtr)size);
                    if (result == null) throw new OutOfMemoryException();
                    return result;
                }

                // Returns the size of a memory block.
                public static int SizeOf(void* block)
                {
                    int result = (int)HeapSize(s_heap, 0, block);
                    if (result == -1) throw new InvalidOperationException();
                    return result;
                }

                // Heap API flags
                private const int HEAP_ZERO_MEMORY = 0x00000008;

                // Heap API functions
                [DllImport("kernel32")]
                private static extern IntPtr GetProcessHeap();

                [DllImport("kernel32")]
                private static extern void* HeapAlloc(IntPtr hHeap, int flags, UIntPtr size);

                [DllImport("kernel32")]
                private static extern bool HeapFree(IntPtr hHeap, int flags, void* block);

                [DllImport("kernel32")]
                private static extern void* HeapReAlloc(IntPtr hHeap, int flags, void* block, UIntPtr size);

                [DllImport("kernel32")]
                private static extern UIntPtr HeapSize(IntPtr hHeap, int flags, void* block);
            }

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void* calloc_t(UIntPtr num, UIntPtr size);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void* malloc_t(UIntPtr size);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void* realloc_t(void* ptr, UIntPtr newsize);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void free_t(void* data);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void* memset_t(void* memptr, int val, UIntPtr num);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void* memcpy_t(void* destination, void* source, UIntPtr num);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int memcmp_t(void* ptr1, void* ptr2, UIntPtr num);


            [StructLayout(LayoutKind.Sequential)]
            struct memory_platform_dependent_methods_t
            {
                public calloc_t rf_calloc;
                public malloc_t rf_malloc;
                public realloc_t rf_realloc;
                public free_t rf_free;

                public memset_t rf_memset;
                public memcpy_t rf_memcpy;
                public memcmp_t rf_memcmp;
            };

            #endregion

            #region iostream_platform

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int trace_info_t(byte* msg);


            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int trace_warning_t(byte* msg);


            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int trace_error_t(byte* msg);

            [StructLayout(LayoutKind.Sequential)]
            struct iostream_platform_dependent_methods_t
            {
                public trace_info_t trace_info;
                public trace_warning_t trace_warning;
                public trace_error_t trace_error;
            };

            #endregion

            #region network_platform

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate uint hton_long_t(uint hostlong);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate uint ntoh_long_t(uint netlong);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate ushort hton_short_t(ushort hostshort);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate ushort ntoh_short_t(ushort netshort);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void* create_udp_socket_t();

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte set_broadcast_socket_option_t(void* socket);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte set_reuseaddr_socket_option_t(void* socket);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte set_socket_option_t(
                void* socket, int level, int optname,
                byte* optval, int optlen);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte set_socket_recv_timeout_t(void* socket, int msec);


            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte socket_connect_t(
                void* socket, uint dst_ip_addr, ushort dst_port);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte socket_bind_t(
                void* socket, uint ip_addr, ushort port);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte socket_listen_t(
                void* socket, int backlog);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate void* socket_accept_t(
                void* socket, uint* srs_ip_addr, ushort* srs_port);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate byte close_socket_t(void* socket);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int send_tcp_data_t(void* socket, void* buf, UIntPtr len);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int send_udp_data_t(
                void* socket, void* data, UIntPtr len,
                uint dest_ip_addr, ushort dest_port);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int recv_data_from_t(
                void* sockfd, void* buf, UIntPtr len,
                uint* srs_ip_addr, ushort* srs_port);

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            delegate int recv_data_t(void* socket, void* buf, UIntPtr len);

            [StructLayout(LayoutKind.Sequential)]
            struct network_platform_dependent_methods_t
            {
                public hton_long_t hton_long;
                public ntoh_long_t ntoh_long;
                public hton_short_t hton_short;
                public ntoh_short_t ntoh_short;

                public create_udp_socket_t create_udp_socket;
                public set_broadcast_socket_option_t set_broadcast_socket_option;
                public set_reuseaddr_socket_option_t set_reuseaddr_socket_option;
                public set_socket_option_t set_socket_option;
                public set_socket_recv_timeout_t set_socket_recv_timeout;
                public socket_connect_t socket_connect;
                public socket_bind_t socket_bind;
                public socket_listen_t socket_listen;
                public socket_accept_t socket_accept;
                public close_socket_t close_socket;

                public send_tcp_data_t send_tcp_data;
                public send_udp_data_t send_udp_data;

                public recv_data_from_t recv_data_from;
                public recv_data_t recv_data;


            };




            [StructLayout(LayoutKind.Sequential)]
            struct network_platform_dependent_settings_t
            {
                public uint host_ip_addr;
                public uint host_mask;
            };

            [StructLayout(LayoutKind.Sequential)]
            struct network_platform_t
            {
                public network_platform_dependent_methods_t network_methods;
                public network_platform_dependent_settings_t network_settings;
            };

            #endregion


            private static void* PlatformCalloc(UIntPtr num, UIntPtr size)
            {
                return Memory.Alloc((int)(num.ToUInt64() * size.ToUInt64()));
            }
            private static void* PlatformMalloc(UIntPtr size)
            {
                return Memory.Alloc((int)(size));
            }
            private static void* PlatformRealloc(void* ptr, UIntPtr newsize)
            {
                return Memory.ReAlloc(ptr, (int)newsize);
            }
            private static void PlatformFree(void* data)
            {
                Memory.Free(data);
            }
            private static void* PlatformMemset(void* memptr, int val, UIntPtr num)
            {
                for (int i = 0; i < (int)(num.ToUInt64()); i++)
                {
                    ((byte*)memptr)[i] = (byte)val;
                }
                return memptr;
            }
            private static void* PlatformMemcpy(void* destination, void* source, UIntPtr num)
            {
                const int blockSize = 4096;
                byte[] block = new byte[blockSize];
                byte* d = (byte*)destination, s = (byte*)source;
                for (int i = 0, step; i < (int)(num.ToUInt64()); i += step, d += step, s += step)
                {
                    step = (int)(num.ToUInt64()) - i;
                    if (step > blockSize)
                    {
                        step = blockSize;
                    }
                    Marshal.Copy(new IntPtr(s), block, 0, step);
                    Marshal.Copy(block, 0, new IntPtr(d), step);
                }
                return source;
            }
            private static int PlatformMemcmp(void* ptr1, void* ptr2, UIntPtr num)
            {
                int res = 0;
                for (int i = 0; i < (int)(num.ToUInt64()); i++)
                {
                    if (((byte*)ptr1)[i] > ((byte*)ptr2)[i])
                    {
                        res = 1;
                        i = (int)(num.ToUInt64());
                    }
                    else if (((byte*)ptr1)[i] < ((byte*)ptr2)[i])
                    {
                        res = -1;
                        i = (int)(num.ToUInt64());
                    }
                }
                return res;
            }


            private static int PlatformPrintf(byte* msg)
            {
                Console.WriteLine(Marshal.PtrToStringAnsi((IntPtr)msg));
                return Marshal.PtrToStringAnsi((IntPtr)msg).Length;
            }

            private static uint PlatformHToNL(uint hostlong)
            {
                long ret = IPAddress.HostToNetworkOrder(hostlong);
                return hostlong;
            }
            private static uint PlatformNToHL(uint netlong)
            {
                long ret = IPAddress.NetworkToHostOrder(netlong);
                return netlong;
            }

            private static ushort PlatformHToNS(ushort hostlong)
            {
                short ret = IPAddress.HostToNetworkOrder((short)hostlong);
                return hostlong;
            }
            private static ushort PlatformNToHS(ushort netlong)
            {
                short ret = IPAddress.NetworkToHostOrder((short)netlong);
                return netlong;
            }


            static List<Socket> sockets = new List<Socket>();
            private static void* PlatformCreateUdpSocket()
            {
                sockets.Add(new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp));
                return (void*)((sockets[sockets.Count - 1]).Handle);
            }

            private static byte PlatformSetBroadcastSocketOption(void* socket)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        sockets[i].SetSocketOption(SocketOptionLevel.Socket, System.Net.Sockets.SocketOptionName.Broadcast, true);
                        return 0;
                    }
                }
                return 1;
            }

            private static byte PlatformSetReuseAddressSocketOption(void* socket)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        sockets[i].SetSocketOption(SocketOptionLevel.Socket, System.Net.Sockets.SocketOptionName.ReuseAddress, true);
                        sockets[i].SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ExclusiveAddressUse, false);
                        return 0;
                    }
                }
                return 1;
            }

            private static byte PlatformSetSocketOption(
                void* socket, int level, int optname,
                byte* optval, int optlen)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        sockets[i].SetSocketOption((SocketOptionLevel)level, (System.Net.Sockets.SocketOptionName)optname, *optval);
                        if ((System.Net.Sockets.SocketOptionName)optname == SocketOptionName.ReuseAddress)
                        {
                            sockets[i].SetSocketOption((SocketOptionLevel)level, SocketOptionName.ExclusiveAddressUse, false);
                        }
                        return 0;
                    }
                }
                return 1;
            }

            private static byte PlatformSetSocketRecvTimeout(void* socket, int msec)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        sockets[i].SetSocketOption(SocketOptionLevel.Socket, System.Net.Sockets.SocketOptionName.ReceiveTimeout, msec);
                        return 0;
                    }
                }
                return 1;
            }

            private static byte PlatformSocketConnect(void* socket, uint dst_ip_addr, ushort dst_port)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if ((void*)(sockets[i].Handle) == socket)
                    {
                        sockets[i].Connect(new IPAddress(dst_ip_addr), dst_port);
                        return 0;
                    }
                }
                return 1;
            }

            private static byte PlatformSocketBind(void* socket, uint ip_addr, ushort port)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        try
                        {
                            sockets[i].Bind(new IPEndPoint(new IPAddress(ip_addr), port));
                        }
                        catch (Exception)
                        {

                        }

                        return 0;
                    }
                }
                return 1;
            }

            private static byte PlatformSocketListen(void* socket, int backlog)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        sockets[i].Listen(backlog);
                        return 0;
                    }
                }
                return 1;
            }

            private static void* PlatformSocketAccept(void* socket, uint* srs_ip_addr, ushort* srs_port)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        sockets[i].Accept();
                        return (void*)sockets[i].Handle;
                    }
                }
                return null;
            }

            private static byte PlatformSocketClose(void* socket)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        sockets[i].Close();
                        sockets.RemoveAt(i);
                        return 0;
                    }
                }
                return 1;
            }

            private static int PlatformSendTcpData(void* socket, void* buf, UIntPtr len)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        byte[] arr = new byte[(int)len];
                        Marshal.Copy((IntPtr)buf, arr, 0, (int)len);
                        sockets[i].Send(arr);
                        return (int)len;
                    }
                }
                return 0;
            }

            private static int PlatformSendUdpData(void* socket, void* buf, UIntPtr len,
                uint dest_ip_addr, ushort dest_port)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        byte[] arr = new byte[(int)len];
                        Marshal.Copy((IntPtr)buf, arr, 0, (int)len);
                        IPEndPoint ip = new IPEndPoint(new IPAddress((uint)IPAddress.HostToNetworkOrder((int)dest_ip_addr)), dest_port);
                        int send = sockets[i].SendTo(arr, ip);

                        return (int)len;
                    }
                }
                return 0;
            }

            private static int PlatformRecvFrom(void* socket, void* buf, UIntPtr len,
               uint* srs_ip_addr, ushort* srs_port)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        byte[] arr = new byte[(int)len];
                        EndPoint remoteEndPoint = new IPEndPoint(IPAddress.Any, 0);
                        try
                        {
                            int r = sockets[i].ReceiveFrom(arr, ref remoteEndPoint);
                            byte[] bytes = ((IPEndPoint)remoteEndPoint).Address.GetAddressBytes();
                            *srs_ip_addr = (uint)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
                            *srs_port = (ushort)((IPEndPoint)remoteEndPoint).Port;
                            Marshal.Copy(arr, 0, (IntPtr)buf, r);
                            return r;
                        }
                        catch (Exception)
                        {
                            return -1;
                        }

                    }
                }
                return 0;

            }

            private static int PlatformRecv(void* socket, void* buf, UIntPtr len)
            {
                for (int i = 0; i < sockets.Count; i++)
                {
                    if (sockets[i].Handle.ToPointer() == socket)
                    {
                        byte[] arr = new byte[len.ToUInt64()];
                        try
                        {
                            int r = sockets[i].Receive(arr);
                            Marshal.Copy(arr, 0, (IntPtr)buf, r);
                            return r;
                        }
                        catch (Exception)
                        {
                            return 0;
                        }

                    }
                }
                return 0;
            }

            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern byte* core_version();

            [DllImport("rf62Xcore.dll", CallingConvention = CallingConvention.Cdecl)]
            private static extern void init_platform_dependent_methods(
            ref memory_platform_dependent_methods_t memory_methods,
            ref iostream_platform_dependent_methods_t iostream_methods,
            ref network_platform_dependent_methods_t network_methods,
            ref network_platform_dependent_settings_t adapter_settings);

            private static memory_platform_dependent_methods_t memory_methods;
            private static iostream_platform_dependent_methods_t iostream_methods;
            private static network_platform_dependent_methods_t network_methods;
            private static network_platform_dependent_settings_t adapter_settings;

            public static string CoreVersion()
            {
                return Marshal.PtrToStringAnsi((IntPtr)(core_version()));
            }
            public static void Init()
            {
                memory_methods = new memory_platform_dependent_methods_t()
                {
                    rf_calloc = PlatformCalloc,
                    rf_malloc = PlatformMalloc,
                    rf_realloc = PlatformRealloc,
                    rf_free = PlatformFree,

                    rf_memset = PlatformMemset,
                    rf_memcpy = PlatformMemcpy,
                    rf_memcmp = PlatformMemcmp
                };

                iostream_methods = new iostream_platform_dependent_methods_t()
                {
                    trace_info = PlatformPrintf,
                    trace_warning = PlatformPrintf,
                    trace_error = PlatformPrintf
                };

                network_methods = new network_platform_dependent_methods_t()
                {
                    hton_long = PlatformHToNL,
                    ntoh_long = PlatformNToHL,
                    hton_short = PlatformHToNS,
                    ntoh_short = PlatformNToHS,

                    create_udp_socket = PlatformCreateUdpSocket,
                    set_broadcast_socket_option = PlatformSetBroadcastSocketOption,
                    set_reuseaddr_socket_option = PlatformSetReuseAddressSocketOption,
                    set_socket_option = PlatformSetSocketOption,
                    set_socket_recv_timeout = PlatformSetSocketRecvTimeout,
                    socket_connect = PlatformSocketConnect,
                    socket_bind = PlatformSocketBind,
                    socket_listen = PlatformSocketListen,
                    socket_accept = PlatformSocketAccept,
                    close_socket = PlatformSocketClose,

                    send_tcp_data = PlatformSendTcpData,
                    send_udp_data = PlatformSendUdpData,

                    recv_data_from = PlatformRecvFrom,
                    recv_data = PlatformRecv
                };

                adapter_settings = new network_platform_dependent_settings_t()
                {
                    host_ip_addr = (uint)BitConverter.ToInt32((IPAddress.Parse("127.0.0.1").GetAddressBytes()), 0),
                    host_mask = (uint)BitConverter.ToInt32((IPAddress.Parse("255.255.255.0").GetAddressBytes()), 0)
                };

                init_platform_dependent_methods(
                    ref memory_methods,
                    ref iostream_methods,
                    ref network_methods,
                    ref adapter_settings);

            }

        }
    }
}