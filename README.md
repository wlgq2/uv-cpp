# uv-cpp
<a href="https://github.com/wlgq2/libuv_cpp11/releases"><img src="https://img.shields.io/github/release/wlgq2/libuv_cpp11.svg" alt="Github release"></a>
[![Platform](https://img.shields.io/badge/platform-%20%20%20%20Linux,%20Windows-green.svg?style=flat)](https://github.com/wlgq2/libuv_cpp11)
[![License](https://img.shields.io/badge/license-%20%20MIT-yellow.svg?style=flat)](LICENSE)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active)

<br>Language Translations:</br>
* [Englishi](README.md)
* [简体中文](README_cn.md)
** **
## Dependencies
 * [libuv][2]
## Features
* C++11 functional/bind style callback instead of C-style function pointer.
* `TCP` and `UDP` wrapper.
* `Timer`and`TimerWheel`：Heartbeat timeout judgment with time complexity of O(1).
* `Async`：libuv async wrapper，but optimized the [problem][1] of calling multiple times  but callback  will only be called once. 
* `Packet`and`PacketBuffer`：Send and receive packet of Tcp data stream.
* Log interface.
** **
## Build Instructions
* VS2017 (windows)
* Codeblocks (linux)
* CMake (linux)
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
    //uv::EventLoop* loop = new uv::EventLoop();
    //or
    uv::EventLoop* loop = uv::EventLoop::DefalutLoop();
    
    uv::SocketAddr serverAddr("127.0.0.1", 10000, uv::SocketAddr::Ipv4);
    //Tcp Server
    uv::TcpServer server(loop);
    server.setMessageCallback(
        [](uv::TcpConnectionPtr conn, const char* data , ssize_t size)
    {
        std::cout << std::string(data, size) << std::endl;
        std::string str("hex :");
        uv::LogWriter::ToHex(str, data, (unsigned int)size);
        std::cout << str << std::endl;
        conn->write(data, size,nullptr);
    });
    server.bindAndListen(serverAddr);


    //Tcp Client
    uv::TcpClient client(loop);
    client.setConnectStatusCallback(
        [&client](uv::TcpClient::ConnectStatus status)
    {
        if (status == uv::TcpClient::ConnectStatus::OnConnectSuccess)
        {
            char data[] = "hello world!";
            client.write(data, sizeof(data));
        }
        else
        {
            std::cout << "Error : connect to server fail" << std::endl;
        }
    });
    client.connect(serverAddr);

    loop->run();
}



```

[1]: http://docs.libuv.org/en/v1.x/async.html
[2]: https://github.com/libuv/libuv
