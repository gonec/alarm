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
    //qDebug()<<"MEMORY";


    QFile file_(fullFileName);
    //qDebug()<<"AFTER: "<<fullFileName;
   // if(file_.exists()){
        //qDebug()<<"EXISTS";
   // }
   // else {
       // qDebug()<<"NOT EXISTS";
  //  }
    if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"OPENED FAILURE!";
        //delete file_;
        return false;
    }
    else
    {
     //   qDebug()<<"OPENED Ok!";

    }
   // qDebug()<<"SUSPECIOUS";
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
                QByteArray message = myData.right(myData.size());
                //QByteArray message = myData.right(myData.size()-9);
                //const int WORD_SIZE = 4;
                //const int POS_TIME = 7;
                //mBody=message.right(message.size()-16);
                //qDebug()<< "MBODY SIZE1 = " << message.size();
                //qDebug()<< "MBODY HEX" << message.toHex();
                mHat = message.left(16);
                //QByteArray name = mHat.left(9);
                //int separator = mHat[8+1];
                //int version = mHat[8+2];

                bool ok;
                QByteArray BtLen = mHat.mid(11,1);

                int point_length  = 0;
                point_length = BtLen.toHex().toInt(&ok, 16);
                //qDebug()<<"LENGTH:  "<<point_length;
                setCoordSize(point_length);
                //qDebug()<<"NAME "<<name;
                //qDebug()<<"SEP  "<<separator;
                //qDebug()<<"VER  "<<version;
                //qDebug()<<"LEN  "<<point_length;
                mBody = message.remove(0, 16);
                //qDebug()<< "MBODY HEX2" << mBody.toHex();
                //qDebug()<< "MBODY SIZE2 = " << mBody.size();
                if (  coordSize() && mBody.size() && mHat.size() ) {
                    qDebug()<<"Message is Valid;";
                    flValid = true;
                }
                else{
                    qDebug()<<"Message not Valid";
                }

                file_.close();
                //delete file_;
                 //qDebug()<<"FILE DELETE: ";
                return true;
            }
        }
    }


    file_.close();
    //delete file_;
return true;
}

bool FtpMessage::setCoordSize(int sz) {

    if( sz == 16 || sz == 20){
        mCoordSize = sz;
        return true;
    }
    return false;
}
int FtpMessage::coordSize() const {
    return mCoordSize;
}

void FtpMessage::setValid(bool st) {
    flValid = st;
}
