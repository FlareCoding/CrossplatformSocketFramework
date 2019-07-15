//
//  CSFSocket.hpp
//  CrossplatformSocketFramework
//
//  Created by Albert Slepak on 7/14/19.
//  Copyright © 2019 Albert Slepak. All rights reserved.
//

#ifndef CSFSocket_hpp
#define CSFSocket_hpp
#include <memory>
#include <stdexcept>
#include <string>

class CSFSocket
{
public:
    virtual void Connect(std::string host, int port) = 0;
    virtual void Bind(std::string host, int port) = 0;
    virtual void Listen(int connections) = 0;
    virtual void Accept() = 0;
    virtual void Close() = 0;
    virtual void SetBlocking(bool blocking) = 0;
    
    virtual size_t Recv(void* result, int bufsize) = 0;
    virtual std::string Recv(int bufsize, size_t* outbytes) = 0;
    
    virtual size_t Send(void* data, int len) = 0;
    virtual size_t Send(std::string data) = 0;
    
    virtual void* GetNativeHandle() = 0;
    
    virtual ~CSFSocket() {}
};

std::shared_ptr<CSFSocket> CreateSocket();

#endif /* CSFSocket_hpp */
