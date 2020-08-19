# Request
Http's request.
<br></br>
```C++
Request()
```
Constructor.
<br></br>
```C++
Request(HttpVersion version, Methon methon)
```
Constructor.
* HttpVersion version : Http protocol version.
* Methon methon : Http request method.
<br></br>
```C++
void setVersion(HttpVersion version)
```
Set http protocol version.
* HttpVersion version : Http version. Unknown,Http1_0,Http1_1.
<br></br>
```C++
void setMethon(Methon methon)
```
Set http request method.
* Methon methon : Http request method.
<br></br>
```C++
HttpVersion getVersion()
```
Get http version.
* return : Http protocol version.
<br></br>
```C++
Methon getMethon()
```
Get http methon.
* return : Http request method.
<br></br>
```C++
void swapContent(std::string& str)
```
Swap http request's content.
* std::string& str : Swap string.
<br></br>
```C++
void swapContent(std::string&& str)
```
Swap http request's content.
* std::string&& str : Swap string with right value.
<br></br>
```C++
const std::string& getContent()
```
Get http request's content.
* return: http request's content.
<br></br>
```C++
void appendHead(std::string& key, std::string& value)
```
Append http's head field.
* std::string& key : Head field key.
* std::string& value : Head field value.
<br></br>
```C++
void appendHead(std::string&& key, std::string&& value)
```
Append http's head field with right value.
* std::string&& key : Head field key.
* std::string&& value : Head field key.
<br></br>
```C++
std::string getHead(std::string& key)
```
Get http request head value.
* std::string& key : Head field key.
* return  : Head field value.
<br></br>
```C++
std::string getHead(std::string&& key)
```
Get http request head value.
* std::string& key : Head field key.
* return  : Head field value.
<br></br>
```C++
void appendUrlParam(std::string& key, std::string& value)
```
Append URL parameter，such as "?param1=100.
* std::string& key : Url parameter.
* std::string& value : url value.
<br></br>
```C++
void appendUrlParam(std::string&& key, std::string&& value)
```
Append URL parameter，such as "?param1=100.
* std::string& key : Url parameter.
* std::string& value : url value.
<br></br>
```C++
std::string getUrlParam(std::string& key)
```
Get URL parameter.
* std::string&& key : Url parameter.
* return : url value.
<br></br>
```C++
std::string getUrlParam(std::string&& key)
```
Get URL parameter.
* std::string&& key : Url parameter.
* return : url value.
<br></br>
```C++
void setPath(std::string&& path)
```
Set http  path, such as "/test".
* std::string&& path : Http's path.
<br></br>
```C++
const std::string& getPath()
```
Get http path.
* return : Http's path.
<br></br>
```C++
const std::string& getValue()
```
Get value, such as "/value:1234".
* return : value.
<br></br>
```C++
int pack(std::string& data)
```
Packaged data from this request.
* std::string& data : Output string.
* return ： Successed if 0.
<br></br>
```C++
ParseResult unpack(std::string& data)
```
Unpack data to this request.
* std::string& data : Data string.
* return : Rusult. Fail,Successe and Error.
<br></br>
```C++
ParseResult unpackAndCompleted(std::string& data)
```
Unpack data to this request and confirm whether package is completed.
* std::string& data : Data string.
* return : Rusult. Fail,Successe and Error.
<br></br>
```C++
static std::string MethonToStr(Methon methon)
```
Methon to string.
* Methon methon : Request Methon, such as Get,Post,Head,Put,Delete,Connect,Options,Trace,Patch,Invalid.
* return : Request methon's string.
<br></br>
```C++
static Methon StrToMethon(std::string& str)
```
String to methon.
* Methon methon : Request methon's string.
* return : Request methon.
<br></br>