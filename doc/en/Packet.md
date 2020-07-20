# Packet
<br> Packet format: </br>
header | size|data|end|
:---------:|:--------:|:--------:|:--------:|
1 byte | 2 bytes|N bytes|1 byte|
```C++
Packet()
```
Constructor.
<br></br>
```C++
~Packet()
```
Destructor.
<br></br>
```C++
void pack(const char* data, uint16_t size)
```
Write data to packet.
* const char* data : Data's address.
* uint16_t size : Data's length.
<br></br>
```C++
const char* getData()
```
Get data's address.
* return : Data's address.
<br></br>
```C++
const uint16_t DataSize()
```
Get data's length.
* return : data's length.
<br></br>
```C++
const std::string& Buffer()
```
Get packet buffer address.
* return : packet buffer address.
<br></br>
```C++
const uint32_t PacketSize()
```
Get packet buffer length.
* return : Packet buffer length.
<br></br>
```C++
void swap(std::string& str)
```
Swap packet buffer.
* std::string& str : Buffer string.
<br></br>
```C++
static int readFromBuffer(PacketBuffer*, Packet&)
```
Read packet data from PacketBuffer interface.
* PacketBuffer* : PacketBuffer interface.
* Packet& ：Packet obj.
<br></br>
```C++
template<typename NumType>
static void UnpackNum(const uint8_t* data, NumType& num)
```
Unpack Num from data stream.
* const uint8_t* data : Data stream.
* NumType& num : Num variable.
<br></br>
```C++
template<typename NumType>
static void PackNum(char* data, NumType num)
```
Write a num to data stream.
* char* data : Data stream.
* NumType num : Num variable.
<br></br>
```C++
static uint32_t PacketMinSize()
```
Min Packet size.(header+data size+end)
* return : Min Packet size.
<br></br>
