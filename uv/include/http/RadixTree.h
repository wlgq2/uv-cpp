/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-2

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "RadixTreeNode.h"
#include "HttpCommon.h"

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
    RadixTreeNodePtr<Type> begin();

private:
    RadixTreeNodePtr<Type> root_;

    void setNode(RadixTreeNodePtr<Type>& node, std::string& key, Type& value);
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
        root_ = make_shared<RadixTreeNode<Type>>();
        *root_ = { false,key,nullptr,nullptr,value };
    }
    else
    {
        setNode(root_, key, value);
    }
}

template<typename Type>
inline void RadixTree<Type>::setNode(std::string&& key, Type value)
{
    setNode(key, value);
}

template<typename Type>
inline RadixTreeNodePtr<Type> RadixTree<Type>::begin()
{
    return root_;
}


template<typename Type>
inline void RadixTree<Type>::setNode(RadixTreeNodePtr<Type>& node, std::string& key, Type& value)
{
    auto commonLength = GetCommomStringLength(node->key, key);
    //相同长度为0，遍历next节点。
    if (commonLength == 0)
    {
        //next节点为空，则插入新节点
        if (nullptr == node->next)
        {
            auto newNode = std::make_shared<RadixTreeNode<Type>>();
            *newNode = { false,key,nullptr,nullptr ,value };
            node->next = newNode;
            return;
        }
        //否则遍历next节点
        setNode(node->next, key, value);
    }
    //相同长度小于节点key长度，则拆分节点
    else if (commonLength < node->key.size())
    {
        std::string key1(node->key, 0, commonLength);
        std::string key2(node->key, commonLength,node->key.size()-commonLength);
        auto childNode = std::make_shared<RadixTreeNode<Type>>();
        *childNode = { node->isEmpty,key2,node->child,nullptr,node->value };
        node->isEmpty = true;
        node->key.swap(key1);
        node->child = childNode;
        //如果共同长度等于新增节点则直接赋值
        if (key.size() == commonLength)
        {
            node->isEmpty = false;
            node->value = value;
        }
        else
        {
            auto newNode = std::make_shared<RadixTreeNode<Type>>();
            std::string key3(key, commonLength,key.size()-commonLength);
            *newNode = { false,key3,nullptr,nullptr,value };
            childNode->next = newNode;
        }
    }
    //相同长度等于节点key长度，则遍历child节点
    else
    {
        //key和node->key相等，则直接赋值；
        if (commonLength == key.size())
        {
            node->isEmpty = false;
            node->value = value;
        }
        else //否则，则拆分key，遍历子节点
        {
            std::string key1(key, commonLength, key.size()-commonLength);
            //子节点为空，直接插入
            if (nullptr == node->child)
            {
                auto childNode = std::make_shared<RadixTreeNode<Type>>();
                *childNode = { false,key1,nullptr,nullptr,node->value };
                node->child = childNode;
            }
            else //否则遍历子节点
            {
                setNode(node->child, key1, value);
            }
        }
    }
}   
}
}