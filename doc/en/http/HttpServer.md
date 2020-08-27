# HttpServer
Http's server.
<br></br>
```C++
HttpServer(EventLoop* loop)
```
Constructor.
* EventLoop* loop : Event loop句柄。
<br></br>
```C++
void Get(std::string path, OnHttpReqCallback callback)
```
Set `GET` methon callback. 
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Post(std::string path, OnHttpReqCallback callback)
```
Set `POST` methon callback.
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Head(std::string path, OnHttpReqCallback callback)
```
Set `HEAD` methon callback. 
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Put(std::string path, OnHttpReqCallback callback)
```
Set `PUT` methon callback. 
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Delete(std::string path, OnHttpReqCallback callback)
```
Set `DELETE` methon callback. 
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Connect(std::string path, OnHttpReqCallback callback)
```
Set `CONNECT` methon callback. 
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Options(std::string path, OnHttpReqCallback callback)
```
Set `OPTIONS` methon callback.  
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Trace(std::string path, OnHttpReqCallback callback)
```
Set `TRACE` methon callback.  
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.
<br></br>
```C++
void Patch(std::string path, OnHttpReqCallback callback)
```
Set `PATCH` methon callback.   
* std::string path : Routing path，wildcards allowed.
* OnHttpReqCallback callback : Callback function.