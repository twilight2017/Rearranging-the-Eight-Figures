#include "head.h"
#include "show.h"
#include "ui_show.h"
#include "eightnumber.h"
#include "ui_eightnumber.h"

#include<QRegExpValidator>
#include <QTime>
#include <QtGlobal>
eightNumber::eightNumber(QWidget *parent) :

    QWidget(parent),
    ui(new Ui::eightNumber)
{
    ui->setupUi(this);
    QRegExp regx("[0-9]$");
    QValidator *validator = new QRegExpValidator(regx);
    ui->init_1->setValidator( validator );
    ui->init_2->setValidator( validator );
    ui->init_3->setValidator( validator );
    ui->init_4->setValidator( validator );
    ui->init_5->setValidator( validator );
    ui->init_6->setValidator( validator );
    ui->init_7->setValidator( validator );
    ui->init_8->setValidator( validator );
    ui->init_9->setValidator( validator );
    ui->final_1->setValidator( validator );
    ui->final_2->setValidator( validator );
    ui->final_3->setValidator( validator );
    ui->final_4->setValidator( validator );
    ui->final_5->setValidator( validator );
    ui->final_6->setValidator( validator );
    ui->final_7->setValidator( validator );
    ui->final_8->setValidator( validator );
    ui->final_9->setValidator( validator );
}

eightNumber::~eightNumber()
{
    free(first);
    free_list(open);
    free_list(close);
    delete ui;
}

void eightNumber::on_Begin_clicked()
{
    QTime t;
    t.start();
    if (first) {
        free(first);
        first = NULL;
    }
    if (open) {
        free_list(open);
        open = NULL;
    }
    if (close) {
        free_list(close);
        close = NULL;
    }
    mode_h = select_H();
    open = init_DList();
    close = init_Close();
    ui->open->clear();
    ui->closed->clear();
    //初始化terminated_matrix，并记录下1-8这8个数字所在的位置，便于后续计算hx
    terminated_matrix[0][0] = ui->final_1->text().toInt();
    num_index[ui->final_1->text().toInt()] = 0;
    terminated_matrix[0][1] = ui->final_2->text().toInt();
    num_index[ui->final_2->text().toInt()] = 1;
    terminated_matrix[0][2] = ui->final_3->text().toInt();
    num_index[ui->final_3->text().toInt()] = 2;
    terminated_matrix[1][0] = ui->final_4->text().toInt();
    num_index[ui->final_4->text().toInt()] = 10;
    terminated_matrix[1][1] = ui->final_5->text().toInt();
    num_index[ui->final_5->text().toInt()] = 11;
    terminated_matrix[1][2] = ui->final_6->text().toInt();
    num_index[ui->final_6->text().toInt()] = 12;
    terminated_matrix[2][0] = ui->final_7->text().toInt();
    num_index[ui->final_7->text().toInt()] = 20;
    terminated_matrix[2][1] = ui->final_8->text().toInt();
    num_index[ui->final_8->text().toInt()] = 21;
    terminated_matrix[2][2] = ui->final_9->text().toInt();
    num_index[ui->final_9->text().toInt()] = 22;
    //qDebug() << terminated_matrix[0][0] << endl;
    if(open && close) {//所有条件都ok
        //数据ok
        int vali = check_valid(open); //不重复、只能有1-8出现
        if(vali == 1) {
            first = deal();
            int non = process_output(first);
        }
        else if(vali == 0){
            QMessageBox::critical(this, "无解", "Try to change another group of data", QMessageBox::Yes, QMessageBox::Yes);
        }
    }

    int ms = t.elapsed();
    ui->label_3->setText(QString::number(ms));
    ui->label_4->setText("   "+QString::number(num_node()));
}
void eightNumber::on_Display_clicked()
{
    Show* my_show=new Show(first);
    my_show->show();
}
void eightNumber::on_random_clicked(){
    //随机初始化状态
    QList<int> numberList;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int num =qrand()%9;
    ui->init_1->setText(QString::number(num));
    numberList.append(num);
    bool flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_2->setText(QString::number(num));
            flag=false;
        }
    }
    flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_3->setText(QString::number(num));
            flag=false;
        }
    }
    flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_4->setText(QString::number(num));
            flag=false;
        }
    }
    flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_5->setText(QString::number(num));
            flag=false;
        }
    }
    flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_6->setText(QString::number(num));
            flag=false;
        }
    }
    flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_7->setText(QString::number(num));
            flag=false;
        }
    }
    flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_8->setText(QString::number(num));
            flag=false;
        }
    }
    flag = true;
    while(flag){
        num =qrand()%9;
        bool f = false;
        for(int i=0;i<numberList.size();i++){
            if(numberList[i] == num){
                f = true;
            }
        }
        if(!f){
            numberList.append(num);
            ui->init_9->setText(QString::number(num));
            flag=false;
        }
    }
}
