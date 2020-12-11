/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-2

   Description: https://github.com/wlgq2/uv-cpp
*/
#ifndef UV_HTTP_RADIX_TREE_HPP
#define UV_HTTP_RADIX_TREE_HPP

#include <memory>
#include "HttpCommon.hpp"

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

template<typename Type>
class RadixTree
{
public:
    RadixTree();
    virtual ~RadixTree();
    void set(std::string& key, Type value);
    void set(std::string&& key, Type value);

    RadixTreeNodePtr<Type> Root();
    bool get(const std::string& key, Type& value);
    bool get(const std::string&& key, Type& value);

    static char WildCard;
private:
    RadixTreeNodePtr<Type> root_;

    void setNode(RadixTreeNodePtr<Type>& node, std::string& key, Type& value);
    bool getNode(RadixTreeNodePtr<Type>& node, const std::string& key, Type& value);
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
inline void RadixTree<Type>::set(std::string& key, Type value)
{
    if (nullptr == root_)
    {
        root_ = std::make_shared<RadixTreeNode<Type>>();
        *root_ = { false,key,nullptr,nullptr,value };
    }
    else
    {
        setNode(root_, key, value);
    }
}

template<typename Type>
inline void RadixTree<Type>::set(std::string&& key, Type value)
{
    set(key, value);
}

template<typename Type>
inline RadixTreeNodePtr<Type> RadixTree<Type>::Root()
{
    return root_;
}

template<typename Type>
inline bool RadixTree<Type>::get(const std::string& key, Type& value)
{
    return getNode(root_, key, value);
}

template<typename Type>
inline bool RadixTree<Type>::get(const std::string&& key, Type& value)
{
    return get(key, value);
}

template<typename Type>
char uv::http::RadixTree<Type>::WildCard = '*';

template<typename Type>
inline void RadixTree<Type>::setNode(RadixTreeNodePtr<Type>& node, std::string& key, Type& value)
{
    auto commonLength = GetCommomStringLength(node->key, key);
    //相同长度为0，递归next节点。
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
        //否则递归next节点
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
    //相同长度等于节点key长度，则递归child节点
    else
    {
        //key和node->key相等，则直接赋值；
        if (commonLength == key.size())
        {
            node->isEmpty = false;
            node->value = value;
        }
        else //否则，则拆分key，递归子节点
        {
            std::string key1(key, commonLength, key.size()-commonLength);
            //子节点为空，直接插入
            if (nullptr == node->child)
            {
                auto childNode = std::make_shared<RadixTreeNode<Type>>();
                *childNode = { false,key1,nullptr,nullptr,value };
                node->child = childNode;
            }
            else //否则递归子节点
            {
                setNode(node->child, key1, value);
            }
        }
    }
}   

template<typename Type>
inline bool RadixTree<Type>::getNode(RadixTreeNodePtr<Type>& node, const std::string& key, Type& value)
{
    auto commonLength = GetCommomStringLength(node->key, key);
    //通配符判定
    if (commonLength == node->key.size() - 1)
    {
        if (node->key.back() == WildCard)
        {
            value = node->value;
            return true;
        }
    }
    //相同长度为0，递归next节点。
    if (commonLength == 0)
    {
        //next节点为空，则未找到该Key
        if (nullptr == node->next)
        {
            return false ;
        }
        //否则递归next节点
        return getNode(node->next, key, value);
    }
    //相同长度小于节点key长度，则未找到该key
    else if (commonLength < node->key.size())
    {
        return false;
    }
    //相同长度等于节点key长度，则递归child节点
    else
    {
        //key和node->key相等，则直接返回value。
        if (commonLength == key.size())
        {
            if (!node->isEmpty)
            {
                value = node->value;
                return true;
            }
            //空节点
            return false;
        }
        else //否则，则拆分key，递归子节点
        {
            //子节点为空，未找到该key
            if (nullptr == node->child)
            {
                return false;
            }
            else //否则递归子节点
            {
                std::string key1(key, commonLength, key.size() - commonLength);
                return getNode(node->child, key1, value);
            }
        }
    }
}

}
}

#endif