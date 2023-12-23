# Signal
libuv signal.
<br></br>
```C++
Signal(EventLoop* loop,int sig, SignalHandle handle = nullptr);
```
Constructor.
* EventLoop* loop : event loop's handle.
* int sig : signal value.
* SignalHandle handle : the signal callback,called when received.
<br></br>

```C++
virtual ~Signal();
```
Destructor.
<br></br>

```C++
void close(DefaultCallback callback);
```
Close signal event.
* DefaultCallback callback : callback called after close completion.
<br></br>


```C++
void setHandle(SignalHandle handle);
```
Set singal callback.
* SignalHandle handle ：the signal callback.
<br></br>

```C++
static void Ignore(int sig);
```
Ignore a signal, only valid in Linux.
* int sig : signal value.
<br></br>
