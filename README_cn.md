# uv-cpp
<a href="https://github.com/wlgq2/uv-cpp/releases"><img src="https://img.shields.io/github/release/wlgq2/uv-cpp.svg" alt="Github release"></a>
[![Platform](https://img.shields.io/badge/platform-%20%20%20%20Linux,%20Windows-green.svg?style=flat)](https://github.com/wlgq2/uv-cpp)
[![License](https://img.shields.io/badge/license-%20%20MIT-yellow.svg?style=flat)](LICENSE)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active)


<br>基于libuv实现的C++11风格网络库。接口简洁，性能优越，做过业务压测，稳定线上运行。正确使用接口情况下，未发现core dump或内存泄漏。</br>
## 依赖项
 * [libuv][1]
## 特性
** **
* C++11风格回调函数：非C语言函数回调，支持非静态类成员函数及lambda。
* TCP及UDP相关类封装：`TcpServer`、`TcpClient`、`TcpConnection`、`TcpAccept`、`Udp`。
* `DNS`和`Http`：DNS查询及HTTP协议支持，基于Radix Tree支持通配符等HTTP SEVER路由机制。
* `Timer`及`TimerWheel`：定时器及时间复杂度为O(1)的心跳超时踢出机制。
* `Async`：异步机制封装。相对于原生libuv async接口，优化了调用多次可能只运行一次的[问题(特性)][2]。由于libuv几乎所有api都非线程安全，建议使用writeInLoop接口代替直接write（writeInLoop会检查当前调用的线程，如果在loop线程中调用则直接write，否则把write加到loop线程中执行）。
* libuv信号封装。   
* `Packet`与`PacketBuffer`：包与缓存，发送/接受包，用于从TCP字节流解析协议包。由ListBuffer和CycleBuffer两种实现(前者空间友好，后者时间友好)。提供默认Packet消息协议，也可实现自定义任意消息协议(参考[uvnsq][3]实现NSQ消息协议)。
* Log日志输出接口，可绑定至自定义Log库。
** **
## 编译
* VS2017 (windows)
* Codeblocks (linux)
* CMake (linux)
** **
## 基准测试
### ping-pong VS boost.asio 1.67
<br>环境：Intel Core i5 8265U + debian8 + gcc8.3.0 + libuv1.30.0 + '-O2'优化</br>

包大小| 1K bytes|2K bytes|4K bytes|8K bytes|
:---------:|:--------:|:--------:|:--------:|:--------:|
uv-cpp | 16138 kbyte|32071 kbyte|59264 kbyte|123813 kbyte|
boost.asio | 16119 kbyte|31566 kbyte|58322 kbyte|126210 kbyte|

![asio1](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_asio/one_no_data.png)

<br>环境：i5-8265U + 4G内存 + 4k字节ping-pong</br>
并发数| 10|100|1000|5000|
:---------:|:--------:|:--------:|:--------:|:--------:|
uv-cpp | 654282 kbyte|591869 kbyte|401500 kbyte|412855 kbyte|
boost.asio | 633818 kbyte|585716 kbyte|371386 kbyte|382402 kbyte|

![asio2](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_asio/concurrency_no_data.png)

### Apache bench VS nginx 1.14.2
<br>环境：Intel Core i5 8265U + debian8 + gcc8.3.0 + libuv1.30.0 + '-O2'</br>
<br>1000 并发 && 100000 次请求和nginx对比。</br>
![uv_http](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_nginx/uv_http_1000.png)
![nginx_http](https://github.com/wlgq2/uv_cpp_res/blob/master/vs_nginx/nginx_http_1000.png)

## 例程
十行代码实现简单echo服务
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
简单的http服务器，基于Radix Tree实现的路由机制，支持通配符、设置参数。
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
更多的例程 [here][4].
<br>API手册[here][5].</br>
** **
<br>**！对于诸如`uv::Timer`,`uv::TcpClient`等对象的释放需要调用close接口并在回调函数中释放对象,否则可能会出错。**</br>
<br>**！切勿在Loop线程外创建注册该Loop下的事件相关对象（`uv::TcpClient`，`uv::TcpServer`，`uv::Timer`……），建议每个Loop都绑定独立线程运行。**</br>
<br>一点微小的工作。</br>

[1]: https://github.com/libuv/libuv
[2]: http://docs.libuv.org/en/v1.x/async.html
[3]: https://github.com/wlgq2/uvnsq
[4]: https://github.com/wlgq2/uv-cpp/tree/master/examples
[5]: https://github.com/wlgq2/uv-cpp/tree/master/doc
