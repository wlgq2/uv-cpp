/*
    Author: object_he@yeah.net

    Last modified: 2017-7-4
    
    Filename: Object.h
    
    Description: 
*/



#ifndef OBJECT_H
#define OBJECT_H

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
#endif 
