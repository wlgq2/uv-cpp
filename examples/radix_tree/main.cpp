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

int main(int argc, char** args)
{
    RadixTree<int> tree;
    tree.setNode("abcdef12345", 1);
    tree.setNode("12345", 2);
    tree.setNode("abcdef", 3);
    tree.setNode("abcde123", 4);
    tree.setNode("abcde", 5);
    tree.setNode("abc", 6);
    tree.setNode("abcde", 7);
    tree.setNode("abcdexxxx", 8);
    tree.setNode("abcdeyyy", 9);
    std::string start = "";
    findAll(tree.begin(), start);
}
