#include <iostream>
#include <uv/include/uv11.hpp>

void func(uv::EventLoop* loop)
{
    std::cout << "in func thread id:" << std::this_thread::get_id() << std::endl;
    loop->runInThisLoop([loop]() 
    {
        std::cout << "stop in loop thread id:" << std::this_thread::get_id() << std::endl;
        loop->stop();
    });
}

void loop_exit()
{
    uv::EventLoop* loop = new uv::EventLoop();
    std::thread t1(std::bind(&func, loop));
    loop->run();
    loop->runInThisLoop([]() 
    {
        std::cout << "loop is stop" << std::endl;
    });
    delete loop;
    t1.join();
    std::cout << "delete loop" << loop << std::endl << std::endl;;
}
int main(int argc, char** args)
{
    while (true)
    {
        std::thread t1(std::bind(&loop_exit));
        t1.join();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
