#include "Widget2.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QtCore/qmath.h>
#include <QString>
#include <QPair>
#include <QTextEdit>
#include <QPlainTextEdit>


Widget2::Widget2(QString n,QString document)
{
    this->setObjectName(n);
    chart.setParent(this);
    text.setParent(this);
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();

    scene1= new GraphicsScene(&text);
    scene= new GraphicsScene(&chart);



    QGraphicsView *view = new QGraphicsView(scene);
    QGraphicsView *view1 = new QGraphicsView(scene1);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    chart.setGeometry(QRect(0, 0, width/2-20, height-130));
    text.setGeometry(QRect(width/2-20, 0, width/2-20, height-130));

    horizontalLayout_1 = new QHBoxLayout(&chart);
    horizontalLayout_2 = new QHBoxLayout(&text);

    horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);

    horizontalLayout_1->addWidget(view);
    horizontalLayout_2->addWidget(view1);


    this->setGeometry(0,0,width,height);
    flag=0;
    QSize distance=this->size();
    xdistance= distance.width();
    ydistance= 10 ;//! see and give a value
    QTextStream out(stdout);

    QPainter qp(this);

    instruction.clear();
    scene->drawForeground(&qp,scene->sceneRect());
    scene1->drawForeground(&qp,scene1->sceneRect());


    //open the file in scene 1




}
Widget2::Widget2()
{
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
    flag=0;
}

void Widget2::operator =(const Widget2& w1)
{
    *this=w1;

}
Widget2::Widget2(const Widget2& w1)
{
    *this=w1;
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    this->setGeometry(0,0,width,height);
    flag=0;
}
