
#include "eightnumber.h"
#include "head.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eightNumber w;
    w.show();
    return a.exec();
}
