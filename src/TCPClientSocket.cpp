#include <SocketManager/TCP.h>

using namespace SocketManager;

inline struct sockaddr_in create_sockaddr(const Domain domain, const std::string ip, const in_port_t port)
{
    sockaddr_in temp;
    temp.sin_family = domain;
    temp.sin_port = htons(port);
    temp.sin_addr.s_addr = inet_addr(ip.c_str());
    return temp;
}

TCPClientSocket::TCPClientSocket(const Domain domain, const std::string ip_to_connect, const in_port_t port_to_connect) : Socket(domain, Type::TCP), target_config(create_sockaddr(domain, ip_to_connect, port_to_connect))
{
    if (connect(this->get_sockfd(), (struct sockaddr *)&(this->target_config), sizeof(this->target_config)) == -1)
    {
        throw "Connection to server failed";
    }
}

std::string TCPClientSocket::recieve_data() const
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

void TCPClientSocket::send_data(const std::string message) const
{
    if (send(this->get_sockfd(), message.c_str(), message.length() + 1, 0) == -1)
    {
        throw "Sending package failed.";
    }
}