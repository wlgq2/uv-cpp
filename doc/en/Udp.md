# Udp
Udp class.
<br></br>
```C++
Udp(EventLoop* loop)
```
Constructor.
* EventLoop* loop : Event loop's handle.
<br></br>
```C++
virtual ~Udp()
```
Destructor.
<br></br>
```C++
int bindAndRead(SocketAddr& addr)
```
Bind address and start read data.
* SocketAddr& addr : The bound address.
* return : 0 on success, or an error code < 0 on failure.
<br></br>
```C++
int send(SocketAddr& to, const char* buf, unsigned size)
```
Send data.
* SocketAddr& to : The sending address.
* const char* buf : Sending data buffer.
* unsigned size : Sending data legth.
* return : 0 on success, or an error code < 0 on failure.
<br></br>
```C++
void close(DefaultCallback callback)
```
Close Udp.
* DefaultCallback callback : Callback function after closing.
<br></br>
```C++
void setMessageCallback(OnUdpMessageCallback callback)
```
Set callback for new message.
* OnUdpMessageCallback callback : Callback function for new messages.