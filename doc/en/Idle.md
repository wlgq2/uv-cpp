# Idle

Idle handles will run the given callback once per loop iteration.
<br></br>
```C++
Idle(EventLoop* loop)
```
Constructor.
* EventLoop* loop : EventLoop's handle.
<br></br>
```C++
virtual ~Idle()
```
Destructor.
<br></br>
```C++
void setCallback(DefaultCallback callback)
```
Set the idle callback function run in eventloop.
* DefaultCallback callback : callback function.
