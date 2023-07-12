#include <SocketManager/types.h>
#include <SocketManager/Socket.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace SocketManager;

Socket::Socket(const Domain domain, const Type type) : sockfd(socket(domain, type, DEFAULT_SOCKET_PROTOCOL)), domain(domain)
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
    shutdown(this->get_sockfd(), SHUT_RDWR);
    close(this->get_sockfd());
}
