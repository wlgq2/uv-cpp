# RadixTree <typename Type>
Compact prefix tree.
<br></br>
```C++
RadixTree()
```
Constructor.
<br></br>
```C++
virtual ~RadixTree()
```
Destructor.
<br></br>
```C++
void set(std::string& key, Type value)
```
Set key and value.
* std::string& key : Key
* Type value : Value
<br></br>
```C++
void set(std::string&& key, Type value)
```
Set key and value with right value.
* std::string& key : Key.
* Type value : Value.
<br></br>
```C++
bool get(const std::string& key, Type& value)
```
Get value of key.
* const std::string& key : Key.
* Type& value : Get value.
* return : true:success, false: key not exist.
<br></br>
```C++
bool get(const std::string&& key, Type& value)
```
Get value of key.
* const std::string& key : Key.
* Type& value : Get value.
* return : true:success, false: key not exist.
<br></br>
```C++
RadixTreeNodePtr<Type> Root()
```
Get root node pointer, while empty then return nullptr.
* return : Root node pointer.
<br></br>
```C++
static char WildCard
```
Wildcard,the default is '*'.
<br></br>