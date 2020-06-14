# DnsGet
DNS查询接口
<br></br>
```C++
DNSGet(uv::EventLoop* loop)
```
构造函数
* EventLoop* loop : EventLoop对象句柄。
<br></br>
```C++
void setOnDNSCallback(OnGetIPAddrCallback callback)
```
<br>设置获取DNS回调函数</br>
OnGetIPAddrCallback  函数原型:  void (int statue, std::string& ip)
<br>int status : 状态码，获取成功则为0。</br>
<br>std::string& ip : 返回域名ip地址</br>
<br></br>

```C++
int GetIP(std::string& hostname, std::string service = "")
```

获取ip地址。
* std::string& hostname : 域名,  "www.google.com"
* std::string service : 服务命,  "http"、"ftp"、"80"……
* 返回值 : 成功则为0。
<br></br>
```C++
int GetIP(std::string&& hostname, std::string service = "");
```
同上。
<br></br>
