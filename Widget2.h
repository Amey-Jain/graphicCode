#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QFile>
#include <QPair>
#include <QStack>
#include <QPainter>
#include <QTextStream>
#include <QtCore/qmath.h>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QGraphicsView>
#include "graphicsscene.h"

class Widget2 : public QScrollArea
{
public:
    Widget2(QString n,QString document);
    QVector<QString> instruction;
    void operator =(const Widget2& w1);
    Widget2(const Widget2& w1);

    Widget2();
    GraphicsScene *scene;
    GraphicsScene *scene1;

private:

    int flag;
    int xdistance;
    int ydistance;
    QStack < QPair<int , int> > cord_stack ;
    QStack < QPair<int , int> > blockendstack ;
    QStack < QPair<int , int> > tempstack ;

    QPair<int , int> pair_up;
    QPair<int , int> pair_side;
    int loop_outside;
    int x_max;
    QWidget chart;
    QWidget text;

    QHBoxLayout *horizontalLayout_1;

    QHBoxLayout *horizontalLayout_2;

};


#endif // WIDGET2_H
