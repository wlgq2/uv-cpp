# SocketAddr
IP address and port.
<br></br>
```C++
SocketAddr(const std::string&& ip, unsigned short port, IPV ipv = Ipv4)
```
Constructor.
* const std::string&& ip : ip address.
* unsigned short port : port num.
* IPV ipv : ip version,ipv4、ipv6.
<br></br>
```C++
SocketAddr(const std::SocketAddr& ip, unsigned short port, IPV ipv = Ipv4)
```
Constructor.
* const std::string& ip : ip address.
* unsigned short port : port num.
* IPV ipv : ip version,ipv4、ipv6.
<br></br>
```C++
SocketAddr(const sockaddr* addr, IPV ipv = Ipv4)
```
Constructor.
* const sockaddr* addr : sockaddr.
* IPV ipv : ip version,ipv4、ipv6.
<br></br>
```C++
const sockaddr* Addr()
```
get ip&&port sockaddr information.
* return: sockaddr.
<br></br>
```C++
void toStr(std::string& str)
```
IP&&port to string,format"xxx.xxx.xxx.xxx:port".
* std::string& str : return IP&&port string.
<br></br>
```C++
std::string toStr()
```
IP&&port to string,format"xxx.xxx.xxx.xxx:port".
* return : IP&&port string.
<br></br>
```C++
IPV Ipv()
```
get IP version.
* return : ipv4、ipv6。
<br></br>
```C++
static  void AddrToStr(uv_tcp_t* client, std::string& addrStr, IPV ipv = Ipv4)
```
Get ip&&port string from uv_tcp.
* uv_tcp_t* client : client's handle.
* std::string& addrStr : Return ip&&port string.
* IPV ipv : IP version,ipv4、ipv6.
<br></br>
```C++
static  uint16_t  GetIpAndPort(const sockaddr_storage* addr, std::string& out, IPV ipv = Ipv4)
```
获取ip和端口。
* const sockaddr_storage*  : socket handle.
* std::string& out : Get ip address string.
* IPV ipv : ip version,ipv4、ipv6.
* return : port num.