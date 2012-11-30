#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <TabWidget1.h>
#include <TabWidget2.h>
#include <Widget1.h>
#include <Widget2.h>
#include <QtGui>
#include <QtCore>
#include <QApplication>
#include <QGraphicsItem>

class MainWindow : public QMainWindow
{
     Q_OBJECT

public:
    MainWindow();
    QVector<QString> instructions;
    QVector<QString> filerange;
    QVector<QVector<QString> > functionrange;
private:
    QWidget *centreWidget;
    TabWidget1* tabgroup1;
    QVector<Widget1*> filewidget;//! in constructor i make these and store which is once in a while task
    QVector<TabWidget2*> tabgroup2;
    QVector< QVector<Widget2*>* > functionwidget;//! size no of files widgets
   //!!!!!!!!

    QMenuBar *menubar;
    QStatusBar *statusbar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QAction *actionOpen_File;
    QAction *actionExit;
    QAction *actionAbout_Graphic_code;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void about();

};

#endif // MAINWINDOW_H
