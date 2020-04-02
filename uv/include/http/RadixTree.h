/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-2

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "RadixTreeNode.h"

namespace uv
{
namespace http
{
template<typename Type>
class RadixTree
{
public:
    RadixTree();
    virtual ~RadixTree();
    void setNode(std::string& key, Type value);
    void setNode(std::string&& key, Type value);

    //Type getNode(std::string& key);
private:
    std::shared_ptr<RadixTreeNode<Type>> root_;
};

template<typename Type>
inline RadixTree<Type>::RadixTree()
    :root_(nullptr)
{
}

template<typename Type>
inline RadixTree<Type>::~RadixTree()
{
}


template<typename Type>
inline void RadixTree<Type>::setNode(std::string& key, Type value)
{
    if (nullptr == root_)
    {
        root_ = make_shared<RadixTreeNode<Type>>(key, value);
    }
    else
    {
        if (!root_->setNode(key, value))
        {
            auto child1 = root_;
            root_ = make_shared<RadixTreeNode<Type>>();
            root_->appendChild(child1);
            auto child2 = make_shared<RadixTreeNode<Type>>(key, value);
            root->appendChild(child2);
        }
    }
}

template<typename Type>
inline void RadixTree<Type>::setNode(std::string&& key, Type value)
{
    setNode(key, value);
}

}
}