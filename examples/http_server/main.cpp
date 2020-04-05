#include <iostream>
#include <uv/include/http/RadixTree.h>


int main(int argc, char** args)
{
    uv::http::RadixTree<int> tree;
    tree.WildCard = '*';
    tree.set("test*", 123);
    tree.set("abc:", 233);
    tree.set("123", 98);
    int value;
    tree.get("123", value);
    tree.get("abc:", value);
}
