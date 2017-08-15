#include "Queen.h"
#include <iostream>

using namespace std;

int Queen::length;

Queen::Queen(int len,int* result)
    :resultCnt(0),
    resultRow(result)
{
    length = len;
}

bool Queen::isEffective(int col,int row)
{
    for(int i=0;i<col;i++)
    {
        //判断皇后是否行相同，或者对角线上。
        if(resultRow[i]==row || abs(i-col)==abs(resultRow[i]-row))
            return false;
    }
    return true;
}

void Queen::solve(int col)
{
    if(col==length)
    {
        resultCnt++;
        return;
    }
    for(int i=0;i<length;i++)
    {
        if(isEffective(col,i))
        {
            resultRow[col] = i;
            solve(col+1);
        }
    }
}

int Queen::getResultCnt()
{
    return resultCnt;
}
