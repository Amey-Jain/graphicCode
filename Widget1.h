#ifndef WIDGET1_H
#define WIDGET1_H

#include <QWidget>
#include <QString>
class Widget1 : public QWidget
{
public:
    Widget1(QString n);
    Widget1(const Widget1& w1);
    void operator =(const Widget1& w1);
    Widget1();
};

#endif // WIDGET1_H
