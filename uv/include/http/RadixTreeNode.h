/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-2

   Description: https://github.com/wlgq2/uv-cpp
*/
#include <string>
#include <List>
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