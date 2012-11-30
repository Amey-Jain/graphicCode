#ifndef TABWIDGET1_H
#define TABWIDGET1_H
#include <QTabWidget>
#include <QString>
#include <QApplication>
#include <QtCore>
#include <QtGui>
class TabWidget1 : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget1(QString n);
    TabWidget1();
    void  operator =(const TabWidget1& w1);
    TabWidget1(const TabWidget1& w1);
public slots:
   void closeTab(int index);
};


#endif // TABWIDGET1_H
