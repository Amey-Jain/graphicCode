#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QVector>
#include <MainWindow.h>
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow window;
  window.showMaximized();

  return app.exec();
}
