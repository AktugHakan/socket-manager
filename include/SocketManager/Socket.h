#pragma once

#include <SocketManager/types.h>
namespace SocketManager
{
    class Socket
    {
    private:
        const int sockfd;
        const Domain domain;

    protected:
        inline int get_sockfd() const
        {
            return sockfd;
        }
        inline Domain get_domain() const
        {
            return domain;
        }

    public:
        Socket(const Domain domain, const Type type);
        Socket(const Domain domain, const int sockfd);
        ~Socket();
    };
}