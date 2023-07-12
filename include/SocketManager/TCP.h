#include <SocketManager/types.h>
#include <SocketManager/Socket.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace SocketManager
{
    const int DEFAULT_MAX_CONNECTION = 3;
    class TCPClientSocket : private Socket
    {
    private:
        const struct sockaddr_in target_config;

    public:
        TCPClientSocket(const Domain domain, const std::string ip_to_connect, const in_port_t port_to_connect);
        void send_data(const std::string message) const;
        std::string recieve_data() const;
    };

    class TCPServerSocket : private Socket
    {
    private:
        const struct sockaddr_in self_config;
        const struct sockaddr_in target_config;

    public:
        TCPServerSocket(const Domain domain, const int sockfd, const struct sockaddr_in self_config, const struct sockaddr_in target_config);
        void send_data(const std::string message) const;
        std::string recieve_data() const;
    };

    class TCPServer : private Socket
    {
    private:
        const struct sockaddr_in self_config;
        const unsigned max_connection;

    public:
        TCPServer(const Domain domain, const Type type, const in_port_t, const int max_connection = DEFAULT_MAX_CONNECTION);
        TCPServerSocket wait_for_connection() const;
    };
}