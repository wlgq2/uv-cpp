/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-31

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/HttpCommon.h"

using namespace uv;
using namespace uv::http;

std::string uv::http::HttpVersionToStr(HttpVersion version)
{
    switch (version)
    {
    case uv::http::Http1_0:
        return "HTTP/1.0";
    case uv::http::Http1_1:
        return "HTTP/1.1";
    default:
        return "";
    }
}
