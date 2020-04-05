#include <iostream>
#include <uv/include/http/RadixTree.h>


int main(int argc, char** args)
{
    uv::http::RadixTree<int> tree;
    tree.WildCard = '*';
    tree.setNode("test*", 123);
    tree.setNode("abc:", 233);
    tree.setNode("123", 98);
    int value;
    tree.getNode("123", value);
    tree.getNode("abc:", value);
}
