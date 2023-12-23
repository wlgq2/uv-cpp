# TcpAcceptor
Tcp's accepter,listen and accept tcp connection.
<br></br>
```C++
TcpAcceptor(EventLoop* loop, bool tcpNoDelay);
```
Constructor.
* EventLoop* loop : Event loop's handle.
* bool tcpNoDelay :  Nagle’s Algorithm, true : no delay, false : delay.
<br></br>
```C++
virtual TcpAcceptor()
```
Destructor.
<br></br>
```C++
int bind(SocketAddr& addr)
```
Bind socket address.
* SocketAddr& addr : Sokcet address.
* return : Successed  if return zero.
<br></br>
```C++
int listen()
```
Listen ip and port.
* return : Successed  if return zero.
<br></br>
```C++
bool isListen()
```
Is listen status.
* return : is listen.
<br></br>
```C++
bool isTcpNoDelay()
```
Is no_delay status.
* return : is no_delay.
<br></br>
```C++
EventLoop* Loop()
```
Return event loop's handle.
* return : Event loop's handle.
<br></br>
```C++
void setNewConnectionCallback( NewConnectionCallback callback)
```
Set callback while new tcp's connection.
* NewConnectionCallback callback : callback.
* NewConnectionCallback : void(EventLoop* ,UVTcpPtr)。
