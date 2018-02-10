# libuv_cpp11
<br>对libuv的C++风格封装,用于上线项目，做过压测。</br>


* TCP相关类封装：`TcpServer`、`TcpClient`、`TcpConnection`、`TcpAccept`。及把C风格回调改为C++11风格的回调（支持非静态类成员函数及lambda）。
* `Timer`及`TimerWheel`：定时器及时间复杂度为O(1)的心跳超时踢出机制。
* Async：异步机制封装，由于libuv的所有api非线程安全，建议使用writeInLoop接口代替直接write（writeInLoop会检查当前调用的线程，如果在loop线程中调用则直接write，否则把write加到loop线程中执行）。
* libuv信号封装。   
* Log日志输出接口，可绑定至自定义Log库。
** **
**！对于诸如`uv::Timer`,`uv::TcpClient`等对象的释放需要调用close接口并在回调函数中释放对象,否则可能会出错。**
<br>一点微小的工作。</br>
