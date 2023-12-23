# GlobalConfig
Global variable and setting.
```C++
static BufferMode BufferModeStatus
```
Data cache mode used,NoBuffer、CycleBuffer、ListBuffer.The default is NoBuffer.
<br></br>
```C++
static uint64_t   CycleBufferSize
```
Cycle buffer size,The default is 32KB.
<br></br>
```C++
static ReadBufferPacketFunc ReadBufferPacket
```
Packet data parsing and reading function,The default is Packet::readFromBuffer.
<br></br>
```C++
static ReadBufferStringFunc ReadBufferString
```
String data packet parsing and reading function,The default is Null.
<br></br>
```C++
static ReadBufferVoidFunc ReadBufferVoid
```
Customized data packet parsing and reading function,The default is Null.
<br></br>