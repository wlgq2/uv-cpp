# SocketAddr
IP地址协议及端口封装。
<br></br>
```C++
SocketAddr(const std::string&& ip, unsigned short port, IPV ipv = Ipv4)
```
构造函数。
* const std::string&& ip : ip地址。
* unsigned short port : 端口号。
* IPV ipv : ip协议版本，ipv4、ipv6。
<br></br>
```C++
SocketAddr(const std::SocketAddr& ip, unsigned short port, IPV ipv = Ipv4)
```
构造函数。
* const std::string& ip : ip地址。
* unsigned short port : 端口号。
* IPV ipv : ip协议版本，ipv4、ipv6。
<br></br>
```C++
SocketAddr(const sockaddr* addr, IPV ipv = Ipv4)
```
构造函数。
* const sockaddr* addr : ip地址信息。
* IPV ipv : ip协议版本，ipv4、ipv6。
<br></br>
```C++
const sockaddr* Addr()
```
获取ip地址端口sockaddr结构信息。
* 返回值: ip地址信息。
<br></br>
```C++
void toStr(std::string& str)
```
ip地址转字符串，格式"xxx.xxx.xxx.xxx:port"。
* std::string& str : 传入字符串引用，返回IP端口信息到该字符串。
<br></br>
```C++
std::string toStr()
```
ip地址转字符串，格式"xxx.xxx.xxx.xxx:port"。
* 返回值 : 返回IP端口信息到该字符串。
<br></br>
```C++
IPV Ipv()
```
返回ip版本信息。
* 返回值 : ipv4、ipv6。
<br></br>
```C++
static  void AddrToStr(uv_tcp_t* client, std::string& addrStr, IPV ipv = Ipv4)
```
获取客户端的ip及端口的字符串。
* uv_tcp_t* client : 客户端连接句柄。
* std::string& addrStr : 输入字符串，返回ip地址端口信息。
* IPV ipv : ip协议版本，ipv4、ipv6。
<br></br>
```C++
static  uint16_t  GetIpAndPort(const sockaddr_storage* addr, std::string& out, IPV ipv = Ipv4)
```
获取ip和端口。
* const sockaddr_storage*  : 传入的socket句柄。
* std::string& out : 输入字符串，返回ip地址。
* IPV ipv : ip协议版本，ipv4、ipv6。
* 返回值 : 端口号。