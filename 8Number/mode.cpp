//
//  mode.c
//  8_puzzle
//
//  Created by twilight on 20-04-13.
//

#include "head.h"
#include "eightnumber.h"

//计算h_x 方法1：不在对应位置点的个数
int eightNumber::count_h(ItemPtr node)
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
