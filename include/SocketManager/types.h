namespace SocketManager
{
    // --- CONST AND TYPES ---
    const int DEFAULT_SOCKET_PROTOCOL = 0;
    const long SOCK_RECV_BUFFER_LEN = 1024*1024;

    enum Domain
    {
        IPV4 = AF_INET,
        IPV6 = AF_INET6
    };
    enum Type
    {
        TCP = SOCK_STREAM,
        UDP = SOCK_DGRAM
    };
}