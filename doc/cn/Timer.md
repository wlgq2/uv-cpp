# Timer
定时器类。
<br></br>
```C++
Timer(EventLoop* loop, uint64_t timeout, uint64_t repeat, TimerCallback callback)
```
构造函数。
* EventLoop* loop : Event loop句柄。
* int64_t timeout :  第一次超时时间，单位毫秒。
* uint64_t repeat :  定时器周期，单位毫秒，为零为不重复。
* TimerCallback callback : 定时器回调函数。
<br></br>
```C++
virtual ~Timer()
```
析构函数。
<br></br>
```C++
void start()
```
开始定时器。
<br></br>
```C++
void close(TimerCloseComplete callback)
```
关闭定时器。
* TimerCloseComplete callback : 关闭完成回调函数，可安全析构定时器对象。
* TimerCloseComplete  : void(Timer*)。
<br></br>
```C++
void setTimerRepeat(uint64_t ms)
```
修改定时器周期。
* uint64_t ms : 定时器周，单位毫秒。