#include "ftpmessage.h"

FtpMessage::FtpMessage(QString fl, QString dir)
{
    mFtpDir = dir;
    mFileName = fl;
   // flProcessed = false;
    mCoordSize =0;
    //Сообщение невалидно, пока не проверили что оно имеет корректную длину
    flValid = false;
}

QString FtpMessage::fileName() const {
    return mFileName;
}
/*
bool FtpMessage::isProcessed() const{
    return flProcessed;
}
*/
bool FtpMessage::getBodyContent() {
    //qDebug()<<"FtpMessage::getBodyContent";
    QString fullFileName = mFtpDir + mFileName;
    QFile file_(fullFileName);
    if ( !file_.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug()<<"OPENED FAILURE!" <<mFileName;

        return false;
    }

    QXmlStreamReader xml(&file_);
    while ( !xml.atEnd() && !xml.hasError() ) {

        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement) {
            
	if (xml.name() == "body") {
                xml.readNext();
                QString bodyStr = xml.text().toString();
                QByteArray myData = QByteArray::fromHex(bodyStr.toLatin1());
                QByteArray message = myData.right( myData.size() );
                //QByteArray message = myData.right(myData.size()-9);
                //const int WORD_SIZE = 4;
                //const int POS_TIME = 7;
                //mBody=message.right(message.size()-16);
                //qDebug()<< "MBODY SIZE1 = " << message.size();
                //qDebug()<< "MBODY HEX" << message.toHex();
                mHat = message.left(MessageStruct::HAT_SIZE);
                //QByteArray name = mHat.left(9);
                //int separator = mHat[8+1];
                //int version = mHat[8+2];
                bool ok;
                QByteArray BtLen = mHat.mid(FtpMessage::Point::POINT_LENGTH_POS, FtpMessage::Point::POINT_LENGTH_SIZE);

                int point_length  = 0;
                point_length = BtLen.toHex().toInt(&ok, 16);
                //qDebug()<<"LENGTH:  "<<point_length;
                setCoordSize(point_length);
                //qDebug()<<"NAME "<<name;
                //qDebug()<<"SEP  "<<separator;
                //qDebug()<<"VER  "<<version;
                //qDebug()<<"LEN  "<<point_length;
                mBody = message.remove(0, MessageStruct::HAT_SIZE);
                //qDebug()<< "MBODY HEX2" << mBody.toHex();
                //qDebug()<< "MBODY SIZE2 = " << mBody.size();
                if (  isValidCoordSize() && mBody.size() && mHat.size() ) {
                    //qDebug()<<"Message is Valid; coord_size: "<<coordSize();
                    flValid = true;
                }
                else {
                    flValid = false;
                   //qDebug()<<"Message not Valid";
                }
                file_.close();
                return true;
            }
        }
    }


    file_.close();
 return true;
}

void FtpMessage::setCoordSize(const int &sz) {

        mCoordSize = sz;
}
bool FtpMessage::isValidCoordSize() const {
	
        return ( coordSize() == Point::ORDINARY || 
	     coordSize() == Point::COURSE || 
	     coordSize() == Point::EXTEND       ) ? true : false;


}
int FtpMessage::coordSize() const {
    return mCoordSize;
}

void FtpMessage::setValid(bool st) {
    flValid = st;
}
