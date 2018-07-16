#include "ping.h"

Ping::Ping(
           QString host, QString dbname, QString login, QString password, QObject *parent) :
           mHost(host), mDbname(dbname), mLogin(login), mPassword(password), QThread(parent)
{
    moveToThread(this);



}
void Ping::run(){
    db2 =  QSqlDatabase::addDatabase("QMYSQL", "thread_ping");
    db2.setHostName(mHost);
    db2.setDatabaseName(mDbname);
    db2.setUserName(mLogin);
    db2.setPassword(mPassword);
    db2.setConnectOptions("MYSQL_OPT_RECONNECT=1");
    const int cPingTimeout = 60;
    while (true) {
        sleep(cPingTimeout);
        db2.open();
        if ( db2.isOpen() ) {
            QSqlQuery fq(db2);
            QString qr= QString("UPDATE services SET updated_at=NOW() WHERE id=1");
            //qDebug()<<"PING BEFORE FAIL DB2:"<<db2;
            if( fq.exec(qr) ) {
                //qDebug()<<"UPDATED OK!";
            }
            else {
                qDebug()<<"UPDATED FAILED";
            }
        }
        else{
            qDebug()<<"PING:: DB IS NOT OPEN";
        }
        db2.close();
    }
}


