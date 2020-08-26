# RadixTree <typename Type>
压缩前缀树。
<br></br>
```C++
RadixTree()
```
构造函数
<br></br>
```C++
virtual ~RadixTree()
```
析构函数
<br></br>
```C++
void set(std::string& key, Type value)
```
设置key和存储值。
* std::string& key : 键值。
* Type value : 存储值。
<br></br>
```C++
void set(std::string&& key, Type value)
```
设置key和存储值。
* std::string&& key : 键值右值。
* Type value : 存储值。
<br></br>
```C++
bool get(const std::string& key, Type& value)
```
获取某键对应值。
* const std::string& key : 键值。
* Type& value : 键对应值。
* 返回值 : true为获取成功，false为键值不存在。
<br></br>
```C++
bool get(const std::string&& key, Type& value)
```
获取某键对应值。
* const std::string& key : 键值右值。
* Type& value : 键对应值。
* 返回值 : true为获取成功，false为键值不存在。
<br></br>
```C++
RadixTreeNodePtr<Type> Root()
```
返回根节点智能指针，树为空则返回nullptr。
* 返回值 : 根节点指针。
<br></br>
```C++
static char WildCard
```
键值通配符，默认为'*'。
<br></br>