#ifndef EIGHTNUMBER_H
#define EIGHTNUMBER_H

#include <QWidget>
#include <iostream>
#include "head.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QElapsedTimer>

namespace Ui{
    class eightNumber;
}

class eightNumber : public QWidget
{
    Q_OBJECT

public:
    explicit eightNumber(QWidget *parent = nullptr);
    ~eightNumber();

    //初始化八数码问题状态
    ItemPtr  init_problem();
    //初始化open表
    DListPtr init_DList();
    //初始化close表
    DListPtr init_Close();
    //比较两节点
    //相同返回0，不同返回1
    int compare_two_node(ItemPtr first,ItemPtr second);
    //检查输入输出有效性
    //有效返回1，无效返回0
    int check_valid(DListPtr list);
    //程序处理入口
    ItemPtr deal();
    //释放open或lose表
    void free_list(DListPtr list);
    //取open表的第一个节点
    ItemPtr get_open_first(DListPtr open);
    //遍历close表检查这个状态是否已经出现过
    int search_close(DListPtr close,ItemPtr new_node);
    //找到0所在的格子
    int find_0(ItemPtr node);
    //将节点加入open表中
    void add_open(DListPtr open,ItemPtr node);
    //将扩展节点加入close表，该节点扩展成功
    void add_close(DListPtr close,ItemPtr node);
    //用1、2、3、4代替上、下、左、右进行扩展后的填充
    void step(int x,int y,int mark,ItemPtr node,DListPtr open,DListPtr close);
    //根据空格（0）所在位置进行拓展试探，进行判重
    void give_try(int x,int y,ItemPtr node,DListPtr open,DListPtr close);
    //拓展该节点的下一个状态
    void expand(DListPtr open,DListPtr close,ItemPtr cur_node);
    //检查当前open表的第一个节点是否为目标结点
    //1是目标结点，0则不是
    int check(ItemPtr node);
    //输出全部处理过程
    int process_output(ItemPtr node);
    //找到所在标签位
    QLabel *find_label(int i);
    //动态显示open表
    int show_open(ItemPtr node);
    //动态显示closed表
    int show_closed(ItemPtr node);
    //mode
    int count_h1(ItemPtr node);
    int count_h2(ItemPtr node);
    int count_h3(ItemPtr node);
    //select 选择启发式函数
    int select_H();
    //计算扩展节点数
    int num_node();

private slots:
    void on_Begin_clicked();//开始求解
    void on_Display_clicked();//展示求解过程
    void on_random_clicked();//随机初始化状态


private:
    Ui::eightNumber *ui; //ui界面控制指针
    int terminated_matrix[Matrix_size][Matrix_size];
    DListPtr open=NULL;//open list
    DListPtr close=NULL;//close list
    ItemPtr first=NULL;
    int mode_h = 1;
    int num_index[9]={0};


};

#endif // EIGHTNUMBER_H
