#include <iostream>
#include <uv/include/uv11.hpp>


void onGetIp(int status, std::string& ip)
{
    if (status < 0)
    {
        uv::LogWriter::Instance()->error(uv::EventLoop::GetErrorMessage(status));
        return;
    }
    std::cout << ip << std::endl;
}

int main(int argc, char** args)
{
    uv::EventLoop* loop = new uv::EventLoop();
    
    uv::DNSGet dnsGet(loop);

    dnsGet.setOnDNSCallback(std::bind(&onGetIp, std::placeholders::_1, std::placeholders::_2));

    int rst = dnsGet.GetIP("www.github.com");

    if (rst != 0) 
    {
        uv::LogWriter::Instance()->error(uv::EventLoop::GetErrorMessage(rst));
    }
    loop->run();
    delete loop;
}
