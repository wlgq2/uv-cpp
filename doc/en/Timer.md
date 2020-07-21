# Timer
uv timer.
<br></br>
```C++
Timer(EventLoop* loop, uint64_t timeout, uint64_t repeat, TimerCallback callback)
```
Constructor.
* EventLoop* loop : Event loop's handle.
* int64_t timeout :  The first timeout of milliseconds.
* uint64_t repeat :  Timer timeout period, do't repeat if it is zero.
* TimerCallback callback : Timer callback function.
<br></br>
```C++
virtual ~Timer()
```
Destructor.
<br></br>
```C++
void start()
```
Strat timer.
<br></br>
```C++
void close(TimerCloseComplete callback)
```
Close timer.
* TimerCloseComplete callback : Callback function after close completion, timer object can be safely destroyed in callback.
* TimerCloseComplete  : void(Timer*)。
<br></br>
```C++
void setTimerRepeat(uint64_t ms)
```
Modify the timer period.
* uint64_t ms : Timer timeout period of milliseconds.