#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("gonets");
    QCoreApplication::setOrganizationDomain("gonets.ru");
    QCoreApplication::setApplicationName("alarm");
    MainWindow w;
    w.show();

    return a.exec();
}
