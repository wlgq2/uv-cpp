/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-9-30

   Description:
*/

#include <uv.h>
#include <memory>
#include <functional>

#ifndef ASYNC_H
#define ASYNC_H
namespace uv
{


template<typename ValueType>
class Async  : public std::enable_shared_from_this<Async<ValueType>>
{
public:
    using AsyncCallback = std::function<void(Async<ValueType>*, ValueType*)>;


    Async<ValueType>(uv_loop_t* loop,AsyncCallback callback)
        :handle(new uv_async_t),
        asyncCallback(callback),
        data(nullptr)
    {
        ::uv_async_init(loop, handle, Async<ValueType>::asyncProcess);
        handle->data = static_cast<void*>(this);
    }

    void setData(ValueType* value)
    {
        data = value;
    }

    void runInLoop()
    {
        ::uv_async_send(handle);
    }


    void close()
    {
        ::uv_close((uv_handle_t*)handle, [](uv_handle_t* handle)
        {
            delete (uv_async_t*)handle;
        });
    }
private:
    uv_async_t* handle;
    AsyncCallback asyncCallback;
    ValueType* data;

    static void asyncProcess(uv_async_t* handle)
    {
        auto async = static_cast<Async*>(handle->data);
		if(async->asyncCallback)
			async->asyncCallback(async,async->data);
    }
};


template<typename ValueType>
using AsyncPtr = std::shared_ptr<Async<ValueType>>;
}
#endif
