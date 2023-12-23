# Request
Http's response.
<br></br>
```C++
enum StatusCode
```
Http statue code.
*  OK =200 
*  BadRequest = 400 
*  Unauthorized  = 401 
*  Forbidden = 403  
*  NotFound = 404 
*  InternalServerError = 500  
*  ServerUnavailable = 503 

<br></br>
```C++
Response()
```
Constructor.
<br></br>
```C++
Response(HttpVersion version, StatusCode code)
```
Constructor.
* HttpVersion version : Http version. Unknown,Http1_0,Http1_1.
* StatusCode code : Http status code.
<br></br>
```C++
void setVersion(HttpVersion version)
```
Set http protocol version.
* HttpVersion version : Http version. Unknown,Http1_0,Http1_1.
<br></br>
```C++
void setStatus(StatusCode code,std::string info)
```
Set http status code and info, suck as 200,"OK".
* StatusCode code : Status code.
* std::string info : Status info.
<br></br>
```C++
HttpVersion getVersion()
```
Get http version.
* return : Http protocol version.
<br></br>
```C++
StatusCode getStatusCode()
```
Get http status code.
* return : Http status code.
<br></br>
```C++
const std::string& getStatusInfo()
```
Get http status info.
* return : Http status info.
<br></br>
```C++
void appendHead(std::string& key, std::string& value)
```
Append http's head.
* std::string& key : head's key.
* std::string& value : head's value.
<br></br>
```C++
void appendHead(std::string&& key, std::string&& value)
```
Append http's head with right value.
* std::string&& key : head's key.
* std::string&& value : head's value.
<br></br>
```C++
std::string getHead(std::string& key)
```
Get http head value.
* std::string&& key : head's key.
* return : head's value.
<br></br>
```C++
void swapContent(std::string& body)
```
Swap http request's content.
* std::string& body  : Swap string.
<br></br>
```C++
void swapContent(std::string&& body)
```
Swap http request's content.
* std::string& body  : Swap string with right value.
<br></br>
```C++
const std::string& getContent()
```
Get http request's content.
* return : http's content.
<br></br>
```C++
int pack(std::string& data)
```
Packaged data from this response.
* std::string& data :  Output string.
* return ： Successed if 0.
<br></br>
```C++
ParseResult unpack(std::string& data)
```
Unpack data to this response.
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
ParseResult isCompletedChunked()
```
Whether it is chunk
* return : Rusult. Fail,Successe and Error.
<br></br>
