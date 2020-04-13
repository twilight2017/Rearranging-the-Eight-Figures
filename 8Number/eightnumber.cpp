#include "head.h"
#include "show.h"
#include "ui_show.h"
#include "eightnumber.h"
#include "ui_eightnumber.h"

#include<QRegExpValidator>

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

    open = init_DList();
    close = init_Close();
    terminated_matrix[0][0] = ui->final_1->text().toInt();
    terminated_matrix[0][1] = ui->final_2->text().toInt();
    terminated_matrix[0][2] = ui->final_3->text().toInt();
    terminated_matrix[1][0] = ui->final_4->text().toInt();
    terminated_matrix[1][1] = ui->final_5->text().toInt();
    terminated_matrix[1][2] = ui->final_6->text().toInt();
    terminated_matrix[2][0] = ui->final_7->text().toInt();
    terminated_matrix[2][1] = ui->final_8->text().toInt();
    terminated_matrix[2][2] = ui->final_9->text().toInt();
    //qDebug() << terminated_matrix[0][0] << endl;
    if(open && close) {//所有条件都ok
        //数据ok
        int vali = check_valid(open);
        if(vali == 1) {
            first = deal();
            int non = process_output(first);
        }
        else if(vali == 0){
            QMessageBox::critical(this, "无解", "Try to change another group of data", QMessageBox::Yes, QMessageBox::Yes);
        }
    }
}
void eightNumber::on_Display_clicked()
{
    Show* my_show=new Show(first);
    my_show->show();
}
