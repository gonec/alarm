#include "myserver.h"
MyServer::MyServer(QObject *parent) :
    QObject(parent),
    firstSocket(NULL)
{
    server = new QTcpServer(this);
    qDebug() << "server listen = " << server->listen(QHostAddress::Any, 6666);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection())); // подключаем сигнал "новое подключение" к нашему обработчику подключений
    qDebug()<<"STARTIN SERVER...";
}
void MyServer::incommingConnection() // обработчик подключений
{
    QTcpSocket * socket = server->nextPendingConnection(); // получаем сокет нового входящего подключения
    QObject::connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState))); // делаем обработчик изменения статуса сокета
    if (!firstSocket) { // если у нас нет "вещающего", то данное подключение становится вещающим
        QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead())); // подключаем входящие сообщения от вещающего на наш обработчик
        socket->write("server"); // говорим ему что он "вещает"
        firstSocket = socket; // сохраняем себе"
        qDebug() << "this one is server";
    }
    else { // иначе говорим подключенному что он "получатель"
        socket->write("client");
        sockets << socket;
    }
}
void MyServer::readyRead() // обработчик входящих сообщений от "вещающего"
{
    QObject * object = QObject::sender(); // далее и ниже до цикла идет преобразования "отправителя сигнала" в сокет, дабы извлечь данные
    if (!object)
        return;
    qDebug() << "[1]";
    QTcpSocket * socket = static_cast<QTcpSocket *>(object);
    QByteArray arr =  socket->readAll();
    QString data = arr;
    emit data_received(data);
    // на самом деле весь верхний код можно было заменить на firstSocket, но я выдирал код из другого проекта, и переписывать мне лень :)
    foreach(QTcpSocket *socket, sockets) { // пишем входящие данные от "вещающего" получателям
        if (socket->state() == QTcpSocket::ConnectedState)
            socket->write(arr);
    }
}
void MyServer::stateChanged(QAbstractSocket::SocketState state) // обработчик статуса, нужен для контроля за "вещающим"
{
    QObject * object = QObject::sender();
    if (!object)
        return;
    QTcpSocket * socket = static_cast<QTcpSocket *>(object);
    qDebug() << state;
    if (socket == firstSocket && state == QAbstractSocket::UnconnectedState)
        firstSocket = NULL;
}
