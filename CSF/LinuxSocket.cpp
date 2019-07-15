//
//  LinuxSocket.cpp
//  CrossplatformSocketFramework
//
//  Created by Albert Slepak on 7/14/19.
//  Copyright © 2019 Albert Slepak. All rights reserved.
//

#include "LinuxSocket.hpp"
#ifndef _WIN32

LinuxSocket::LinuxSocket() {}

void LinuxSocket::Connect(std::string host, int port)
{
    connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd < 0)
    {
        throw "Failed to create socket.";
        return;
    }
    
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &(serv_addr.sin_addr)) <= 0)
    {
        throw "Invalid host address.";
        return;
    }
    
    int result = connect(connfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (result < 0)
    {
        throw "Failed to connect to the server.";
        return;
    }
}

void LinuxSocket::Bind(std::string host, int port)
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd <= 0)
    {
        throw "Failed to create listening socket.";
        return;
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &(serv_addr.sin_addr)) <= 0)
    {
        throw "Invalid host address.";
        return;
    }
    
    int result = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (result < 0)
    {
        throw "Failed to bind listening socket.";
        return;
    }
}

void LinuxSocket::Listen(int connections)
{
    int result = listen(listenfd, connections);
    if (result < 0)
    {
        throw "Failed to listen for connections.";
        return;
    }
}

void LinuxSocket::Accept()
{
    socklen_t clilen = sizeof(serv_addr);
    connfd = accept(listenfd, (struct sockaddr*)&serv_addr, (socklen_t*)&clilen);
    if (connfd < 0)
    {
        throw "Failed to accept client connection.";
        return;
    }
}

void LinuxSocket::Close()
{
    close(listenfd);
    close(connfd);
}

void LinuxSocket::SetBlocking(bool blocking)
{
    int flags = fcntl(connfd, F_GETFL, 0);
    if (flags == -1)
    {
        throw "Error retrieving current socket blocking state.";
        return;
    }
    
    flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    
    int result = fcntl(connfd, F_SETFL, flags);
    if (result == -1)
    {
        throw "Failed to set socket blocking state.";
        return;
    }
}

size_t LinuxSocket::Recv(void *result, int bufsize)
{
    return recv(connfd, result, bufsize, 0);
}

std::string LinuxSocket::Recv(int bufsize, size_t* outbytes)
{
    std::string result = "";
    
    char buffer[bufsize];
    size_t bytes = recv(connfd, buffer, bufsize, 0);
    
    if (bytes > 0)
        result = std::string(buffer, 0, bytes);
    
    if (outbytes != nullptr)
        *outbytes = bytes;
    
    return result;
}

size_t LinuxSocket::Send(void *data, int len)
{
    return send(connfd, data, len, 0);
}

size_t LinuxSocket::Send(std::string data)
{
    return send(connfd, data.c_str(), data.size(), 0);
}

#endif
