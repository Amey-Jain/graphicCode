#include "MainWindow.h"
#include <QSize>
#include <QString>
#include <QTextStream>
#include <QDesktopWidget>
#include <QApplication>
#include <QFileDialog>
#include <QtCore>
#include <QtWidgets>//#include <QtGui>
#include <QFile>
#include <QProcess>
#include <cstdlib>
#include <cstdio>
#include <cstring>
MainWindow ::MainWindow()
{
  const int width = QApplication::desktop()->width();
  const int height = QApplication::desktop()->height();

  QFont font;
  font.setPointSize(9);

   menubar = new QMenuBar(this);
   menubar->setObjectName(QString::fromUtf8("menubar"));
   menubar->setGeometry(QRect(0, 0,width, 21));

   menuFile = new QMenu(menubar);
   menuFile->setObjectName(QString::fromUtf8("menuFile"));
   menuFile->setFont(font);

   menuAbout = new QMenu(menubar);
   menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
   menuAbout->setFont(font);

   actionOpen_File = new QAction(this);
   actionOpen_File->setObjectName(QString::fromUtf8("actionOpen_File"));
   actionOpen_File->setFont(font);
   //connect(actionOpen_File, SIGNAL(triggered()), this, SLOT(open()));
   menuFile->addAction(actionOpen_File);

   actionExit = new QAction(this);
   actionExit->setObjectName(QString::fromUtf8("actionExit"));
   actionExit->setFont(font);


   menuFile->addAction(actionExit);

   actionAbout_Graphic_code = new QAction(this);
   actionAbout_Graphic_code->setObjectName(QString::fromUtf8("actionAbout_Graphic_code"));
   actionAbout_Graphic_code->setFont(font);
   menuAbout->addAction(actionAbout_Graphic_code);


   this->setMenuBar(menubar);
   statusbar = new QStatusBar(this);
   statusbar->setObjectName(QString::fromUtf8("statusbar"));
   this->setStatusBar(statusbar);

   menubar->addAction(menuFile->menuAction());
   menubar->addAction(menuAbout->menuAction());

   this->setFont(font);
   this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
   menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
   menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0));

   actionOpen_File->setText(QApplication::translate("MainWindow", "Open File", 0));
   actionOpen_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));

   actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
   actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));

   actionAbout_Graphic_code->setText(QApplication::translate("MainWindow", "About Graphic_code", 0));
   actionAbout_Graphic_code->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0));


  connect(actionOpen_File, SIGNAL(triggered()),this, SLOT(open()));
  connect(actionAbout_Graphic_code, SIGNAL(triggered()), this, SLOT(about()));
  connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

    this->setWindowTitle(QString::fromUtf8("Graphic_Code"));

    centreWidget = new QWidget(this);//! the window created is the central widget
    centreWidget->setGeometry(0,21,width,height-21);
    tabgroup1=new TabWidget1();
    tabgroup1->setParent(centreWidget);//! make a function setParent for this
}


