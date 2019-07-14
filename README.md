# CrossplatformSocketFramework

CrossplatformSocketFramework (CSF) is a cross-platform C++ wrapper for network sockets.

|  |   Platform   | |
|:--------:| :-: | :-: |
| Linux    | Windows | MacOS


# CSFSocket

>CSFSocket is a superclass which can be extended to write your own socket wrapper implementation!

## 📖 Documentation


* `void Connect(std::string host, int port)`
    **Description:**&nbsp;&nbsp;Attempts to connect to a server. Can throw specific exceptions depending on the error.
    **Parameters:**
    **_host:_**&nbsp;&nbsp;&nbsp; IP address of the server to connect to
    **_port:_**&nbsp;&nbsp;&nbsp; Port number to connect to

* `void Bind(std::string host, int port)`
    **Description:**&nbsp;&nbsp;When building a server, use this function to bind a socket to an address described by parameters _host_ and _port_. Socket will be able to listen for incoming connections on this address.
    **Parameters:**
    **_host:_**&nbsp;&nbsp;&nbsp; IP address of the server to connect to
    **_port:_**&nbsp;&nbsp;&nbsp; Port number to connect to

* `void Listen(int connections)`
    **Description:**&nbsp;&nbsp;When building a server, use this function to listen for incoming connections after binding the socket to an address.
    **Parameters:**
    **_connections:_**&nbsp;&nbsp;&nbsp; Number of connections server can handle simultaneously.

* `void Accept()`
    **Description:**&nbsp;&nbsp;Accepts an incoming connection.

* `void Close()`
    **Description:**&nbsp;&nbsp;Terminates the connection and closes the network socket.

* `void SetBlocking(bool blocking)`
    **Description:**&nbsp;&nbsp;Sets blocking property of the socket. If socket is blocking, when `Recv` is called, it hangs the thread until incoming data is received. Nonblocking socket would let program continue execution even if no incoming data is available at the time.
    **Parameters:**
    **_blocking:_**&nbsp;&nbsp;&nbsp; Specifies blocking state in which to put the socket.

* `size_t Recv(void* result, int bufsize)`
    **Description:**&nbsp;&nbsp;Checks if there is any incoming data available to read. If the socket is _blocking_, thread execution will be held until data becomes available. If the socket is _nonblocking_, even if no data is available, program will continue execution.
    **Parameters:**
    **_result:_**&nbsp;&nbsp;&nbsp; Buffer which received data will be put into
    **_bufsize:_**&nbsp;&nbsp;&nbsp; Specifies number of bytes to be read

    **Returns:**&nbsp; &nbsp; &nbsp;Length of the received data in bytes
    
* `std::string Recv(int bufsize, size_t* outbytes)`
    **Description:**&nbsp;&nbsp;Checks if there is any incoming data available to read. If the socket is _blocking_, thread execution will be held until data becomes available. If the socket is _nonblocking_, even if no data is available, program will continue execution.
    **Parameters:**
    **_bufsize:_**&nbsp;&nbsp;&nbsp; Specifies number of bytes to be read
    **_outbytes:_**&nbsp;&nbsp;&nbsp; Pointer to a variable which holds length of received data in bytes

    **Returns:**&nbsp; &nbsp; &nbsp;String object formed from the received data
    
* `size_t Send(void* data, int len)`
    **Description:**&nbsp;&nbsp;Sends data over the network
    **Parameters:**
    **_data:_**&nbsp;&nbsp;&nbsp; Pointer to the data to send
    **_len:_**&nbsp;&nbsp;&nbsp; Number of bytes to send

    **Returns:**&nbsp; &nbsp; &nbsp;If data was sent successfully, number of bytes sent is returned, otherwise -1 is returned and error is written to `errno`
    
* `size_t Send(std::string data)`
    **Description:**&nbsp;&nbsp;Sends data over the network
    **Parameters:**
    **_data:_**&nbsp;&nbsp;&nbsp; String data to send

    **Returns:**&nbsp; &nbsp; &nbsp;If data was sent successfully, number of bytes sent is returned, otherwise -1 is returned and error is written to `errno`
    
* `void* GetNativeHandle()`
    **Description:**&nbsp;&nbsp; Returns pointer to a native handle object.  On different platforms handle object will have a different data type.



## Example Server

```
std::shared_ptr<CSFSocket> socket = CreateSocket(); // Create socket object

socket->Bind("0.0.0.0", 4500); // Bind the socket 
socket->Listen(1); // Listening for 1 connection
socket->Accept(); // Accepting incoming client connection

size_t len;
std::string clientmsg = socket->Recv(4096, &len); // Receive client message
socket->Send("Message Received!"); // Send client the reply message

socket->Close(); // Shutting down the connection
```

## Example Client

```
std::shared_ptr<CSFSocket> socket = CreateSocket(); // Create socket object
socket->Connect("301.0.113.100", 4500); // Connect to a server

socket->Send("Hello from client!"); // Send client the reply message
std::string clientmsg = socket->Recv(4096, nullptr); // Receive server response

socket->Close(); // Shutting down the connection
```


