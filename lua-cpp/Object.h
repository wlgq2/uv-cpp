#ifndef TEST_H
#define TEST_H

#include <iostream>

class Object
{
private :
    std::string name;
    int    value;
public :
    Object(std::string& str,int num)
    :name(str),
    value(num)
    {
    }

    std::string& getName()
    {
        return name;
    }
    int getValue()
    {
        return value;
    }
    void setValue(long num)
    {
        value = num;
    }
    void setName(std::string& str)
    {
        name = str;
    }
};
#endif // TEST_H
