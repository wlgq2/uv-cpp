# uv-cpp
<a href="https://github.com/wlgq2/libuv_cpp11/releases"><img src="https://img.shields.io/github/release/wlgq2/libuv_cpp11.svg" alt="Github release"></a>
[![Platform](https://img.shields.io/badge/platform-%20%20%20%20Linux,%20Windows-green.svg?style=flat)](https://github.com/wlgq2/libuv_cpp11)
[![License](https://img.shields.io/badge/license-%20%20MIT-yellow.svg?style=flat)](LICENSE)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active)

<br>Language Translations:</br>
* [Englishi](README.md)
* [简体中文](README_zh_cn.md)
** **
## Features
* C++11 style callbacks instead of C： You can use class member functions or lambda as callbacks.
* TCP and UDP wrapper.
* `Timer`and`TimerWheel`：Heartbeat timeout judgment mechanism with time complexity of O(1).
* `Async`：Optimized the problem of calling multiple times, perhaps only once, compared to the libuv's async. 
* `Packet`and`PacketBuffer`：Send and receive packet data, used to resolve TCP stubs/stickers.
* Log interface.
** **
## Simple test
one thread 1k bytes ping-pong。
<br>environment：Intel Core i5 6402 + ubuntu14.04.5 + gcc5.5.0 + libuv1.22.0 + O2优化</br>

   libuv_cpp | no use PacketBuffer|CycleBuffer|ListBuffer|
:---------:|:--------:|:--------:|:--------:|
Times/Sec | 192857 |141487|12594|


## Quick start
```C++
#include <iostream>
#include <uv/uv11.h>


int main(int argc, char** args)
{
    //event's loop
    uv::EventLoop* loop = uv::EventLoop::DefalutLoop();

    //Tcp Server
    uv::SocketAddr serverAddr("0.0.0.0", 10002, uv::SocketAddr::Ipv4);
    uv::TcpServer server(loop, serverAddr);
    server.setMessageCallback(
        [](std::shared_ptr<uv::TcpConnection> conn, const char* data , ssize_t size)
    {
        std::cout << std::string(data, size) << std::endl;
        conn->write(data, size,nullptr);
    });
    server.start();

    //Tcp Client
    uv::TcpClient client(loop);
    client.setConnectCallback(
        [&client](bool isSuccess)
    {
        if (isSuccess)
        {
            char data[] = "hello world!";
            client.write(data, sizeof(data));
        }
    });
    client.connect(serverAddr);
       
    loop->run();
}

```

