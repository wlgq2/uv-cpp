# Request
Http请求数据流。
<br></br>
```C++
Request()
```
构造函数
<br></br>
```C++
Request(HttpVersion version, Methon methon)
```
构造函数
* HttpVersion version : Http协议版本。
* Methon methon : 请求方法。
<br></br>
```C++
void setVersion(HttpVersion version)
```
设置请求HTTP协议版本。
* HttpVersion version : Http协议版本。    Unknown、Http1_0、Http1_1、
<br></br>
```C++
void setMethon(Methon methon)
```
设置请求方法。
* Methon methon : Http请求方法。
<br></br>
```C++
HttpVersion getVersion()
```
返回HTTP协议版本。
* 返回值 : Http协议版本。
<br></br>
```C++
Methon getMethon()
```
返回请求方法
* 返回值 : 请求方法。