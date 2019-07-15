//
//  WindowsSocket.hpp
//  CrossplatformSocketFramework
//
//  Created by Albert Slepak on 7/14/19.
//  Copyright © 2019 Albert Slepak. All rights reserved.
//

#ifndef WindowsSocket_hpp
#define WindowsSocket_hpp

#ifdef _WIN32
#include "CSFSocket.hpp"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

class WindowsSocket : public CSFSocket
{
public:
    WindowsSocket();
    
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
    SOCKET listenfd, connfd;
};

#endif /* WIN32 */
#endif /* WindowsSocket_hpp */
