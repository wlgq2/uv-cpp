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
* std::string& message : 输出hex文本。
* const char* data : 输入字符数据。
* unsigned int size : 输入字符数据长度。
<br></br>
```C++
static void ToHex(std::string& message, std::string& data);
```
字节流转hex文本。
* std::string& message : 输出hex文本。
* std::string& data : 输入字符串数据。
<br></br>

```C++
void registerInterface(WriteLogCallback callback);
```
注册日志输出函数。
* WriteLogCallback callback ：日志输出函数，未设置则默认使用std::cout。
* WriteLogCallback : void(int level,const std::string& log)
<br></br>

```C++
void setLevel(int level);
```
设置日志输出等级阈值。
* int level : 日志等级阈值。
<br></br>

```C++
int getLevel();
```
获取日志输出等级阈值。
* 返回值 ：当前日志输出等级阈值。
<br></br>

```C++
const std::string& getLevelName(int level);
```
获取日志等级对应字符串。
* int level : 日志等级。
* 返回值 : 日志等级字符串,"Debug","Info","Warn","Error","Fatal"。
<br></br>

```C++
void write(Level level, const std::string& data);
```
写日志。
* Level level : 日志等级。
* const std::string& data : 日志内容。
<br></br>

```C++
void fatal(const std::string& data);
```
写fatal等级日志
* const std::string& data : 日志内容
<br></br>

```C++
void warn(const std::string& data);
```
写warn等级日志
* const std::string& data : 日志内容
<br></br>

```C++
void error(const std::string& data);
```
写error等级日志
* const std::string& data : 日志内容
<br></br>


```C++
void info(const std::string& data);
```
写info等级日志
* const std::string& data : 日志内容
<br></br>

```C++
void debug(const std::string& data);
```
写debug等级日志
* const std::string& data : 日志内容
<br></br>
