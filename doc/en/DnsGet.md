# DnsGet
DNS utility.
<br></br>
```C++
DNSGet(uv::EventLoop* loop)
```
Constructor.
* EventLoop* loop : EventLoop's handle.
<br></br>
```C++
void setOnDNSCallback(OnGetIPAddrCallback callback)
```
<br>Set DNS callback function.</br>
OnGetIPAddrCallback  function format :  void (int statue, std::string& ip)
<br>int status : will 0 while successed.</br>
std::string& ip : hostname's ip address
<br></br>

```C++
int GetIP(std::string& hostname, std::string service = "")
```
Get hostname's ip address.
* std::string& hostname : hostname, like "www.google.com"
* std::string service : service,  like "http"、"ftp"、"80"……
* return  : return 0 while successed.
<br></br>
```C++
int GetIP(std::string&& hostname, std::string service = "");
```
The same.
<br></br>
