#include <SocketManager/TCP.h>

using namespace SocketManager;

TCPServerSocket::TCPServerSocket(const Domain domain, const int sockfd) : Socket(domain, sockfd)
{
}

void TCPServerSocket::send_data(const std::string message) const
{
    if (send(this->get_sockfd(), message.c_str(), message.length() + 1, 0) == -1)
    {
        throw "Sending package failed.";
    }
}

std::string TCPServerSocket::recieve_data() const
{
    char recieved_msg[SOCK_RECV_BUFFER_LEN];
    ssize_t response = recv(this->get_sockfd(), recieved_msg, SOCK_RECV_BUFFER_LEN, 0);
    if (response == -1)
    {
        throw "Recieving package failed.";
    }
    else if (response == 0)
    {
        throw "Sender closed the connection while recieving data.";
    }
    else if (response > SOCK_RECV_BUFFER_LEN)
    {
        throw "Unsufficient reciever buffer size";
    }

    return std::string(recieved_msg);
}
