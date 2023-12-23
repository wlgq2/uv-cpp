# GlobalConfig
全局变量及配置。
```C++
static BufferMode BufferModeStatus
```
使用数据缓存模式，NoBuffer、CycleBuffer、ListBuffer。默认为NoBuffer。
<br></br>
```C++
static uint64_t   CycleBufferSize
```
循环缓存数据大小，默认32KB。
<br></br>
```C++
static ReadBufferPacketFunc ReadBufferPacket
```
Packet数据包解析读取函数，默认为Packet::readFromBuffer。
<br></br>
```C++
static ReadBufferStringFunc ReadBufferString
```
String数据包解析读取函数，默认为空。
<br></br>
```C++
static ReadBufferVoidFunc ReadBufferVoid
```
自定义数据包解析读取函数，默认为空。
<br></br>