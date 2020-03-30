#include <iostream>
#include <uv/include/uv11.h>




int main(int argc, char** args)
{
    uv::http::Request req;
    req.appendParam("Host", "www.example.com");
    req.appendParam("Accept - Language", "en");
    req.getBody() = "hello";

    std::string data;
    req.pack(data);
    std::cout << data << std::endl;
}
