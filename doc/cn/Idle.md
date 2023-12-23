# Idle
空闲事件，在每次EventLoop事件中都被调用。
<br></br>
```C++
Idle(EventLoop* loop)
```
构造函数
* EventLoop* loop : EventLoop对象句柄。
<br></br>
```C++
virtual ~Idle()
```
析构函数
<br></br>
```C++
void setCallback(DefaultCallback callback)
```
注册一个回调函数到eventloop中执行。
* DefaultCallback callback : 注册运行回调函数。
