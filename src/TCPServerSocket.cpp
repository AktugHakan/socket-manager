#include <SocketManager/TCP.h>
#include <fcntl.h>
#include <sys/socket.h>

using namespace SocketManager;

TCPServerSocket::TCPServerSocket(const Domain domain, const int sockfd, bool blocking) : Socket(domain, sockfd)
{
    if (!blocking)
    {
        timeval recieve_timeout;
        recieve_timeout.tv_sec = 0;
        recieve_timeout.tv_usec = 100000;
        socklen_t a_len = sizeof(recieve_timeout);
        setsockopt(this->get_sockfd(), SOL_SOCKET, SO_RCVTIMEO, &recieve_timeout, a_len);
    }
}

void TCPServerSocket::send_string(const std::string message) const
{
    if ((send(this->get_sockfd(), message.c_str(), message.length() + 1, 0) == -1) && (errno != EWOULDBLOCK))
    {
        throw "Sending package failed.";
    }
}

std::string TCPServerSocket::recieve_string() const
{
    char recieved_msg[SOCK_RECV_BUFFER_LEN];
    ssize_t response = recv(this->get_sockfd(), recieved_msg, SOCK_RECV_BUFFER_LEN, 0);
    if ((response == -1))
    {
        if (errno == EWOULDBLOCK)
        {
            throw 0;
        }
        else
        {
            throw "Data recieve failed.";
        }
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

std::vector<uint8_t> TCPServerSocket::recieve_bytes() const
{
    uint8_t recieved_msg[SOCK_RECV_BUFFER_LEN];
    ssize_t response = recv(this->get_sockfd(), recieved_msg, SOCK_RECV_BUFFER_LEN, 0);
    if (response == -1)
    {
        throw "Recieving data failed.";
    }
    else if (response == 0)
    {
        throw "Sender closed the connection while recieving data.";
    }
    else if (response > SOCK_RECV_BUFFER_LEN)
    {
        throw "Unsufficient reciever buffer size";
    }

    return std::vector<uint8_t>(recieved_msg, recieved_msg + (response - 1));
}

void TCPServerSocket::send_bytes(const std::vector<uint8_t> &buffer)
{
    if (send(this->get_sockfd(), buffer.data(), buffer.size(), 0) == -1)
    {
        throw "Sending package failed.";
    }
}

sockaddr_in TCPServerSocket::get_client_info() const
{
    sockaddr_in info;
    socklen_t info_len = sizeof(info);
    getpeername(this->get_sockfd(), (sockaddr *)&info, &info_len);
    return info;
}

bool TCPServerSocket::operator==(TCPServerSocket const &to_compare) const
{
    return this->get_sockfd() == to_compare.get_sockfd();
}