#ifndef QUEEN_H
#define QUEEN_H

class Queen
{
public:
    Queen(int len,int* result);
    //运算解问题
    void solve(int col);
    //获取解个数
    int getResultCnt();
private:
    //判断皇后位置是否合法
    bool isEffective(int row,int col);
    //要解的N皇后问题长度
    static int length;
    //有多少解
    int resultCnt;
    //存储解法的数组指针（一个线程使用一块缓存）
    int* resultRow;
};

#endif // QUEUE_H
