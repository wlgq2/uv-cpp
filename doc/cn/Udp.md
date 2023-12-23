# Udp
Udp类。
<br></br>
```C++
Udp(EventLoop* loop)
```
构造函数。
* EventLoop* loop : Event loop句柄。
<br></br>
```C++
virtual ~Udp()
```
析构函数。
<br></br>
```C++
int bindAndRead(SocketAddr& addr)
```
绑定地址并开始读数据。
* SocketAddr& addr : 绑定地址。
* 返回值 : 0为成功。
<br></br>
```C++
int send(SocketAddr& to, const char* buf, unsigned size)
```
发送数据。
* SocketAddr& to : 发送地址。
* const char* buf : 发送数据缓存。
* unsigned size : 发送数据长度。
* 返回值 : 0 为成功。
<br></br>
```C++
void close(DefaultCallback callback)
```
关闭Udp。
* DefaultCallback callback : 关闭完成回调函数。
<br></br>
```C++
void setMessageCallback(OnUdpMessageCallback callback)
```
设置消息回调函数。
* OnUdpMessageCallback callback : 新消息回调函数。