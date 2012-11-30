#include "TabWidget1.h"
#include <QApplication>
#include <QDesktopWidget>
TabWidget1::TabWidget1(QString n)
{
    this->setObjectName(n);
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
    this->setTabsClosable(true);
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
}

TabWidget1::TabWidget1()
{
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);

}

void TabWidget1:: operator =(const TabWidget1& w1)
{
    *this=w1;
}


TabWidget1::TabWidget1(const TabWidget1& w1)
{
    *this=w1;
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
}

void TabWidget1::closeTab(int index)
{
    //Handle tabCloseRequested Signal and Close the Tab
    this->removeTab(index);
}


