#include <SocketManager/TCP.h>
#include <errno.h>
#include <fcntl.h>
#include <string>

using namespace SocketManager;

inline struct sockaddr_in create_sockaddr(const Domain domain, const in_port_t port)
{
    sockaddr_in temp;
    temp.sin_addr.s_addr = INADDR_ANY;
    temp.sin_family = domain;
    temp.sin_port = htons(port);
    return temp;
}

TCPServer::TCPServer(const Domain domain, const Type type, const in_port_t port, const int max_connection) : Socket(domain, type), max_connection(max_connection), self_config(create_sockaddr(domain, port)), blocking(true)
{
    if (bind(this->get_sockfd(), (struct sockaddr *)&(this->self_config), sizeof(this->self_config)) == -1)
    {
        throw "Socket binding error.";
    }

    if (listen(this->get_sockfd(), max_connection) == -1)
    {
        throw "Socket cannot listen.";
    }
}

TCPServerSocket TCPServer::wait_for_connection()
{
    sockaddr_in client_config;
    socklen_t client_config_size = sizeof(client_config);
    if (!(this->blocking))
    {
        int flags = fcntl(this->get_sockfd(), F_GETFL, 0);
        if (flags == -1)
        {
            throw "Switching to blocking mode for server failed.1";
        }
        flags = (flags & ~O_NONBLOCK);
        if (fcntl(this->get_sockfd(), F_SETFL, flags) == 0)
        {
            throw "Switching to blocking mode for server failed.2";
        }
        this->blocking = true;
    }
    int connected_sockfd = accept(this->get_sockfd(), (struct sockaddr *)&(client_config), &client_config_size);
    if (connected_sockfd == -1)
    {
        throw std::string("Connection acception failed. (sync)") + std::to_string(errno);
    }
    return TCPServerSocket(this->get_domain(), connected_sockfd, true);
}

TCPServerSocket TCPServer::get_queued_connection()
{
    sockaddr_in client_config;
    socklen_t client_config_size = sizeof(client_config);
    if (this->blocking)
    {
        int flags = fcntl(this->get_sockfd(), F_GETFL, 0);
        if (flags == -1)
        {
            throw "Switching to non-blocking mode for server failed.1";
        }
        flags = (flags | O_NONBLOCK);
        if (fcntl(this->get_sockfd(), F_SETFL, flags) == -1)
        {
            throw "Switching to non-blocking mode for server failed.2";
        }
        this->blocking = false;
    }

    int connected_sockfd = accept(this->get_sockfd(), (struct sockaddr *)&(client_config), &client_config_size);
    if (connected_sockfd == -1)
    {
        if (errno == EWOULDBLOCK)
        {
            throw 0;
        }
        else
        {
            throw std::string("Connection acception failed. (async)") + std::to_string(errno);
        }
    }
    return TCPServerSocket(this->get_domain(), connected_sockfd, false);
}
