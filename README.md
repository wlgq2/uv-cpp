# cpp_hodgepodge
这是一个C++11环境下的测试代码杂项。 
** **  

 **`libuv C++11`**

libuv C++11风格封装，基本操作及内存管理。

* TCP相关类封装：`TcpServer`、`TcpClient`、`TcpConnection`、`TcpAccept`。及把C风格回调改为C++11风格的回调（支持lambda及非静态类成员函数）。
* Timer及TimerWheel：定时器及时间复杂度为O(1)的心跳超时提出机制。
* Async：异步机制封装，由于libuv的所有api非线程安全，建议使用writeInLoop接口代替直接write（writeInLoop会检查当前调用的线程，如果在loop线程中调用则直接write，否则把write加到loop线程中执行）。
* libuv信号封装。   
** **

**`lua C++对象绑定`** 

C++对象绑定到lua测试。
** **

**`C++11 多线程n皇后`**

一段利用C++11 多线程并行计算n皇后程序。
