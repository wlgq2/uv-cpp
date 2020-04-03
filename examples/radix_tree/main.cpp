#include <iostream>
#include <uv/include/http/RadixTree.h>


using namespace uv;
using namespace http;
using namespace std;

template<typename Type>
void findAll(RadixTreeNodePtr<Type> node, std::string& key)
{
    if (nullptr == node)
    {
        return;
    }
    auto nodeKey = key + node->key;
    if (!node->isEmpty)
    {
        cout << nodeKey<<":"<<node->value << std::endl;
    }
    else
    {
        cout << nodeKey << ": empty" << std::endl;
    }
    findAll(node->child, nodeKey);
    findAll(node->next, key);
}
struct KV
{
    std::string key;
    int  value;
};
int main(int argc, char** args)
{
    struct KV kvs[] =
    {
        {"abcdef12345", 1},
        {"12345", 2},
        {"abcdef", 3},
        {"abcde123", 4},
        //{"abcde", 5},
        {"abc", 6},
        {"abcde", 7},
        {"abcdexxxx", 8},
        {"abcdeyyy", 9},
    };
    RadixTree<int> tree;
    auto size = sizeof(kvs) / sizeof(struct KV);
    for (int i = 0;i < size;i++)
    {
        tree.setNode(kvs[i].key, kvs[i].value);
    }

    std::string start = "";
    findAll(tree.begin(), start);
    std::cout << std::endl;
    for (int i = 0;i < size; i++)
    {
        int value;
        if (tree.getNode(kvs[i].key, value))
        {
            if (value != kvs[i].value)
            {
                std::cout << "error value key :" << kvs[i].key << " value :"<<value << std::endl;
            }
            else
            {
                std::cout << kvs[i].key << " :" << value << std::endl;
            }
        }
        else
        {
            std::cout << "can not find key :" << kvs[i].key << std::endl;
        }
    }
}
