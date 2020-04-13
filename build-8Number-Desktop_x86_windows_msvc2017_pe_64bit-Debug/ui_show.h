/********************************************************************************
** Form generated from reading UI file 'show.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_H
#define UI_SHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_show
{
public:
    QPushButton *finish;
    QTextBrowser *result;

    void setupUi(QWidget *show)
    {
        if (show->objectName().isEmpty())
            show->setObjectName(QString::fromUtf8("show"));
        show->resize(350, 600);
        finish = new QPushButton(show);
        finish->setObjectName(QString::fromUtf8("finish"));
        finish->setGeometry(QRect(140, 490, 80, 31));
        result = new QTextBrowser(show);
        result->setObjectName(QString::fromUtf8("result"));
        result->setGeometry(QRect(25, 10, 301, 421));

        retranslateUi(show);

        QMetaObject::connectSlotsByName(show);
    } // setupUi

    void retranslateUi(QWidget *show)
    {
        show->setWindowTitle(QCoreApplication::translate("show", "show", nullptr));
        finish->setText(QCoreApplication::translate("show", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class show: public Ui_show {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_H
