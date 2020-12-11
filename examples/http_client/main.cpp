#include <iostream>
#include <fstream>
#include <uv/include/uv11.hpp>

void onHttpResp(uv::http::HttpClient* client,int error, uv::http::Response* resp)
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
    //close connection.
    delete client;
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
    client->setOnResp(std::bind(&onHttpResp, client,
        std::placeholders::_1,std::placeholders::_2));

    uv::http::Request req;
    req.setPath("/search");
    //url参数
    req.appendUrlParam("q", "uv-cpp");
    //消息头列表
    req.appendHead("Host", "cn.bing.com");
    req.appendHead("Connection", "keep - alive");
    req.appendHead("Accept-Language", "en");
  

    //请求http服务
    client->Req(addr,req);
}

int main(int argc, char** args)
{
    uv::EventLoop loop;
  
    //查询DNS。
    uv::DNSGet dnsGet(&loop);
    dnsGet.setOnDNSCallback(std::bind(&onGetIp, &loop, std::placeholders::_1, std::placeholders::_2));

    int rst = dnsGet.GetIP("cn.bing.com","80");

    if (rst != 0)
    {
        uv::LogWriter::Instance()->error(uv::EventLoop::GetErrorMessage(rst));
    }

    loop.run();
}
