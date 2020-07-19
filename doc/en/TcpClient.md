# TcpClient
Tcp's client.
<br></br>
```C++
TcpClient(EventLoop* loop,bool tcpNoDelay = true);
```
Constructor.
* EventLoop* loop : Event loop's handle.
* bool tcpNoDelay :  Nagle’s Algorithm, true : no delay, false : delay.
<br></br>
```C++
virtual ~TcpClient();
```
Destructor.
<br></br>
```C++
bool isTcpNoDelay();
```
Return enable No-Delay. 
<br></br>
```C++
void setTcpNoDelay(bool isNoDelay)
```
set enable No-Delay. 
* bool isNoDelay : Enable No-Delay
<br></br>
```C++
void connect(SocketAddr& addr)
```
Connect to server.
* SocketAddr& addr : Server's address.
<br></br>
```C++
void close(std::function<void(uv::TcpClient*)> callback)
```
Close client.
* std::function<void(uv::TcpClient*)> callback : Callback function after closing the client. 
<br></br>
```C++
void write(const char* buf, unsigned int size, AfterWriteCallback callback = nullptr)
```
Write tcp socket buffer.
* const char* buf : Write data buffer.
* unsigned int size :  Data's length.
* AfterWriteCallback callback : Callback function after writing data.
<br></br>
```C++
void writeInLoop(const char* buf, unsigned int size, AfterWriteCallback callback)
```
Write tcp buffer.Force to write in event loop,thread-safe.
* const char* buf : Write data buffer.
* unsigned int size : Data's length.
* AfterWriteCallback callback : Callback function after writing data.
<br></br>
```C++
void setConnectStatusCallback(ConnectStatusCallback callback);
```
Set callback while client's status changed.Such as disconnect,connect success,connect fail.
* ConnectStatusCallback callback : callback function.
* ConnectStatusCallback   : void(ConnectStatus) 
<br></br>
```C++
void setMessageCallback(NewMessageCallback callback)
```
Set callback when new message.
* NewMessageCallback callback : callback function.
* NewMessageCallback  : void(const char*,ssize_t)
<br></br>
```C++
EventLoop* Loop();
```
* return : Event loop's handle.
<br></br>
```C++
PacketBufferPtr getCurrentBuf()
```
Get packet buffer interface.
    
    

    
    