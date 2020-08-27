# HttpClient
Http client.
<br></br>
```C++
enum ReqResult
```
Http request result.
* Success : Successed.
* ConnectFail : Connect to server fail.
* ParseFail : Data analysis failed.
* Unknow  : Unknow.
<br></br>
```C++
HttpClient(EventLoop* loop)
```
Constructor.
* EventLoop* loop : Event loop's handle.
<br></br>
```C++
virtual ~HttpClient()
```
Destructor.
<br></br>
```C++
void setOnResp(OnRespCallback callback)
```
Set callback when receive response from the server.
* OnRespCallback callback : Response callback.
* OnRespCallback prototype : void(ReqResult, Response* )
<br></br>
```C++
void Req(uv::SocketAddr& addr,Request& req)
``
Request http.
* uv::SocketAddr& addr : Sever's address.
* Request& req : Http's resquest.