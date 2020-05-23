# EventLoop
Event's loop,single-threaded operation.
<br></br>
```C++
EventLoop()
```
Constructor.
<br></br>
```C++
~EventLoop()
```
Destructor.
<br></br>
```C++
static EventLoop* DefaultLoop()
```
Get singleton loop.
<br></br>
```C++ 
int run()
```
Blocked run loop.
<br></br>
```C++ 
int runNoWait()
```
Non-blocking run loop
<br></br>
```C++ 
bool isRunInLoopThread()
```
Is it in the loop thread.
* return true：loop's thread. false: no loop's thread.
<br></br>
```C++ 
void runInThisLoop(const DefaultCallback func)
```
Register callback function to loop's event, all registered callback functions will be called.

* const DefaultCallback func  : callback function
<br></br>
```C++ 
uv_loop_t* handle()
```
Get libuv's loop handle.
<br></br>
```C++ 
static const char* GetErrorMessage(int status)
```
 <br>Get Error Info Message.</br>
 * int status ： error's code
 
