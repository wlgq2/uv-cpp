# TcpConnection
Tcp连接类。
<br></br>
```C++
TcpConnection(EventLoop* loop,std::string& name,UVTcpPtr client,bool isConnected = true)
```
构造函数。
* EventLoop* loop : Event loop句柄。
* std::string& name :  连接标识，ip+端口。
* UVTcpPtr client : libuv tcp句柄。
* bool isConnected  : 连接是否建立。
<br></br>
```C++
virtual ~TcpConnection()
```
析构函数。
<br></br>
```C++
void onSocketClose()
```
连接被断开。
<br></br>
```C++
void close(std::function<void(std::string&)> callback)
```
关闭连接。
* std::function<void(std::string&)> callback : 关闭连接完成后回调函数。
<br></br>
```C++
int write(const char* buf,ssize_t size,AfterWriteCallback callback)
```
写TCP缓存。
* const char* buf : 发送数据buffer。
* ssize_t size : 数据长度。
* AfterWriteCallback callback : 写完成回调。
* 返回值 : 0为成功。
<br></br>
```C++
void writeInLoop(const char* buf,ssize_t size,AfterWriteCallback callback)
```
写TCP缓存，强制在Eventloop轮询中写，线程安全。
* const char* buf : 发送数据buffer。
* ssize_t size : 数据长度。
* AfterWriteCallback callback : 写完成回调。
<br></br>
```C++
void setWrapper(std::shared_ptr<ConnectionWrapper> conn)
```
设置包装，用于时间轮心跳超时判定。
* std::shared_ptr<ConnectionWrapper> conn : tcp连接包装。
<br></br>
```C++
std::shared_ptr<ConnectionWrapper> getWrapper()
```
获取连接包装，用于时间轮心跳超时判定。
* 返回值 : tcp连接包装。
<br></br>
```C++
void setMessageCallback(OnMessageCallback callback)
```
设置消息回调。
* OnMessageCallback callback : 新消息回调函数。
<br></br>
```C++
void setConnectCloseCallback(OnCloseCallback callback)
```
设置连接关闭回调函数。
* OnCloseCallback callback : 连接关闭回调。
<br></br>
```C++
void setConnectStatus(bool status)
```
设置连接状态。
* bool status : 连接/断开。
<br></br>
```C++
bool isConnected()
```
获取连接状态。
* 返回值 : 连接/断开。
<br></br>
```C++
const std::string& Name()
```
获取连接标识。
* 返回值 : 连接标识，ip+端口。
<br></br>
```C++
PacketBufferPtr getPacketBuffer()
```
获取应用层包缓存接口。
* 返回值 : 应用层包缓存接口。