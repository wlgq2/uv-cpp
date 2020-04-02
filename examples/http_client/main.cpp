#include <iostream>
#include <fstream>
#include <uv/include/uv11.h>

void onHttpResp(int error, uv::http::Response* resp)
{
    if (error == uv::http::HttpClient::ConnectFail)
    {
        //连接服务失败
        uv::LogWriter::Instance()->error("connect server fail.");
        return;
    }
    if (error == uv::http::HttpClient::ParseFail)
    {
        //解析response出错
        uv::LogWriter::Instance()->error("parse http response fail.");
        return;
    }
    std::ofstream outfile;
    outfile.open("test.html", std::ios_base::out);
    outfile << resp->getContent();
    outfile.close();
    std::cout << "write test.htmt success" << std::endl;
}


void onGetIp(uv::EventLoop* loop ,int status, std::string& ip)
{
    if (status < 0)
    {
        uv::LogWriter::Instance()->error(uv::EventLoop::GetErrorMessage(status));
        return;
    }
    uv::LogWriter::Instance()->debug(std::string("get ip:")+ ip);
    //服务器ip地址
    uv::SocketAddr addr(ip, 80);
    uv::http::HttpClient* client = new uv::http::HttpClient(loop);
    client->setOnResp(std::bind(&onHttpResp, std::placeholders::_1,std::placeholders::_2));

    uv::http::Request req;
    req.setPath("/s");
    //url参数
    req.appendUrlParam("ie", "utf-8");
    req.appendUrlParam("wd", "uv-cpp");
    //消息头列表
    req.appendHead("Host", "www.baidu.com");
    req.appendHead("Accept - Language", "en");
    req.appendHead("User - Agent", "Mozilla / 5.0 (Windows NT 10.0; Win64; x64; rv:73.0) Gecko / 20100101 Firefox / 73.0");

    //请求http服务
    client->Req(addr,req);
}

int main(int argc, char** args)
{
    uv::EventLoop loop;
  
    //查询DNS。
    uv::DNSGet dnsGet(&loop);
    dnsGet.setOnDNSCallback(std::bind(&onGetIp, &loop, std::placeholders::_1, std::placeholders::_2));

    int rst = dnsGet.GetIP("www.baidu.com","80");

    if (rst != 0)
    {
        uv::LogWriter::Instance()->error(uv::EventLoop::GetErrorMessage(rst));
    }

    loop.run();
}
