# Request
Http 返回数据。
<br></br>
```C++
enum StatusCode
```
Http状态码。
*  OK =200 :客户端请求成功
*  BadRequest = 400 :客户端请求有语法错误，不能被服务器所理解
*  Unauthorized  = 401 : 请求未经授权，这个状态代码必须和WWW-Authenticate报头域一起使用 
*  Forbidden = 403  : 服务器收到请求，但是拒绝提供服务
*  NotFound = 404 : 请求资源不存在，eg：输入了错误的URL
*  InternalServerError = 500  : 服务器发生不可预期的错误
*  ServerUnavailable = 503 : 服务器当前不能处理客户端的请求，一段时间后可能恢复正常

<br></br>
```C++
Response()
```
构造函数
<br></br>
```C++
Response(HttpVersion version, StatusCode code)
```
构造函数
* HttpVersion version : Http协议版本。
* StatusCode code : 状态码。
<br></br>
```C++
void setVersion(HttpVersion version)
```
设置Http协议版本。
* HttpVersion version : Http协议版本。
<br></br>
```C++
void setStatus(StatusCode code,std::string info)
```
设置Http状态行，例 200、"OK"。
* StatusCode code : 状态码。
* std::string info : 状态信息。
<br></br>
```C++
HttpVersion getVersion()
```
获取Http协议版本。
* 返回值 : Http协议版本。
<br></br>
```C++
StatusCode getStatusCode()
```
获取Http状态码。
* 返回值 : Http状态码。
<br></br>
```C++
const std::string& getStatusInfo()
```
获取Http状态信息。
* 返回值 : 状态信息。
<br></br>
```C++
void appendHead(std::string& key, std::string& value)
```
添加消息报头字段。
* std::string& key : 消息报头key值。
* std::string& value : 消息报头value值。
<br></br>
```C++
void appendHead(std::string&& key, std::string&& value)
```
添加消息报头字段。
* std::string&& key : 消息报头key值。
* std::string&& value : 消息报头value值。
<br></br>
```C++
std::string getHead(std::string& key)
```
获取消息报头字段。
* std::string&& key : 消息报头key值。
* 返回值 : 消息报头value值。
<br></br>
```C++
void swapContent(std::string& body)
```
字符串交换Http消息正文内容。
* std::string& body  : 交换Http消息正文内容。
<br></br>
```C++
void swapContent(std::string&& body)
```
字符串交换Http消息正文内容。
* std::string& body  : 交换Http消息正文内容。
<br></br>
```C++
const std::string& getContent()
```
获取Http消息正文内容。
* 返回值 : Http消息正文内容。
<br></br>
```C++
int pack(std::string& data)
```
打包Http response到字节流。
* std::string& data : 打包到字符串中。
* 返回值 : 0为成功。
<br></br>
```C++
ParseResult unpack(std::string& data)
```
从string中解析报数据。
* std::string& data : 字符串数据。
* 返回值 : 解析结果，成功、失败、出错。
<br></br>
```C++
ParseResult unpackAndCompleted(std::string& data)
```
从string中解析报数据并判断是否时间接收完成。
* std::string& data : 字符串数据。
* 返回值 : 解析结果，成功、失败、出错。
<br></br>
```C++
ParseResult isCompletedChunked()
```
判定是否为chunked分段数据。
* 返回值 : 解析结果，成功、失败、出错。
<br></br>
