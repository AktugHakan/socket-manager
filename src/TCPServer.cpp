#include <SocketManager/TCP.h>

using namespace SocketManager;

TCPServer::TCPServer(const Domain domain, const Type type, const in_port_t port, const int max_connection) : Socket(domain, type), max_connection(max_connection), self_config(create_sockaddr(domain, port))
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

TCPServerSocket TCPServer::wait_for_connection() const
{
    sockaddr_in client_config;
    socklen_t client_config_size;
    int connected_sockfd = accept(this->get_sockfd(), (struct sockaddr *)&(client_config), &client_config_size);
    if (connected_sockfd == -1)
    {
        throw "Connection acception failed.";
    }
    return TCPServerSocket(this->get_domain(), connected_sockfd, this->self_config, client_config);
}

inline struct sockaddr_in create_sockaddr(const Domain domain, const in_port_t port)
{
    sockaddr_in temp;
    temp.sin_addr.s_addr = INADDR_ANY;
    temp.sin_family = domain;
    temp.sin_port = htons(port);
    return temp;
}