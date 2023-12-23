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
* HttpVersion version : Http协议版本。 Unknown、Http1_0、Http1_1。
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
<br></br>
```C++
void swapContent(std::string& str)
```
将字符串变量与http请求内容交换。
* std::string& str : 交换内容字符串变量。
<br></br>
```C++
void swapContent(std::string&& str)
```
将字符串变量与http请求内容交换。
* std::string&& str : 交换内容字符串右值变量。
<br></br>
```C++
const std::string& getContent()
```
获取请求内容。
* 返回值: 请求内容。
<br></br>
```C++
void appendHead(std::string& key, std::string& value)
```
添加请求头部字段。
* std::string& key : 头部字段key值。
* std::string& value : 头部字段值。
<br></br>
```C++
void appendHead(std::string&& key, std::string&& value)
```
添加请求头部字段。
* std::string&& key : 头部字段key值。
* std::string&& value : 头部字段值。
<br></br>
```C++
std::string getHead(std::string& key)
```
获取请求头部字段值。
* std::string& key : 头部字段key值。
* 返回值 : 头部字段值。
<br></br>
```C++
std::string getHead(std::string&& key)
```
获取请求头部字段。
* std::string&& key : 头部字段key值。
* 返回值 : 头部字段值。
<br></br>
```C++
void appendUrlParam(std::string& key, std::string& value)
```
添加Url参数，例"?param1=100"。
* std::string& key : url参数。
* std::string& value : url参数值。
<br></br>
```C++
void appendUrlParam(std::string&& key, std::string&& value)
```
添加Url参数，例"?param1=100"。
* std::string&& key : url参数。
* std::string&& value : url参数值。
<br></br>
```C++
std::string getUrlParam(std::string& key)
```
获取url参数。
* std::string&& key : url参数。
* 返回值 : url参数值。
<br></br>
```C++
std::string getUrlParam(std::string&& key)
```
获取url参数。
* std::string&& key : url参数。
* 返回值 : url参数值。
<br></br>
```C++
void setPath(std::string&& path)
```
设置路径，例如"/test"。
* std::string&& path : 路径。
<br></br>
```C++
const std::string& getPath()
```
获取路径。
* 返回值 : 路径。
<br></br>
```C++
const std::string& getValue()
```
获取解析后的值,例"/value:1234"
* 返回值 : 获取值。
<br></br>
```C++
int pack(std::string& data)
```
请求打包成数据流。
* std::string& data : 打包输出字符串。
* 返回值 ： 0为成功。
<br></br>
```C++
ParseResult unpack(std::string& data)
```
从数据流中解析请求包。
* std::string& data : 数据包字节流。
* 返回值 : 解析结果，失败、成功、出错。
<br></br>
```C++
ParseResult unpackAndCompleted(std::string& data)
```
从数据流中解析请求包，并判定包是否发完。
* std::string& data : 数据包字节流。
* 返回值 : 解析结果，失败、成功、出错。
<br></br>
```C++
static std::string MethonToStr(Methon methon)
```
请求方法转换成字符串。
* Methon methon : 请求方法，Get、Post等。
* 返回值 : 请求方法字符串。
<br></br>
```C++
static Methon StrToMethon(std::string& str)
```
字符串转换成请求方法。
* Methon methon : 请求方法字符串。
* 返回值 : 请求方法。
<br></br>