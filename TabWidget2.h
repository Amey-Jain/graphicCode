#ifndef TABWIDGET2_H
#define TABWIDGET2_H
#include <QTabWidget>
#include <QString>
#include <QApplication>
#include <QtCore>
#include <QtGui>
class TabWidget2 : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget2(QString n);
    TabWidget2();
    void operator =(const TabWidget2& w1);
    TabWidget2(const TabWidget2& w1);
public slots:
   void closeTab(int index);
};
#endif // TABWIDGET2_H
