# Signal
libuv信号封装。
<br></br>
```C++
Signal(EventLoop* loop,int sig, SignalHandle handle = nullptr);
```
构造函数。
* EventLoop* loop : event loop句柄。
* int sig : 信号值。
* SignalHandle handle : 信号回调函数。
<br></br>
```C++
void close(DefaultCallback callback);
```
关闭信号回调。
* DefaultCallback callback : 关闭完成回调函数。
<br></br>
```C++
virtual ~Signal();
```
析构函数。
<br></br>

```C++
void setHandle(SignalHandle handle);
```
设置回调函数。
* SignalHandle handle ：信号回调函数。
<br></br>

```C++
static void Ignore(int sig);
```
忽略某个信号，仅linux环境下有效。
* int sig : 信号值。
<br></br>
