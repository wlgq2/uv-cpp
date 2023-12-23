# PacketBuffer
包缓存接口。
```C++
PacketBuffer()
```
构造函数。
<br></br>
```C++
virtual ~PacketBuffer()
```
析构函数。
<br></br>
```C++
virtual int append(const char* data, uint64_t size) = 0
```
向缓存写入数据接口。
* const char* data : 写入数据地址。
* uint16_t size : 写入数据长度。
* 返回值 : 0 成功，-1失败（缓存不够）。
<br></br>
```C++
virtual int readBufferN(std::string& data, uint64_t N) = 0
```
从缓存读出N字节数据,读过程不清除数据(性能考虑)。
* std::string& data : 读数据接口。
*  uint64_t N : 读数据长度。
* 返回值 : 0 成功，-1失败。
<br></br>
```C++
virtual int clearBufferN(uint64_t N) = 0
```
删除N字节数据。
*  uint64_t N : 删除数据长度。
* 返回值 : 0 成功，-1失败。
<br></br>
```C++
virtual int clear() = 0
```
删除所有数据。
* 返回值 : 0 成功，-1失败。
<br></br>
```C++
irtual uint64_t readSize() = 0
```
当前可读数据字节长度。
* 返回值 : 可读字节长度。
<br></br>
```C++
int readString(std::string& out)
```
从缓存中读取一个字符串数据包。
* std::string& out : 字符串数据包。
<br></br>
```C++
int readPacket(Packet& out)
```
从缓存中读取一个Packet对象数据包。
* Packet& out : Packet对象数据包。
<br></br>
```C++
int readGeneric(void* out)
```
从缓存中读取一个自定义对象数据包。
* void* out : 自定义数据对象指针。
<br></br>