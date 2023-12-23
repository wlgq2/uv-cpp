# TimerWheel  template<typename Type>
Time wheel.
<br></br>
```C++
TimerWheel(EventLoop* loop)
```
Constructor.
* EventLoop* loop : Event loop's handle.
<br></br>
```C++
TimerWheel(EventLoop* loop,unsigned int timeout)
```
Constructor.
* EventLoop* loop : Event loop's handle.
* unsigned int timeout : Timeout of seconds.
<br></br>
```C++
void setTimeout(unsigned int seconds)
```
Set timeout of seconds.
* unsigned int timeout : Timeout of seconds.
<br></br>
```C++
int getTimeout()
```
Get timeout of seconds.
* Return : Timeout of seconds.
<br></br>
```C++
void start()
```
Start time wheel.
<br></br>
```C++
void insert(std::shared_ptr<Type> value)
```
Insert element of time wheel.
* std::shared_ptr<Type> value : Elements of the time wheel.