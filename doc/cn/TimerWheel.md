# TimerWheel  template<typename Type>
时间轮类。
<br></br>
```C++
TimerWheel(EventLoop* loop)
```
构造函数。
* EventLoop* loop : Event loop句柄。
<br></br>
```C++
TimerWheel(EventLoop* loop,unsigned int timeout)
```
构造函数。
* EventLoop* loop : Event loop句柄。
* unsigned int timeout : 超时时间，单位秒。
<br></br>
```C++
void setTimeout(unsigned int seconds)
```
设置超时时间，单位秒。
* unsigned int timeout : 超时时间，单位秒。
<br></br>
```C++
int getTimeout()
```
返回超时时间。
* 返回值 : 超时时间，单位秒。
<br></br>
```C++
void start()
```
开始时间轮。
<br></br>
```C++
void insert(std::shared_ptr<Type> value)
```
插入时间轮对象。
* std::shared_ptr<Type> value : 时间轮元素对象。