# TcpAcceptor
Tcp监听类，监听接收tcp连接。
<br></br>
```C++
TcpAcceptor(EventLoop* loop, bool tcpNoDelay)
```
构造函数。
* EventLoop* loop : Event loop句柄。
* bool tcpNoDelay :  Nagle 算法, true : 不延迟 false : 延迟。
<br></br>
```C++
virtual TcpAcceptor()
```
析构函数。
<br></br>
```C++
int bind(SocketAddr& addr)
```
绑定ip地址及端口。
* SocketAddr& addr : ip及端口信息。
* 返回值 : 0为成功。
<br></br>
```C++
int listen()
```
监听地址及端口。
* 返回值 : 0为成功。
<br></br>
```C++
bool isListen()
```
是否监听状态。
* 返回值 : 是否在监听状态。
<br></br>
```C++
bool isTcpNoDelay()
```
是否开启no_delay.
* 返回值 : 开启不延时。
<br></br>
```C++
EventLoop* Loop()
```
返回Event loop句柄。
* 返回值 : EventLoop句柄。
<br></br>
```C++
void setNewConnectionCallback( NewConnectionCallback callback)
```
设置新连接回调函数。
* NewConnectionCallback callback : 新连接回调函数。
* NewConnectionCallback : void(EventLoop* ,UVTcpPtr)。