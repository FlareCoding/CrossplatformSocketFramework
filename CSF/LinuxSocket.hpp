//
//  LinuxSocket.hpp
//  CrossplatformSocketFramework
//
//  Created by Albert Slepak on 7/14/19.
//  Copyright © 2019 Albert Slepak. All rights reserved.
//

#ifndef LinuxSocket_hpp
#define LinuxSocket_hpp

#ifndef _WIN32
#include "CSFSocket.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

class LinuxSocket : public CSFSocket
{
public:
    LinuxSocket();
    
    void Connect(std::string host, int port) override;
    
    void Bind(std::string host, int port) override;
    
    void Listen(int connections) override;
    
    void Accept() override;
    
    void Close() override;
    
    void SetBlocking(bool blocking) override;
    
    size_t Recv(void *result, int bufsize) override;
    
    std::string Recv(int bufsize, size_t *outbytes) override;
    
    size_t Send(void *data, int len) override;
    
    size_t Send(std::string data) override;
    
    void* GetNativeHandle() override { return (void*)&connfd; };
    
private:
    int listenfd, connfd;
    sockaddr_in serv_addr;
};

#endif /* _WIN32 */
#endif /* LinuxSocket_hpp */
