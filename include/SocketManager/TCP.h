#pragma once

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
        using Socket::get_socket_info;
        using Socket::shutdown_socket;
    };

    class TCPServerSocket : private Socket
    {
    public:
        TCPServerSocket(const Domain domain, const int sockfd, bool blocking);
        void send_data(const std::string message) const;
        std::string recieve_data() const;
        sockaddr_in get_client_info() const;
        using Socket::get_socket_info;
        using Socket::shutdown_socket;
        bool operator==(TCPServerSocket const &to_compare) const;
    };

    class TCPServer : private Socket
    {
    private:
        const unsigned max_connection;
        const struct sockaddr_in self_config;
        bool blocking;

    public:
        TCPServer(const Domain domain, const Type type, const in_port_t, const int max_connection = DEFAULT_MAX_CONNECTION);
        TCPServerSocket wait_for_connection();
        TCPServerSocket get_queued_connection();
        using Socket::get_socket_info;
        using Socket::shutdown_socket;
    };
}