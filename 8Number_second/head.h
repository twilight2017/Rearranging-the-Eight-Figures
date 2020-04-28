#ifndef HEAD_H
#define HEAD_H



#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define Matrix_size 3

//state descriptiion

class item{
public:
    int matrix[Matrix_size][Matrix_size];
    int h_x;
    int f_x;
    int g_x;
    //f(x)=g(x)+h(x)
    item *next; //队列中之前的状态
    item *pre;  //队列中之后的状态
};

typedef  item * ItemPtr;

//用于管理状态表的队列
class DList{
public:
    ItemPtr head;
    ItemPtr tail;
};

typedef  DList * DListPtr;

//声明该方法中计算h(x)的方法：当前图中不在对应目标点中的个数
int count_h(ItemPtr node);

#endif // HEAD_H
