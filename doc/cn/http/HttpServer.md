# HttpServer
Http服务器。
<br></br>
```C++
HttpServer(EventLoop* loop)
```
构造函数
* EventLoop* loop : Event loop句柄。
<br></br>
```C++
void Get(std::string path, OnHttpReqCallback callback)
```
设置Get请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Post(std::string path, OnHttpReqCallback callback)
```
设置Post请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Head(std::string path, OnHttpReqCallback callback)
```
设置Head请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Put(std::string path, OnHttpReqCallback callback)
```
设置Put请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Delete(std::string path, OnHttpReqCallback callback)
```
设置Delete请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Connect(std::string path, OnHttpReqCallback callback)
```
设置Connect请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Options(std::string path, OnHttpReqCallback callback)
```
设置Options请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Trace(std::string path, OnHttpReqCallback callback)
```
设置Trace请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。
<br></br>
```C++
void Patch(std::string path, OnHttpReqCallback callback)
```
设置Patch请求回调函数。 
* std::string path : 请求路径，支持通配符、参数等。
* OnHttpReqCallback callback : 回调函数。