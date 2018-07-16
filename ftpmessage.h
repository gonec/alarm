#ifndef FTPMESSAGE_H
#define FTPMESSAGE_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include "message.h"

class FtpMessage
{

public:
    FtpMessage(QString fl, QString dir);
    QString fileName() const;
    bool isProcessed() const;
    QByteArray mBody;
    QByteArray mHat;
    bool getBodyContent();
    void getFtpDir() const ;
    void deleteFtpFile(QString fl);
    int coordSize() const;
    //Установим длину записи
    bool setCoordSize(int );
signals:
    void new_message();

private:
    QString mFtpDir;
    bool flFlarm;
    //корректное ли сообщение!
    void setValid(bool st);
    //Обработанное файловое сообщение
    bool flSeen;
    //Флаг целостности сообщения
    bool flValid;
    //bool flProcessed;
    QString mFileName;
    int mCoordSize;
};

#endif // FTPMESSAGE_H
