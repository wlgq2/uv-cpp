# Async
异步接口，用于跨线程调用函数。
<br></br>
```C++
Async(EventLoop* loop)
```
构造函数
* EventLoop* loop : EventLoop对象句柄。
<br></br>
```C++
virtual ~Async()
```
析构函数
<br></br>
```C++
void runInThisLoop(DefaultCallback callback)
```
注册一个回调函数到eventloop中执行。
* DefaultCallback callback : 注册运行回调函数。
<br></br>
```C++
void close(DefaultCallback callback)
```
关闭async接口。回调函数被执行时，对象可以被安全释放。
* DefaultCallback callback : 关闭完成后的回调函数。
<br></br>
