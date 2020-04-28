#ifndef SHOW_H
#define SHOW_H

#include <QWidget>
#include "head.h"

namespace Ui {
class show;
}

class Show : public QWidget
{
    Q_OBJECT

public:
    int process_output(ItemPtr node);
    int find_0(ItemPtr node);
    explicit Show(ItemPtr first, QWidget *parent = 0);
    ~Show();

private slots:
    void on_finish_clicked();

private:
    Ui::show *ui;
};

#endif // SHOW_H
