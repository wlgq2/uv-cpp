# TcpClient
Tcp客户端类。
<br></br>
```C++
TcpClient(EventLoop* loop,bool tcpNoDelay = true);
```
构造函数。
* EventLoop* loop : Event loop句柄。
* bool tcpNoDelay :  Nagle 算法, true : 不延迟 false : 延迟。
<br></br>
```C++
virtual ~TcpClient();
```
析构函数。
<br></br>
```C++
bool isTcpNoDelay();
```
返回是否关闭nagle算法。
* 返回值 : 是否关闭nagle算法。
<br></br>
```C++
void setTcpNoDelay(bool isNoDelay)
```
设置是否开启nagle算法。
* bool isNoDelay : 关闭negle算法。
<br></br>
```C++
void connect(SocketAddr& addr)
```
连接服务器。
* SocketAddr& addr : 服务器地址。
<br></br>
```C++
void close(std::function<void(uv::TcpClient*)> callback)
```
关闭客户端。
* std::function<void(uv::TcpClient*)> callback : 关闭完成回调函数，参数为Client指针，回调被调用可以安全删除客户端对象。
<br></br>
```C++
void write(const char* buf, unsigned int size, AfterWriteCallback callback = nullptr)
```
写tcp socket缓存。
* const char* buf : 写消息指针。
* unsigned int size : 消息长度。
* AfterWriteCallback callback : 写缓存回调函数，返回成功状态。
<br></br>
```C++
void writeInLoop(const char* buf, unsigned int size, AfterWriteCallback callback)
```
写tcp socket缓存，在loop线程中执行，可以跨线程调用，线程安全。
* const char* buf : 写消息指针。
* unsigned int size : 消息长度。
* AfterWriteCallback callback : 写缓存回调函数，返回成功状态，回调函数中可以安全删除写消息buffer。
<br></br>
```C++
void setConnectStatusCallback(ConnectStatusCallback callback);
```
设置连接状态改变回调函数。断开连接、连接成功、连接失败。
* ConnectStatusCallback callback : 连接状态改变回调函数。
* ConnectStatusCallback格式  : void(ConnectStatus) 
<br></br>
```C++
void setMessageCallback(NewMessageCallback callback)
```
设置新消息回调函数。
* NewMessageCallback callback : 新消息回调函数。
* NewMessageCallback格式 : void(const char*,ssize_t)
<br></br>
```C++
EventLoop* Loop();
```
返回Event loop句柄。
* 返回值 : Event loop句柄。
<br></br>
```C++
PacketBufferPtr getCurrentBuf()
```
返回数据包缓存接口。
* 返回值 : 返回PacketBufferPtr缓存接口，用于缓存解析消息包数据。
    
    

    
    