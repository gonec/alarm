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
    void setCoordSize(const int &);
signals:
    void new_message();

private: 
    bool isValidCoordSize() const;
    struct Point { 
	    static const int ORDINARY = 16;
	    static const int COURSE   = 20;
	    static const int EXTEND   = 32;    
	    static const int POINT_LENGTH_POS = 11; 
	    static const int POINT_LENGTH_SIZE = 1; 
    };

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
    struct MessageStruct { 
    	static const int HAT_SIZE = 16;
    };
};

#endif // FTPMESSAGE_H
