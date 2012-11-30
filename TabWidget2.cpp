#include "TabWidget2.h"
#include <QApplication>
#include <QDesktopWidget>
TabWidget2::TabWidget2(QString n)
{
    this->setObjectName(n);
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
    this->setTabsClosable(true);
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
}
TabWidget2::TabWidget2()
{
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
}

void TabWidget2:: operator =(const TabWidget2& w1)
{
    *this=w1;

}


TabWidget2::TabWidget2(const TabWidget2& w1)
{
    *this=w1;
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
}

void TabWidget2::closeTab(int index)
{
    //Handle tabCloseRequested Signal and Close the Tab
    this->removeTab(index);
}
