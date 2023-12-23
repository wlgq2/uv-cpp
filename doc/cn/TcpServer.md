# TcpServer
Tcp服务器类。
<br></br>
```C++
TcpServer(EventLoop* loop, bool tcpNoDelay = true)
```
构造函数。
* EventLoop* loop : Event loop句柄。
* bool tcpNoDelay :  Nagle 算法, true : 不延迟 false : 延迟。
<br></br>
```C++
virtual ~TcpServer();
```
析构函数。
<br></br>
```C++
int bindAndListen(SocketAddr& addr)
```
绑定ip地址并监听端口。
* SocketAddr& addr : ip及端口信息。
* 返回值 : 0为成功。
<br></br>
```C++
void close(DefaultCallback callback)
```
关闭服务并停止监听。
* DefaultCallback callback : 关闭完成后回调函数。
<br></br>
```C++
TcpConnectionPtr getConnection(const std::string& name)
```
获取连接对象。
* std::string& name : 连接名称，ip&&端口。
* 返回值 : Tcp connection对象。
<br></br>
```C++
void closeConnection(const std::string& name)
```
关闭并删除一个连接。
* std::string& name : 连接名称，ip&&端口。
<br></br>
```C++
void setNewConnectCallback(OnConnectionStatusCallback callback)
```
设置新连接回调函数。
* OnConnectionStatusCallback callback : 新连接回调函数。
* OnConnectionStatusCallback : void (std::weak_ptr<TcpConnection> )
<br></br>
```C++
void setConnectCloseCallback(OnConnectionStatusCallback callback)
```
设置连接被关闭回调函数。
* OnConnectionStatusCallback callback : 连接被关闭回调函数。
* OnConnectionStatusCallback : void (std::weak_ptr<TcpConnection> )
<br></br>
```C++
void setMessageCallback(OnMessageCallback callback)
```
设置消息回调函数。
* OnMessageCallback callback : 消息回调函数。
* OnMessageCallback : void (TcpConnectionPtr,const char*,ssize_t)
<br></br>
```C++
void write(TcpConnectionPtr connection,const char* buf,unsigned int size, AfterWriteCallback callback = nullptr)
```
写tcp socket缓存。
* TcpConnectionPtr connection : Tcp连接对象。
* const char* buf : 写消息指针。
* unsigned int size : 消息长度。
* AfterWriteCallback callback : 写缓存回调函数，返回成功状态。
<br></br>
```C++
void write(std::string& name,const char* buf,unsigned int size, AfterWriteCallback callback =nullptr)
```
写tcp socket缓存。
* std::string& name : Tcp连接对象名称。
* const char* buf : 写消息指针。
* unsigned int size : 消息长度。
* AfterWriteCallback callback : 写缓存回调函数，返回成功状态。
<br></br>
```C++
void writeInLoop(TcpConnectionPtr connection,const char* buf,unsigned int size,AfterWriteCallback callback)
```
写tcp socket缓存，在loop线程中执行，可以跨线程调用，线程安全。
* TcpConnectionPtr connection : Tcp连接对象。
* const char* buf : 写消息指针。
* unsigned int size : 消息长度。
* AfterWriteCallback callback : 写缓存回调函数，返回成功状态，回调函数中可以安全删除写消息buffer。
<br></br>
```C++
void writeInLoop(std::string& name,const char* buf,unsigned int size,AfterWriteCallback callback)
```
写tcp socket缓存，在loop线程中执行，可以跨线程调用，线程安全。
* std::string& name : Tcp连接对象名称。
* const char* buf : 写消息指针。
* unsigned int size : 消息长度。
* AfterWriteCallback callback : 写缓存回调函数，返回成功状态，回调函数中可以安全删除写消息buffer。
<br></br>
```C++
void setTimeout(unsigned int secend)
```
设置心跳超时。该时间内未收到客户端消息则断开连接。
* unsigned int secend : 心跳超时时间，单位为秒。