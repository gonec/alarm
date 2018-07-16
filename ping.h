#ifndef PING_H
#define PING_H

#include <QObject>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>
class Ping : public QThread
{
    Q_OBJECT
public:
    Ping(QString host,
         QString dbname,
         QString login,
         QString password,
         QObject *parent = 0);

public slots:
      void run();
private:
    QSqlDatabase db2;
    QString mHost;
    QString mDbname;
    QString mLogin;
    QString mPassword;
};

#endif // PING_H
