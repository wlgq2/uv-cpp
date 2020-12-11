#include <iostream>
#include <random>
#include <map>
#include <uv/include/http/RadixTree.hpp>


using namespace uv;
using namespace http;
using namespace std;

template<typename Type>
struct KV
{
    std::string key;
    Type  value;
};


//随机插入若干节点，并测试
template<typename Type>
bool TestRand(RadixTree<Type>& tree,uint64_t cnt)
{
    //生成Key值不相同若干个kv。
    std::vector<struct KV<Type>> kvs;
    for (uint64_t i = 0;i < cnt;i++)
    {
        struct KV<Type> kv = { std::to_string(i),i };
        kvs.push_back(kv);
    }

    //随机顺序取出元素插入radix tree.
    std::map<std::string, Type> kvMap;
    std::default_random_engine random;
    std::uniform_int_distribution<int> dis(0, (int)cnt);
    while (!kvs.empty())
    {
        int index = dis(random) % kvs.size();
        auto kv = kvs[index];
        tree.set(kv.key, kv.value);
        kvs[index] = kvs.back();
        kvs.pop_back();
        //std::cout << "{ " << kv.key << "," << kv.value << "}"<<std::endl;
        kvMap[kv.key] = kv.value;
    }

    //遍历对比kvmap与radix tree值
    for (auto& kv : kvMap)
    {
        Type value;
        std::string key = kv.first;
        if (!tree.get(key, value))
        {
            //未找到该key
            std::cout << "not find key " << kv.first << std::endl;
            return false;
        }
        if (value != kv.second)
        {
            //value值不正确
            std::cout << "error key " << kv.first << " value " << kv.second << " but " << value << std::endl;
            return false;
        }

    }
    return true;

}
int main(int argc, char** args)
{
    std::cout << "wait ..." << std::endl;
    int cnt = 1000000;
    RadixTree<uint64_t> tree;
    //生成cnt个kv并随机顺序插入检测。
    if (TestRand(tree, cnt))
    {
        std::cout << "test success:" << cnt << std::endl;
    }
}

//遍历节点
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
        cout << nodeKey << ":" << node->value << std::endl;
    }
    else
    {
        cout << nodeKey << ": empty" << std::endl;
    }
    findAll(node->child, nodeKey);
    findAll(node->next, key);
}
