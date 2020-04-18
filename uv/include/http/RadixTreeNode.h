/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-2

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_RADIX_TREE_NODE
#define UV_HTTP_RADIX_TREE_NODE

#include <string>
#include <memory>

namespace uv
{
namespace http
{
template<typename Type>
struct RadixTreeNode
{
    bool isEmpty;
    std::string key;
    std::shared_ptr <RadixTreeNode<Type>> child;
    std::shared_ptr <RadixTreeNode<Type>> next;
    Type value;
};
template<typename Type>
using RadixTreeNodePtr = std::shared_ptr<RadixTreeNode<Type>>;

}
}

#endif
