#include"Widget1.h"
#include <QApplication>
#include <QDesktopWidget>
Widget1::Widget1(QString n)
{
    this->setObjectName(n);
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
}
Widget1::Widget1(const Widget1& w1)
{
    *this=w1;
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
}

void Widget1:: operator =(const Widget1& w1)
{
        *this=w1;
}

Widget1::Widget1()
{
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
}
