#ifndef MYSERVER_H
#define MYSERVER_H
//#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QString>
class MyServer : public QObject
{
    Q_OBJECT
public:
     MyServer(QObject *parent = 0); // конструктор
signals:
    void data_received(QString);
public slots:
    void incommingConnection(); // обработчик входящего подключения
    void readyRead(); // обработчик входящих данных
    void stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего сокета (он нам важен, дабы у нас всегда был кто-то, кто будет вещать
private:
    QTcpServer *server; // указатель на сервер
    QList<QTcpSocket *> sockets; // получатели данных
    QTcpSocket *firstSocket; // вещатель
};
#endif // MYSERVER_H
