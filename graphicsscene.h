#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QPainter>
#include <QWidget>
#include <QPen>
#include <QTextStream>
#include <QTextItem>
#include <QRectF>
#include <QGraphicsItem>
#include <QtGui>
#include <QVector>
#include <QFont>
class GraphicsScene: public QGraphicsScene
{

private:
    int flag;
    int xdistance;
    int ydistance;
    QStack < QPair<int , int> > cord_stack ;
    QStack < QPair<int , int> > blockendstack ;
    QStack < QPair<int , int> > tempstack ;

    QStack <int> ifstack;
    int inloops;

    QPair<int , int> pair_up;
    QPair<int , int> pair_side;
    int loop_outside;
    int x_max;

public:
    GraphicsScene(QWidget* w)
    {
        setParent(w);
        flag=0;
        xdistance= this->width();
        ydistance= 10 ;//! see and give a value
        QTextStream out(stdout);
        x_max=xdistance + 80;
        loop_outside=0;
        inloops=0;
    }
    QVector<QString> instruction;

  void drawForeground(QPainter *painter,QRectF rect)
  {
      QString instruction1;
       int num,i,j,k;
       QTextStream out(stdout);
       for(i=0;i<instruction.size();i++)
       {
           instruction1=instruction[i];
           for(j=0;j<instruction1.length();j++)
            {
                if(instruction1[j]=='@')
                    break;
            }
           num=0;
           for(k=0;k<j;k++)
           {
                num=num*10+(instruction1[k].toLatin1()-48);
           }
           drawLines(painter,num, instruction1.right(instruction1.length()-j-1));
       }

        xdistance=this->width()/4;
        x_max=xdistance + 80;
        ydistance= 10 ;         //! see and give a value

       QPen pen(Qt::black, 2, Qt::SolidLine);

   }

    void drawLines(QPainter *qp,int a, QString str);
};

#endif // GRAPHICSSCENE_H
