# HttpClient
Http客户端。
<br></br>
```C++
enum ReqResult
```
Http请求结果。
* Success : 请求成功。
* ConnectFail : 连接服务器失败。
* ParseFail : 解析数据失败。
* Unknow  : 未知失败。
<br></br>
```C++
HttpClient(EventLoop* loop)
```
构造函数
* EventLoop* loop : Event loop句柄。
<br></br>
```C++
virtual ~HttpClient()
```
析构函数。
<br></br>
```C++
void setOnResp(OnRespCallback callback)
```
设置请求服务端数据回调函数。
* OnRespCallback callback : 请求回调函数。
* OnRespCallback原型 : void(ReqResult, Response* )
<br></br>
```C++
void Req(uv::SocketAddr& addr,Request& req)
```
请求一次Http。
* uv::SocketAddr& addr : 服务器地址，可由DNS模块获得。
* Request& req : Http请求数据。