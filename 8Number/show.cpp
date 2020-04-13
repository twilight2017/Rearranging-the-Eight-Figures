
#include "show.h"
#include "ui_show.h"

Show::Show(ItemPtr first, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::show)
{
    ui->setupUi(this);
    ui->result->document()->setDefaultTextOption(QTextOption(Qt::AlignHCenter));
    //展示窗口居中显示
    int k = process_output(first);//从初始状态开始进行展示
    ui->result->append("End Of Presentation");
}

Show::~Show()
{
    delete ui;
}


//recursion output
int Show::process_output(ItemPtr node)
{
    if (node != NULL) {
        int i = process_output(node->pre);

        if (i == 0) {//展示第一个矩阵
            QString result_str;
            result_str = QString::number(node->matrix[0][0]) + " " + QString::number(node->matrix[0][1]) + " " + QString::number(node->matrix[0][2]) + "\n";
            result_str += QString::number(node->matrix[1][0]) + " " + QString::number(node->matrix[1][1]) + " " + QString::number(node->matrix[1][2]) + "\n";
            result_str += QString::number(node->matrix[2][0]) + " " + QString::number(node->matrix[2][1]) + " " + QString::number(node->matrix[2][2]) + "\n";
            result_str += "|";
            ui->result->setText(result_str);
            return find_0(node);
        }
        else {//append方法用于在原有基础上继续添加字符串
            QString result_str;
            result_str = QString::number(node->matrix[0][0]) + " " + QString::number(node->matrix[0][1]) + " " + QString::number(node->matrix[0][2]) + "\n";
            result_str += QString::number(node->matrix[1][0]) + " " + QString::number(node->matrix[1][1]) + " " + QString::number(node->matrix[1][2]) + "\n";
            result_str += QString::number(node->matrix[2][0]) + " " + QString::number(node->matrix[2][1]) + " " + QString::number(node->matrix[2][2]) + "\n";
            result_str += "|";
            ui->result->append(result_str);
            return find_0(node);
        }
    }
    else {
        return 0;
    }
}

//找到0在那个格子
int Show::find_0(ItemPtr node)
{
    int temp_i = 0, temp_j = 0, result = 0;
    for (temp_i = 0; temp_i < Matrix_size; temp_i++) {
        for (temp_j = 0; temp_j < Matrix_size; temp_j++) {
            if (node->matrix[temp_i][temp_j] == 0) {
                result = (temp_i+1)*10 + temp_j;
            }
        }
    }
    return result;
}

void Show::on_finish_clicked()
{
    this->close();
}
