#include "messagesgenerator.h"

MessagesGenerator::MessagesGenerator(QObject *parent) : QObject(parent)
{

}
void MessagesGenerator::income_message(QString flname, QByteArray body, int point_size){

    //qDebug()<<"income message: "<<flname<<body.toHex();
    CoordParser parser;
   // qDebug()<<"BEFORE MESSAGE CREATE";
    Message msg = parser.parse(body, point_size);

    //  qDebug()<<"AFTER PARSE MESSAGE:";
    msg.mFileName = flname;
    //если битое сообщение
    if (!msg.isValid())
        return;

    if( msg.makeHeader(flname) ) {
       // qDebug()<<"HEADER OK!";
    }
    else {

        qDebug()<<"MAKE HEADER ERROR! ";
        return ;
    }
    addMessage(msg);

}

bool MessagesGenerator::addMessage(Message msg_) {
    mMessagesList.append(msg_);
    return true;
}

bool MessagesGenerator::isNewFile(QString fl){
    return true;
}
