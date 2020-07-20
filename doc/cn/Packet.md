# Packet
<br> 数据包格式: </br>
包头 | 数据长度|数据段|包尾|
:---------:|:--------:|:--------:|:--------:|
1字节 | 2字节|N字节|1字节|
```C++
Packet()
```
构造函数。
<br></br>
```C++
~Packet()
```
析构函数。
<br></br>
```C++
void pack(const char* data, uint16_t size)
```
数据写入packet类。
* const char* data : 写入数据地址。
* uint16_t size : 写入数据长度。
<br></br>
```C++
const char* getData()
```
读取数据缓存指针。
* 返回值 : 数据缓存地址。
<br></br>
```C++
const uint16_t DataSize()
```
读取数据缓存长度。
* 返回值 : 数据缓存长度。
<br></br>
```C++
const std::string& Buffer()
```
读取包缓存。
* 返回值 : 数据包缓存。
<br></br>
```C++
const uint32_t PacketSize()
```
读取包缓存长度。
* 返回值 : 数据包缓存长度。
<br></br>
```C++
void swap(std::string& str)
```
交换缓存。
* std::string& str : 交换缓存string。
<br></br>
```C++
static int readFromBuffer(PacketBuffer*, Packet&)
```
从PacketBuffer接口中读取包数据。
* PacketBuffer* : PacketBuffer接口。
* Packet& ：读取的Packet对象。
<br></br>
```C++
template<typename NumType>
static void UnpackNum(const uint8_t* data, NumType& num)
```
从字节流中解析数字。
* const uint8_t* data : 字节流。
* NumType& num ：解析出的数字。
<br></br>
```C++
template<typename NumType>
static void PackNum(char* data, NumType num)
```
把数字打包刀字节流。
* char* data : 字节流。
* NumType num ：被打包的数字。
<br></br>
```C++
static uint32_t PacketMinSize()
```
数据包最小长度(包头+数据长度字段+包尾)
* 返回值 : 数据包最小长度。
<br></br>
