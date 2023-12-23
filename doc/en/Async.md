# Async
Asynchronous interface, used to across threads.
<br></br>
```C++
Async(EventLoop* loop)
```
Constructor.
* EventLoop* loop : EventLoop's handle.
<br></br>
```C++
virtual ~Async()
```
Destructor.
<br></br>
```C++
void runInThisLoop(DefaultCallback callback)
```
Register a callback function run in eventloop.
* DefaultCallback callback : callback function.
<br></br>
```C++
void close(DefaultCallback callback)
```
Close async object. The async's object can be released safely when the callback function is called, 

* DefaultCallback callback : Is called when the close is complete.
<br></br>
