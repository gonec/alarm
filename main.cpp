#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QLockFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("gonets");
    QCoreApplication::setOrganizationDomain("gonets.ru");
    QCoreApplication::setApplicationName("alarm");

    QCommandLineParser parser;
    QCommandLineOption iniFile(QStringList() << "f" << "ini-file",
               QCoreApplication::translate("main", "Copy all source files into <directory>."),
               QCoreApplication::translate("main", "directory"));
    parser.addOption(iniFile);
    parser.process(a);
    bool ini = parser.isSet(iniFile);
    QString iniFileName ="/home/user/alarm.ini";
    if ( ini ) {
        iniFileName = parser.value( iniFile);
        qDebug()<<"INI IS SET "<<iniFileName;
    }
    else {
        qDebug()<<"INI NOT SET";
    }
    QLockFile lockFile("alarm.lock");
    if ( !lockFile.tryLock() ) {
        qDebug()<<"ALREADY RUNNING EXIT!";
        return 0;
    }
    else {
       qDebug()<<"TRY LOCK OK!";
    }
    MainWindow w(iniFileName);
    w.show();
    return a.exec();
}