void MainWindow::open()
{
     QFile files("in.txt");
     files.open(QIODevice::WriteOnly | QIODevice::Text);

     system("c++ ../GraphicCode/graphicCode.cpp");

         QString name , file = "./a.out < in.txt";
         name= QFileDialog::getOpenFileName(this);
         QTextStream out(&files);
         out<<name<<endl;
         out<<"-1"<<endl;

         system(file.toStdString().c_str());

         files.close();
         QString fileName4  = name;
         QFile data3(fileName4);


    QString fileName1 ="instructions.txt";
    QFile data(fileName1);
    QString fileName2 = "filerange.txt";
    QFile data1(fileName2);
   QString fileName3 ="functionsrange.txt";
   QFile data2(fileName3);
   QString fileName5 ="classrange.txt";
   QFile data4(fileName5);


    QString line;
    QVector<QString> instructions1,filerange1,arbit;
    QVector<QVector<QString> > functionrange1;
    functionrange1.push_back(arbit);
    if (data.open(QFile::ReadOnly)) {
    QTextStream in(&data);

      do {
        line = in.readLine();
        instructions1.push_back(line);
      } while (!line.isNull());
      instructions1.pop_back();
     }

      if (data1.open(QFile::ReadOnly)) {
        QTextStream in(&data1);

        do {
          line = in.readLine();
          filerange1.push_back(line);
          functionrange1[0].push_back(line);
        } while (!line.isNull());
        filerange1.pop_back();
      }

       if (data2.open(QFile::ReadOnly)) {
          QTextStream in(&data2);

          do {
            line = in.readLine();
            functionrange1[0].push_back(line);
          } while (!line.isNull());
          functionrange1[0].pop_back();
      }

       if (data3.open(QFile::ReadOnly)) {
          QTextStream in(&data3);

          do {
            line = in.readLine();
            functionrange1[0].push_back(line);
          } while (!line.isNull());
          functionrange1[0].pop_back();
      }
       if (data4.open(QFile::ReadOnly)) {
          QTextStream in(&data3);

          do {
            line = in.readLine();
            functionrange1[0].push_back(line);
          } while (!line.isNull());
          functionrange1[0].pop_back();
      }
    instructions=instructions1;
    filerange=filerange1;
    functionrange=functionrange1;
    int lastfile=0,lastfunc=0;
    int a=0,l;
    int startnum,endnum,fstartnum,fendnum;
    QTextStream sout(stdout);

    for(int i=0;i<filerange.size();i++)
    {
        QString singleFile=filerange.at(i);

        QString str,filename,start,end;
        startnum=0;endnum=0;fstartnum=0;fendnum=0;

        a=0;
        for(int j=0;j<singleFile.length();j++)
        {
            if(singleFile.at(j)==':')
            {
                if(a==0)
                {
                    filename=str;
                    str.clear();
                    a++;
                }
                else if(a==1)
                {
                    start=str;
                    str.clear();
                    a++;
                }
                else
                    end=str;
            }
            else
                str.append(singleFile.at(j));
        }

        for(l=0;l<start.length();l++)
        {
             startnum=startnum*10+(start[l].toLatin1()-48);
        }

        for(l=0;l<end.length();l++)
        {
             endnum=endnum*10+(end[l].toLatin1()-48);
        }
        sout<<"endnum**"<<endnum<<endl;



        filewidget.push_back(new Widget1(filename));
        (filewidget.back())->setParent(tabgroup1);

        tabgroup2.push_back(new TabWidget2(filename));
        (tabgroup2.back())->setParent(filewidget.back());

        functionwidget.push_back(new QVector<Widget2*>);

        for(int j=0;j<functionrange[i].size();j++)
        {
            QString singleFunction=functionrange[i].at(j);
            QString str1,funcname,fstart,fend;
            a=0;
            str1.clear();

            for(int k=0;k<singleFunction.length();k++)
            {
                if(singleFunction.at(k)==':')
                {
                    if(a==0)
                    {
                        funcname=str1;
                        str1.clear();//! just to ensure that str becomes empty
                        a++;
                    }
                    else if(a==1)
                    {
                        fstart=str1;
                        str1.clear();
                        a++;
                    }
                    else
                        fend=str1;
                }
                else
                    str1.append(singleFunction.at(k));
            }

            fstartnum=0;fendnum=0;
            for(l=0;l<fstart.length();l++)
            {
                 fstartnum=fstartnum*10+(fstart[l].toLatin1()-48);
            }

            for(l=0;l<fend.length();l++)
            {
                 fendnum=fendnum*10+(fend[l].toLatin1()-48);
            }

            sout<<"fendnum**"<<fendnum<<endl;
           (*functionwidget.back()).push_back(new Widget2(funcname,fileName4));
           ((*functionwidget.back()).back())->setParent(tabgroup2.back());

            for(int k=fstartnum;k<=fendnum;k++)
            {
                ((((*functionwidget.back()).back())->scene)->instruction).push_back(instructions[k]);
            }
            QPainter qp;
            (((*functionwidget.back()).back())->scene)->drawForeground(&qp,(((*functionwidget.back()).back())->scene)->sceneRect());
             (tabgroup2.back())->addTab(((*functionwidget.back()).back()),funcname);
            lastfunc=fendnum;


            if (data3.open(QFile::ReadOnly)) {
            QTextStream in(&data3);
                    line = in.readAll();
                }


            sout<<line<<endl;
            QApplication::setOverrideCursor(Qt::WaitCursor);
            QGraphicsTextItem *txt1=new QGraphicsTextItem(line);
            txt1->setPos(0,0);
            QApplication::restoreOverrideCursor();

            (((*functionwidget.back()).back())->scene1)->addItem(txt1);

        }
        lastfunc=0;
        tabgroup1->addTab(filewidget.back(),filename);
        lastfile=endnum;
    }
    instructions.empty();
    filerange.empty();
    functionrange.empty();
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Graphic_code"),
            tr("This <b>Graphic_Code</b> application is used to generate flowchart of compiled c++ programs."
               "To use it open file using Ctrl+O and the flowchart is generated."));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        event->accept();
}
