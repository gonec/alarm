#ifndef MESSAGESCONTROLLER_H
#define MESSAGESCONTROLLER_H
#include "filesmonitor.h"
#include "message.h"
#include "coordparser.h"
#include <QDebug>
class MessagesGenerator : public QObject
{
Q_OBJECT
public:
    MessagesGenerator(QObject *parent = 0);
    void Monitor();
    bool isNewFile(QString fl);
    bool addMessage(Message msg);
    QList<Message> mMessagesList;
public slots:
    void income_message(QString flName, QByteArray body, int point_size);

};

#endif // MESSAGESCONTROLLER_H
