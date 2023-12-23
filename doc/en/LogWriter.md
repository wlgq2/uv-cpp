# LogWriter
Log output interface.
<br></br>
```C++
static LogWriter* Instance();
```
Get single log object.
<br></br>
```C++
static void ToHex(std::string& message, const char* data, unsigned int size);
```
Byte stream to hex text.
* std::string& message : output hex text.
* const char* data : intput char ptr data.
* unsigned int size : intput data's size.
<br></br>

```C++
static void ToHex(std::string& message, std::string& data);
```
Byte stream to hex text.
* std::string& message : output hex text.
* std::string& data : intput data string.
<br></br>

```C++
void registerInterface(WriteLogCallback callback);
```
Register log's writer function.
* WriteLogCallback callback ：log writer function，Use std::cout by default
* WriteLogCallback : void(int level,const std::string& log)
<br></br>

```C++
void setLevel(int level);
```
Set log's output level.
* int level : log's level.
<br></br>

```C++
int getLevel();
```
Get log's output level.
* return ：log's level.
<br></br>

```C++
const std::string& getLevelName(int level);
```
Get log's level name.
* int level : log's level.
* return : log's level,"Debug","Info","Warn","Error","Fatal"。
<br></br>

```C++
void write(Level level, const std::string& data);
```
Write log.
* Level level : log's level。
* const std::string& data : log's info.。
<br></br>

```C++
void fatal(const std::string& data);
```
write fatal log.
* const std::string& data : log's info.
<br></br>

```C++
void warn(const std::string& data);
```
write warn log.
* const std::string& data : log's info.
<br></br>

```C++
void error(const std::string& data);
```
write error log.
* const std::string& data : log's info.
<br></br>


```C++
void info(const std::string& data);
```
write info log.
* const std::string& data : log's info.
<br></br>

```C++
void debug(const std::string& data);
```
write debug log.
* const std::string& data : log's info.
<br></br>