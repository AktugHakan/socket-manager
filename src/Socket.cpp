#include <SocketManager/types.h>
#include <SocketManager/Socket.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace SocketManager;

Socket::Socket(const Domain domain, const Type type) : sockfd(socket(domain, type, DEFAULT_SOCKET_PROTOCOL)), domain(domain), copied(false)
{
    if (this->sockfd == -1)
    {
        throw "Socket creation error.";
    }
}

Socket::Socket(const Domain domain, const int sockfd) : sockfd(sockfd), domain(domain)
{
}

Socket::~Socket()
{
}

void Socket::shutdown_socket()
{
    shutdown(this->get_sockfd(), SHUT_RDWR);
    close(this->get_sockfd());
}

sockaddr_in Socket::get_socket_info() const
{
    sockaddr_in info;
    socklen_t info_length = sizeof(info);
    if (getsockname(this->get_sockfd(), (sockaddr *)&info, &info_length) == -1)
    {
        throw "Socket info demand is refused by system.";
    }
    return info;
}