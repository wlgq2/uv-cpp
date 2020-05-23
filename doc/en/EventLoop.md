# EventLoop
事件轮询类，单线程。
<br></br>
```C++
EventLoop()
```
构造函数
<br></br>
```C++
~EventLoop()
```
析构函数
<br></br>
```C++
static EventLoop* DefaultLoop()
```
获取单例Loop
<br></br>
```C++ 
int run()
```
阻塞运行loop
<br></br>
```C++ 
int runNoWait()
```
非阻塞运行loop
<br></br>
```C++ 
bool isRunInLoopThread()
```
判定当前是否在loop线程中
* 返回 true：当前为loop线程 false: 当前不为loop线程
<br></br>
```C++ 
void runInThisLoop(const DefaultCallback func)
```
注册回调函数到loop线程中执行，确保每次注册的函数都能被执行。
* const DefaultCallback func 回调函数
<br></br>
```C++ 
uv_loop_t* handle()
```
返回libuv的loop句柄
<br></br>
```C++ 
static const char* GetErrorMessage(int status)
```
 <br>获取错误信息</br>
 * int status 错误码
 
