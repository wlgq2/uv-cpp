# uv-cpp
<a href="https://github.com/wlgq2/uv-cpp/releases"><img src="https://img.shields.io/github/release/wlgq2/uv-cpp.svg" alt="Github release"></a>
[![Platform](https://img.shields.io/badge/platform-%20%20%20%20Linux,%20Windows-green.svg?style=flat)](https://github.com/wlgq2/uv-cpp)
[![License](https://img.shields.io/badge/license-%20%20MIT-yellow.svg?style=flat)](LICENSE)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active)

<br>Language Translations:</br>
* [English](README.md)
* [简体中文](README_cn.md)
** **
uv-cpp is a simple interface, high-performance network library based on C++11.

## Dependencies
 * [libuv][1]
## Features
* C++11 functional/bind style callback instead of C-style function pointer.
* `TCP` and `UDP` wrapper.
* `DNS`and`Http`：DNS query and http support，Http routing based on radix tree.
* `Timer`and`TimerWheel`：Heartbeat timeout judgment with time complexity of O(1).
* `Async`：libuv async wrapper，but optimized the [problem][2] of calling multiple times  but callback  will only be called once. 
* `Packet`and`PacketBuffer`：Send and receive packet of Tcp data stream. Support custom data packet structure (such as [uvnsq][3])
* Log interface.
** **
## Build Instructions
* VS2017 (windows)
* Codeblocks (linux)
* CMake (linux)
** **
## Benchmark
### ping-pong VS boost.asio-1.67
<br>environment：Intel Core i5 8265U + debian8 + gcc8.3.0 + libuv1.30.0 + '-O2'</br>

 size peer pack | 1K bytes|2K bytes|4K bytes|8K bytes|
:---------:|:--------:|:--------:|:--------:|:--------:|
uv-cpp | 16138 kbyte|32071 kbyte|59264 kbyte|123813 kbyte|
boost.asio | 16119 kbyte|31566 kbyte|58322 kbyte|126210 kbyte|

![asio1](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_asio/one_no_data.png)

<br>environment：i5-8265U + 4G memory + 4k bytes ping-pong</br>
concurrency| 10|100|1000|5000|
:---------:|:--------:|:--------:|:--------:|:--------:|
uv-cpp | 654282 kbyte|591869 kbyte|401500 kbyte|412855 kbyte|
boost.asio | 633818 kbyte|585716 kbyte|371386 kbyte|382402 kbyte|

![asio2](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_asio/concurrency_no_data.png)

### Apache bench VS nginx-1.14.2
<br>environment：Intel Core i5 8265U + debian8 + gcc8.3.0 + libuv1.30.0 + '-O2'</br>
<br>1000 concurrency && 100000 request.</br>
![uv_http](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_nginx/uv_http_1000.png)
![nginx_http](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_nginx/nginx_http_1000.png)

## Quick start
A simple echo server
```C++
#include <iostream>
#include <uv/include/uv11.h>

int main(int argc, char** args)
{
    uv::EventLoop* loop = uv::EventLoop::DefaultLoop();
	
    uv::TcpServer server(loop);
    server.setMessageCallback([](uv::TcpConnectionPtr ptr,const char* data, ssize_t size)
    {
        ptr->write(data, size, nullptr);
    });
    //server.setTimeout(60); //heartbeat timeout.
	
    uv::SocketAddr addr("0.0.0.0", 10005, uv::SocketAddr::Ipv4);
    server.bindAndListen(addr);
    loop->run();
}

```

A simple http service router which based on radix tree.
```C++
int main(int argc, char** args)
{
    uv::EventLoop loop;
    uv::http::HttpServer::SetBufferMode(uv::GlobalConfig::BufferMode::CycleBuffer);

    uv::http::HttpServer server(&loop);
	
    //example:  127.0.0.1:10010/test
    server.Get("/test",std::bind(&func1,std::placeholders::_1,std::placeholders::_2));
    
    //example:  127.0.0.1:10010/some123abc
    server.Get("/some*",std::bind(&func2, std::placeholders::_1, std::placeholders::_2));
    
    //example:  127.0.0.1:10010/value:1234
    server.Get("/value:",std::bind(&func3, std::placeholders::_1, std::placeholders::_2));
    
    //example:  127.0.0.1:10010/sum?param1=100&param2=23
    server.Get("/sum",std::bind(&func4, std::placeholders::_1, std::placeholders::_2));
    
    uv::SocketAddr addr("127.0.0.1", 10010);
    server.bindAndListen(addr);
    loop.run();
}

```
More examples [here][4].
<br>API's document [here][5].  </br>

[1]: https://github.com/libuv/libuv
[2]: http://docs.libuv.org/en/v1.x/async.html
[3]: https://github.com/wlgq2/uvnsq
[4]: https://github.com/wlgq2/uv-cpp/tree/master/examples
[5]: https://github.com/wlgq2/uv-cpp/tree/master/doc
