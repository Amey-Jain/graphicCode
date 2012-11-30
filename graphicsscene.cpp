#include "graphicsscene.h"

void GraphicsScene::drawLines(QPainter *qp,int a, QString str)
{
    QPen pen(Qt::black, 2, Qt::SolidLine);
    //! qp->setPen(QColor("#c56c00"));
    QTextStream out(stdout);
    //! out<<" switch : "<<a<<"   "<<str<<endl;
    switch(a)
    {
    case 1:                                                   //! rectangle
    {
         //! qp->setPen(pen);
         //! qp->setBrush(QBrush("#c56c00"));
         int strlen= str.size();
         int rectlenbase=  210 ;//! set this
         int rectheightbase= 20  ; //! set this
         float multiple= ceil(strlen/20.0);

         if(multiple == 1)
         {
             rectlenbase = 5 + strlen*8 + 4;
             if(rectlenbase < 40)
             {
                 rectlenbase = 40;      //! 40 is the minimal value to start the size of rect
             }
         }
         //! qp->drawRect(xdistance-(rectlenbase/2), ydistance, rectlenbase, multiple*(rectheightbase)+10);
         QGraphicsRectItem *rect1=new QGraphicsRectItem(0, 0, rectlenbase, multiple*(rectheightbase)+10);
         rect1->setPos(xdistance-(rectlenbase/2), ydistance);
         this->addItem(rect1);
         pair_up.first = xdistance;
         pair_up.second = ydistance+ multiple*(rectheightbase)+10+10;

         if(x_max <= (xdistance + (rectlenbase/2)))
         {
             x_max= (xdistance + (rectlenbase/2)+10);
         }

        //! ydistance+=rectheightbase;
         out<<"multiple : "<<multiple<<endl;
         while(multiple-->0)
         {
             if(str.length()>20 && str.at(20)!=' ')
             {
               //!  qp->drawText(xdistance-(rectlenbase/2)+5,ydistance,(str.left(20)).append('-'));
                 QGraphicsTextItem *txt=new QGraphicsTextItem((str.left(20)).append('-'));
                 txt->setPos(xdistance-(rectlenbase/2)+5,ydistance);
                 this->addItem(txt);
             }

             else
             {
               //!  qp->drawText(xdistance-(rectlenbase/2)+5,ydistance,str.left(20));
                 QGraphicsTextItem *txt=new QGraphicsTextItem(str.left(20));
                 txt->setPos(xdistance-(rectlenbase/2)+5,ydistance);
                 this->addItem(txt);
             }
             ydistance+=rectheightbase;
             str=str.right(str.length()-20);
         }
         ydistance+= 10 ;
         //! ydistance = ydistance - rectheightbase ;
         break;
    }

    case 5:                                                      //! draw line
    {
           //! pen.setStyle(Qt::SolidLine);
            //! qp->setPen(pen);
            //! qp->setBrush(QBrush("#1ac500"));
            //! qp->drawLine(xdistance, ydistance, xdistance , ydistance+20);
            QGraphicsLineItem *line=new QGraphicsLineItem(xdistance,ydistance,xdistance,ydistance+20);
             //! line.setPos(xdistance, ydistance);
             this->addItem(line);
             ydistance = ydistance+20 ;
            break;
    }
    case 2:                                                      //! ellipse
    {
            pen.setStyle(Qt::SolidLine);
            //! qp->setPen(pen);
            //! qp->setBrush(QBrush("#539e47"));
            int strlen= str.size();
            int ellipselenbase=  200 ;//! set this
            int ellipseheightbase= 25 ; //! set this
            float multiple= ceil(strlen/28.0);
            if(multiple == 1)
            {

                ellipselenbase = strlen*10;
                if(ellipselenbase < 50)
                {
                    ellipselenbase = 60;      //! 50 is the minimal value to start the size of ellipse
                }
            //! qp->drawEllipse(xdistance-(ellipselenbase/2), ydistance, ellipselenbase, multiple*(ellipseheightbase)+10);

            QGraphicsEllipseItem *ellipse=new QGraphicsEllipseItem(0,0, ellipselenbase, multiple*(ellipseheightbase)+10);
            ellipse->setPos(xdistance-(ellipselenbase/2), ydistance);
            this->addItem(ellipse);

            if(x_max <= xdistance + (ellipselenbase/2)) x_max= xdistance + (ellipselenbase/2)+10;
            //! ydistance+=  ellipseheightbase;
            //!  qp->drawText(xdistance-(ellipselenbase/2)+8,ydistance,str);

            QGraphicsTextItem *txt=new QGraphicsTextItem(str);
            txt->setPos(xdistance-(ellipselenbase/2)+5,ydistance+5);
            this->addItem(txt);
            ydistance += ellipseheightbase + 10;
            }

            else
            {
                out<<"multiple : "<<multiple<<endl;
                //! qp->drawEllipse(xdistance-(ellipselenbase/2), ydistance, ellipselenbase, multiple*(ellipseheightbase)+30);
                QGraphicsEllipseItem *ellipse=new QGraphicsEllipseItem(0,0, ellipselenbase, multiple*(ellipseheightbase)+30);
                ellipse->setPos(xdistance-(ellipselenbase/2), ydistance);
                this->addItem(ellipse);

                if(x_max <= xdistance + (ellipselenbase/2)) x_max= xdistance + (ellipselenbase/2)+10;
                ydistance+=  10 ;
                while(multiple-->0)
                {
                    if(str.length()>28 && str.at(28)!=' ')
                    {
                       //! qp->drawText(xdistance-(ellipselenbase/2)+15,ydistance,(str.left(28)).append('-'));
                        QGraphicsTextItem *txt=new QGraphicsTextItem((str.left(28)).append('-'));
                        txt->setPos(xdistance-(ellipselenbase/2)+15,ydistance+5);
                        this->addItem(txt);
                    }
                    else
                    {
                        //! qp->drawText(xdistance-(ellipselenbase/2)+15,ydistance,str.left(28));
                        QGraphicsTextItem *txt=new QGraphicsTextItem(str.left(28));
                        txt->setPos(xdistance-(ellipselenbase/2)+15,ydistance+5);
                        this->addItem(txt);
                    }

                    ydistance+=ellipseheightbase;
                    str=str.right(str.length()-28);
                }
               //! ydistance += multiple*(ellipseheightbase)+20 ;
                 ydistance += 20 ;
            }
            break;
    }

    case 3:                                                                //! rhombus
    {
            //! pen.setStyle(Qt::SolidLine);
            //! qp->setPen(pen);
            int strlen= str.size();
            int rectlenbase=  210 ;//! set this
            int rectheightbase= 40  ; //! set this
            float multiple= ceil(strlen/20.0);
            if(multiple == 1)
            {
                rectlenbase = 40 + strlen*10;
                if(rectlenbase < 85)
                {
                    rectlenbase = 100;      //! 40 is the minimal value to start the size of rect
                }
            }
            //! qp->drawRect(xdistance-(rectlenbase/2), ydistance, rectlenbase, multiple*(rectheightbase)+10);

                  QPointF a1(xdistance , ydistance);
                  QPointF a2(xdistance+(rectlenbase/2), ydistance+((multiple*rectheightbase)/2));
                  QPointF a3(xdistance, ydistance+(rectheightbase*multiple));
                  QPointF a4(xdistance-(rectlenbase/2), ydistance+((multiple*rectheightbase)/2));

                  QVector<QPointF> points;
                  points.push_back(a1);
                  points.push_back(a2);
                  points.push_back(a3);
                  points.push_back(a4);

           //! qp->drawPolygon(points, 4);
             QPolygonF *rhombus=new QPolygonF(points);
             QGraphicsPolygonItem *polygon=new QGraphicsPolygonItem(*rhombus);
             polygon->setPos(0,0);
             this->addItem(polygon);

           pair_up.first = xdistance;
           pair_up.second = ydistance-10 ;
           pair_side.first = xdistance+(rectlenbase/2);
           pair_side.second = ydistance+((multiple*rectheightbase)/2) ;
           tempstack.push(pair_side);

           if(x_max <= xdistance + (rectlenbase/2)) x_max= xdistance + (rectlenbase/2)+10;

           ydistance+= multiple*10;
           int temp = multiple ;
           out<<"multiple : "<<multiple<<endl;

           while(multiple-->0)
            {
               if(str.length()>20 && str.at(20)!=' ')
               {
                   //! qp->drawText(xdistance-(rectlenbase/2)+40,ydistance,(str.left(24)).append('-'));
                   QGraphicsTextItem *txt=new QGraphicsTextItem((str.left(20)).append('-'));
                   txt->setPos(xdistance-(rectlenbase/2)+35,ydistance);
                   this->addItem(txt);
               }
               else
               {
                   //! qp->drawText(xdistance-(rectlenbase/2)+40,ydistance,str.left(24));
                   QGraphicsTextItem *txt=new QGraphicsTextItem(str.left(20));
                   txt->setPos(xdistance-(rectlenbase/2)+35,ydistance);
                   this->addItem(txt);
               }
                ydistance+=20;
                str=str.right(str.length()-20);
            }
            ydistance +=  temp*10;
            //! ydistance = ydistance - 15 ;

            break;
           }

    case 9:                                                     //! parallelgram
    {
            pen.setStyle(Qt::SolidLine);
            qp->setPen(pen);
            int strlen= str.size();
            int rectlenbase=  200 ;//! set this
            int rectheightbase= 20  ; //! set this
            float multiple= ceil(strlen/25.0);
            out<<"ssomthing"<<xdistance-(rectlenbase/2)<<"  "<< ydistance <<" "<< rectlenbase<<"  "<< multiple*(rectheightbase+2)<<endl;
            out<<"string "<<str<<endl;
            if(multiple == 1)
            {
                rectlenbase = strlen*9;
                if(rectlenbase < 50)
                {
                    rectlenbase = 60;      //! 40 is the minimal value to start the size of rect
                }
            }
            //! qp->drawRect(xdistance-(rectlenbase/2), ydistance, rectlenbase, multiple*(rectheightbase)+10);

             QPointF a1(xdistance-(rectlenbase/2), ydistance);
             QPointF a2(xdistance+(rectlenbase/2), ydistance);
             QPointF a3(xdistance+(rectlenbase/2)-14*multiple, ydistance+multiple*(rectheightbase)+10);
             QPointF a4(xdistance-(rectlenbase/2)-14*multiple, ydistance+multiple*(rectheightbase)+10);

             QVector<QPointF> points;
             points.push_back(a1);
             points.push_back(a2);
             points.push_back(a3);
             points.push_back(a4);

        QPolygonF *rhombus=new QPolygonF(points);
        QGraphicsPolygonItem *polygon=new QGraphicsPolygonItem(*rhombus);
        polygon->setPos(0,0);
        this->addItem(polygon);
         //!  qp->drawPolygon(points, 4);

         if(x_max <= xdistance + (rectlenbase/2)) x_max= xdistance + (rectlenbase/2)+10;

           //! ydistance+=rectheightbase;
            out<<"parallellogram multiple : "<<multiple<<endl;
           while(multiple-->0)
            {
               if(str.length()>25 && str.at(25)!=' ')
               {
                   //!  qp->drawText(xdistance-(rectlenbase/2)+3,ydistance,(str.left(20)).append('-'));
                   QGraphicsTextItem *txt=new QGraphicsTextItem((str.left(25)).append('-'));
                   txt->setPos(xdistance-(rectlenbase/2)+8,ydistance);
                   this->addItem(txt);
               }
               else
               {
                   //! qp->drawText(xdistance-(rectlenbase/2)+3,ydistance,str.left(20));
                   QGraphicsTextItem *txt=new QGraphicsTextItem(str.left(25));
                   txt->setPos(xdistance-(rectlenbase/2)+5,ydistance);
                   this->addItem(txt);
               }
                ydistance+=rectheightbase;
                str=str.right(str.length()-25);
            }
            ydistance+= 10 ;
           //!  ydistance = ydistance - rectheightbase ;
            break;
    }

    case 4:                                                 //! store cordinates for if-else switch
    {
        out<<"in here :: 4"<<endl;
        //! pen.setStyle(Qt::DashDotDotLine);
        //! qp->setPen(pen);
        QPair<int,int> cordinates;
        cordinates = tempstack.pop();
        cord_stack.push(cordinates);
        if(loop_outside==0 && ifstack.isEmpty() && inloops==0)
            x_max = xdistance + 80;
        break;
    }

    case 12:                                                 //! store cordinates for while and for
    {
        cord_stack.push(pair_up);
        if(loop_outside==0 && ifstack.isEmpty() && inloops==0)
            x_max =  xdistance + 80;
        loop_outside++;
        x_max-=5;
        break;
     }

    case 8:                                                           //! draw closed sideline for loops
    {
       //! pen.setStyle(Qt::SolidLine);
       //! qp->setPen(pen);
       loop_outside--;
       x_max +=  10;

       QPair<int,int> cordinates;
       cordinates = tempstack.pop();
       cordinates = cord_stack.pop();
       inloops=0;

      //! qp->drawLine(xdistance, ydistance, x_max , ydistance);
        QGraphicsLineItem *line=new QGraphicsLineItem(xdistance, ydistance, x_max , ydistance);
        this->addItem(line);
        //! qp->drawLine(x_max, ydistance, x_max , cordinates.second);
        QGraphicsLineItem *line1=new QGraphicsLineItem(x_max, ydistance, x_max , cordinates.second);
        this->addItem(line1);
        //! qp->drawLine( x_max , cordinates.second , cordinates.first , cordinates.second);
        QGraphicsLineItem *line2=new QGraphicsLineItem(x_max , cordinates.second , cordinates.first , cordinates.second);
        this->addItem(line2);

       break;
    }

    case 15:                                                      //! draw side line for if-else
    {
        pen.setStyle(Qt::SolidLine);
        qp->setPen(pen);

        QPair<int,int> cordinates;
        cordinates = cord_stack.pop();

        loop_outside++;
        x_max -= 5;
        int t1;

        QStack<int> tempstack;
        while(!ifstack.empty())
        {
            t1 = ifstack.pop() ;
            out<<t1<<endl;
            tempstack.push( t1 + 1 );
        }
        out<<"over" <<endl;
        while(!tempstack.empty())
        {
            t1 = tempstack.pop();
            ifstack.push(t1);
        }


        int t=x_max;

        if(x_max < cordinates.first) t = cordinates.first;

        //! qp->drawLine(cordinates.first , cordinates.second , t + 150, cordinates.second);
        QGraphicsLineItem *line=new QGraphicsLineItem(cordinates.first , cordinates.second , t + 150, cordinates.second);
        this->addItem(line);
        //!  qp->drawLine(t+150 , cordinates.second , t+150 , cordinates.second+20);
        QGraphicsLineItem *line1=new QGraphicsLineItem(t+150 , cordinates.second , t+150 , cordinates.second+20);
        this->addItem(line1);

        if(ifstack.empty() && loop_outside > 0)
        {
            x_max = t+100;
        }
        else if (loop_outside > 0)
            x_max = t + 150;

        QPair<int,int> pair;
        pair.first = xdistance;
        pair.second = ydistance;
        blockendstack.push(pair);
        xdistance = t+150 ;
        ydistance = cordinates.second + 20 ;
        break;
    }

    case 16:                                                     //! join ends after if-else
    {
        pen.setStyle(Qt::SolidLine);
        qp->setPen(pen);
        QPair<int,int> pair = blockendstack.pop();

        if( pair.second > ydistance)
        {
            QGraphicsLineItem *line=new QGraphicsLineItem (xdistance, ydistance , xdistance , pair.second+5 );
            this->addItem(line);
            QGraphicsLineItem *line1=new QGraphicsLineItem(xdistance, pair.second+5 , pair.first , pair.second+5);
            this->addItem(line1);
            QGraphicsLineItem *line2=new QGraphicsLineItem (pair.first , pair.second , pair.first , pair.second+5 );
            this->addItem(line2);
             //! qp->drawLine(xdistance, ydistance , xdistance , pair.second);
             //! qp->drawLine(xdistance, pair.second , pair.first , pair.second);
             ydistance = pair.second+5;
        }
        else if( pair.second < ydistance)
        {
            QGraphicsLineItem *line=new QGraphicsLineItem (pair.first , pair.second , pair.first , ydistance+5);
            this->addItem(line);
            QGraphicsLineItem *line1=new QGraphicsLineItem (pair.first , ydistance+5 , xdistance , ydistance+5 );
            this->addItem(line1);
            QGraphicsLineItem *line2=new QGraphicsLineItem (xdistance , ydistance , xdistance , ydistance+5 );
            this->addItem(line2);

            //! qp->drawLine(pair.first , pair.second , pair.first , ydistance);
            //! qp->drawLine(pair.first , ydistance , xdistance , ydistance );
            ydistance += 5;

        }
        else if (pair.second == ydistance)
        {
            QGraphicsLineItem *line=new QGraphicsLineItem (pair.first , pair.second , xdistance , ydistance);
            this->addItem(line);
            //! qp->drawLine(pair.first , pair.second , xdistance , ydistance);
        }

        xdistance=pair.first;

        //! qp->drawLine(xdistance, ydistance, xdistance , ydistance+10);
        QGraphicsLineItem *line=new QGraphicsLineItem (xdistance , ydistance , xdistance , ydistance+10);
        this->addItem(line);

        ydistance = ydistance+10 ;

        loop_outside--;
         x_max +=  10;

          inloops=0;

 /*       if(loop_outside == 0 && ifstack.isEmpty() && inloops==0)
             x_max = xdistance + 80;
*/
        break;
    }

    case 6:                                                 //! start of if
    {
        if(loop_outside == 0 && ifstack.isEmpty())
                     x_max = xdistance + 80;
        ifstack.push(0);
        out<<"          case : "<<6<<endl;

        break;
    }

    case 7:                                                  //! end of if
    {
        inloops = ifstack.pop();
        out<<"              inloops : "<<inloops<<endl;
        break;
    }

  }


}

