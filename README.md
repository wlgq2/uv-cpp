# libuv_cpp11
Language Translations:
* [Englishi](README.md)
* [繁體中文](README_zh_tw.md)
* [简体中文](README_zh_cn.md)
** **
## Features
* C++11 style callbacks instead of C： You can use class member functions or lambda as callbacks.
* `Timer`and`TimerWheel`：Heartbeat timeout judgment mechanism with time complexity of O(1).
* `Async`：Optimized the problem of calling multiple times, perhaps only once, compared to the libuv's async. 
* `Packet`and`PacketBuffer`：Send and receive packet data, used to resolve TCP stubs/stickers.
* Log interface.
** **
Simple test：one thread 1k bytes ping-pong。
<br>environment：Intel Core i5 6402 + ubuntu14.04.5 + gcc5.5.0 + libuv1.22.0 + O2优化</br>

   libuv_cpp | no use PacketBuffer|CycleBuffer|ListBuffer|
:---------:|:--------:|:--------:|:--------:|
Times/Sec | 192857 |141487|12594|

