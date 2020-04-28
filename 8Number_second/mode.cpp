//
//  mode.c
//  8_puzzle
//
//  Created by twilight on 20-04-13.
//

#include "head.h"
#include "eightnumber.h"
#include "math.h"

//计算h_x 方法1：不在对应位置点的个数
int eightNumber::count_h1(ItemPtr node)
{
    int mark = 0;
    int temp_i = 0, temp_j = 0;
    for (temp_i = 0; temp_i < Matrix_size; temp_i++) {
        for (temp_j = 0; temp_j < Matrix_size; temp_j++) {
            if (node->matrix[temp_i][temp_j] != terminated_matrix[temp_i][temp_j]) {
                mark++;
            }
        }
    }
    return mark;
}
//方法2：每个牌与其目标位置之间的距离和
int eightNumber::count_h2(ItemPtr node){
    int num = 0;
    int temp_i = 0, temp_j = 0;
    for (temp_i = 0; temp_i < Matrix_size; temp_i++) {
        for (temp_j = 0; temp_j < Matrix_size; temp_j++) {
            int n = num_index[node->matrix[temp_i][temp_j]];
            int t_i = n/10;//得到目标位置行号
            int t_j = n%10;//得到目标位置列号
            num+=abs(temp_i-t_i)+abs(temp_j-t_j);

        }
    }
    return num;

}
//方法3：待扩展 目前是h(x)=0
int eightNumber::count_h3(ItemPtr node){
    return 0;
}
