# TcpConnection
Tcp connection class.
<br></br>
```C++
TcpConnection(EventLoop* loop,std::string& name,UVTcpPtr client,bool isConnected = true)
```
Constructor.
* EventLoop* loop : Event loop's handle.
* std::string& name :  Connection's name,ip+port.
* UVTcpPtr client : Libuv tcp handle.
* bool isConnected  : Whether the connection is established.
<br></br>
```C++
virtual ~TcpConnection()
```
Destructor.
<br></br>
```C++
void onSocketClose()
```
Disconnected.
<br></br>
```C++
void close(std::function<void(std::string&)> callback)
```
close connection.
* std::function<void(std::string&)> callback : Callback function after closing the connection.
<br></br>
```C++
int write(const char* buf,ssize_t size,AfterWriteCallback callback)
```
Write tcp buffer.
* const char* buf : Write data buffer.
* ssize_t size : Data's length.
* AfterWriteCallback callback : Callback function after writing data.
* return : 0 for success.
<br></br>
```C++
void writeInLoop(const char* buf,ssize_t size,AfterWriteCallback callback)
```
Write tcp buffer.Force to write in event loop,thread-safe.
* const char* buf : Write data buffer.
* ssize_t size : data's length.
* AfterWriteCallback callback : Callback function after writing data.
<br></br>
```C++
void setWrapper(std::shared_ptr<ConnectionWrapper> conn)
```
Set tcp connection's wrapper.
* std::shared_ptr<ConnectionWrapper> conn : tcp connection's wrapper.
<br></br>
```C++
std::shared_ptr<ConnectionWrapper> getWrapper()
```
Get tcp connection's wrapper.
* return : tcp connection wrapper.
<br></br>
```C++
void setMessageCallback(OnMessageCallback callback)
```
Set callback while new message.
* OnMessageCallback callback : callback as new message.
<br></br>
```C++
void setConnectCloseCallback(OnCloseCallback callback)
```
Set callback while connetion closed.
* OnCloseCallback callback : callback.
<br></br>
```C++
void setConnectStatus(bool status)
```
Set connection status.
* bool status : connected/disconnected.
<br></br>
```C++
bool isConnected()
```
Get connection status.
* return : connected/disconnected.
<br></br>
```C++
const std::string& Name()
```
Get connection's name.
* return : connection's name,ip+port.
<br></br>
```C++
PacketBufferPtr getPacketBuffer()
```
Get packet buffer interface.
* return : Packet buffer interface.