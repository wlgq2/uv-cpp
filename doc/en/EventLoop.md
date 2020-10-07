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
* return : Returns non-zero if uv_stop() was called and there are still active handles or requests. Returns zero in all other cases.
<br></br>
```C++ 
int runNoWait()
```
Non-blocking run loop
* return : Returns zero when done (no active handles or requests left), or non-zero if more callbacks are expected (meaning you should run the event loop again sometime in the future).
<br></br>
```C++ 
int stop()()
```
async stop event loop. the loop will stop after end of EventLoop::run() call, not EventLoop::stop().
* return : zero if success.
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
 
