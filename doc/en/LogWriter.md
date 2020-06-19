# LogWriter
日志输出接口。
<br></br>
```C++
static LogWriter* Instance();
```
获取单例日志对象。
<br></br>
```C++
static void ToHex(std::string& message, const char* data, unsigned int size);
```
字节流转hex文本。
* std::string& message : output hex message.
* const char* data : intput char ptr data.
* unsigned int size : intput data's size.
<br></br>
```C++
static void ToHex(std::string& message, std::string& data);
```
获取单例日志对象。
<br></br>