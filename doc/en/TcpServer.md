# TcpServer
Tcp's Sever.
<br></br>
```C++
TcpServer(EventLoop* loop, bool tcpNoDelay = true)
```
Constructor.
* EventLoop* loop : Event loop's handle.
* bool tcpNoDelay :  Nagle’s Algorithm, true : no delay, false : delay.
<br></br>
```C++
virtual ~TcpServer();
```
Destructor.
<br></br>
```C++
int bindAndListen(SocketAddr& addr)
```
Bind and Listen ip&&port.
* SocketAddr& addr : Sokcet address.
* return :  Successed  if return zero.
<br></br>
```C++
void close(DefaultCallback callback)
```
close and stop server.
* DefaultCallback callback : Callback function after closing the server.
<br></br>
```C++
TcpConnectionPtr getConnection(const std::string& name)
```
Get new tcp's connection object.
* std::string& name : tcp connection name，ip&&port.
* return : Tcp connection object.
<br></br>
```C++
void closeConnection(const std::string& name)
```
Close and remove a tcp connection.
* std::string& name : Tcp connect name，ip&&port。
<br></br>
```C++
void setNewConnectCallback(OnConnectionStatusCallback callback)
```
Set callback when new connect.
* OnConnectionStatusCallback callback : callback function.
* OnConnectionStatusCallback : void (std::weak_ptr<TcpConnection> )
<br></br>
```C++
void setConnectCloseCallback(OnConnectionStatusCallback callback)
```
Set callback when connect closed.
* OnConnectionStatusCallback callback : callback function.
* OnConnectionStatusCallback : void (std::weak_ptr<TcpConnection> )
<br></br>
```C++
void setMessageCallback(OnMessageCallback callback)
```
Set callback when new message.
* OnMessageCallback callback : callback function.
* OnMessageCallback : void (TcpConnectionPtr,const char*,ssize_t)
<br></br>
```C++
void write(TcpConnectionPtr connection,const char* buf,unsigned int size, AfterWriteCallback callback = nullptr)
```
Write tcp buffer.
* TcpConnectionPtr connection : Tcp connection object.
* const char* buf : write message pointer.
* unsigned int size : message's length.
* AfterWriteCallback callback : Callback When the writing is complete,return execution error status.
<br></br>
```C++
void write(std::string& name,const char* buf,unsigned int size, AfterWriteCallback callback =nullptr)
```
Write tcp buffer.
* std::string& name : Tcp connection name.
* const char* buf : write message pointer.
* unsigned int size : message's length.
* AfterWriteCallback callback : Callback When the writing is complete,return execution error status.
<br></br>
```C++
void writeInLoop(TcpConnectionPtr connection,const char* buf,unsigned int size,AfterWriteCallback callback)
```
Write tcp buffer run in event loop,thread safe.
* TcpConnectionPtr connection : Tcp connection object.
* const char* buf : write message pointer.
* unsigned int size : message's length.
* AfterWriteCallback callback : Callback When the writing is complete,return execution error status and message buffer can be deleted safe.
<br></br>
```C++
void writeInLoop(std::string& name,const char* buf,unsigned int size,AfterWriteCallback callback)
```
Write tcp buffer run in event loop,thread safe.
* std::string& name : Tcp connection name.
* const char* buf : write message pointer.
* unsigned int size : message's length.
* AfterWriteCallback callback : Callback When the writing is complete,return execution error status and message buffer can be deleted safe.
<br></br>
```C++
void setTimeout(unsigned int secend)
```
Set the heartbeat timeout
* unsigned int secend : Heartbeat timeout seconds