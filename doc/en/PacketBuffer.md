# PacketBuffer
Packet buffer interface.
```C++
PacketBuffer()
```
Constructor.
<br></br>
```C++
virtual ~PacketBuffer()
```
Destructor.
<br></br>
```C++
virtual int append(const char* data, uint64_t size) = 0
```
Write data to buffer.
* const char* data : Write data address.
* uint16_t size : Write data size.
* return : 0 success, -1 fail.
<br></br>
```C++
virtual int readBufferN(std::string& data, uint64_t N) = 0
```
Read data from buffer,but not clear data.
* std::string& data : Read data.
*  uint64_t N : Read data size.
*  return : 0 success，-1 fail.
<br></br>
```C++
virtual int clearBufferN(uint64_t N) = 0
```
Delete N bytes data from buffer.
*  uint64_t N : Delete data size.
* return : 0 success，-1 fail.
<br></br>
```C++
virtual int clear() = 0
```
Delete all data from buffer.
* return : 0 success，-1 fail.
<br></br>
```C++
irtual uint64_t readSize() = 0
```
Get current data size in buffer.
* return : Readable data length.
<br></br>
```C++
int readString(std::string& out)
```
Read a string data packet from buffer.
* std::string& out : String data packet.
<br></br>
```C++
int readPacket(Packet& out)
```
Read a data packet from buffer.
* Packet& out : Packet obj.
<br></br>
```C++
int readGeneric(void* out)
```
Read a customized data packet from buffer.
* void* out : Customized data packet pointer.
<br></br>