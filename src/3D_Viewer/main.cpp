#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
  QCoreApplication::setApplicationName(APPLICATION_NAME);

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
