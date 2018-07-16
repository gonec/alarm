#include "messagesgenerator.h"

MessagesGenerator::MessagesGenerator(QObject *parent) : QObject(parent)
{

}
void MessagesGenerator::income_message(QString flname, QByteArray body, int point_size){
    //qDebug()<<"income message: "<<flname<<body.toHex();
    CoordParser parser;
    Message msg = parser.parse(body, point_size);

    msg.mFileName = flname;
    //если битое сообщение
    if (!msg.isValid())
        return;
    msg.makeHeader(flname);
    addMessage(msg);
}

bool MessagesGenerator::addMessage(Message msg_) {
    mMessagesList.append(msg_);

    return true;
}

bool MessagesGenerator::isNewFile(QString fl){
    return true;
}
