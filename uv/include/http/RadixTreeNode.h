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
class RadixTreeNode
{
public:
    RadixTreeNode();
    RadixTreeNode(std::string& key, Type value);
    RadixTreeNode(std::string&& key, Type value);
    virtual ~RadixTreeNode();

    bool setNode(std::string& key,Type value);
    bool setNode(std::string&& key, Type value);

    void appendChild(std::shared_ptr<RadixTreeNode<Type>> child);

private:
    std::string key_;
    std::shared_ptr<Type> value_;
    std::list<std::shared_ptr<RadixTreeNode<Type>>> childs_;

    int getCommomLength(std::string& str1, std::string& str2);
};
template<typename Type>
inline RadixTreeNode<Type>::RadixTreeNode()
{
    key_ = "";
    value_ = nullptr;
}

template<typename Type>
inline RadixTreeNode<Type>::RadixTreeNode(std::string& key, Type value)
    :key_(key),
    value_(new Type(value))
{
}

template<typename Type>
inline RadixTreeNode<Type>::RadixTreeNode(std::string&& key, Type value)
    :RadixTreeNode(key,value)
{
}

template<typename Type>
inline RadixTreeNode<Type>::~RadixTreeNode()
{
}

template<typename Type>
inline bool RadixTreeNode<Type>::setNode(std::string& key, Type value)
{
    int commomLength = getCommomLength(key, key_);
    if (commomLength == 0)
    {
        //没有找到共有字符串，则返回false.
        return false;
    }
    //key一样，则直接替换value.
    if (commomLength == key_.size())
    {
        value_ = value;
        return true;
    }
    if (commomLength > key_.size())
    {
        std::string childKey(key, commomLength, key.size() - commomLength);
        for (auto it = childs_.begin();it != childs_.end();it++)
        {
            auto child = make_shared<RadixTreeNode<Type>>(childKey, value);
        }
    }
    
}

template<typename Type>
inline bool RadixTreeNode<Type>::setNode(std::string&& key, Type value)
{
    return setNode(key, value);
}

template<typename Type>
inline void RadixTreeNode<Type>::appendChild(std::shared_ptr<RadixTreeNode<Type>> child)
{
    childs_.push_back(child);
}

template<typename Type>
inline int RadixTreeNode<Type>::getCommomLength(std::string& str1, std::string& str2)
{
    int i = 0;
    for (;i < str1.size() && i < str2.size();i++)
    {
        if (str1[i] != str2[i])
        {
            break;
        }
    }
    return i;
}

}
}