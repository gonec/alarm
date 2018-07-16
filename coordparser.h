#ifndef COORDPARSER_H
#define COORDPARSER_H

#include <QObject>
#include <QDebug>
#include "message.h"
#include "course.h"

class CoordParser : public QObject
{
    Q_OBJECT
public:
    explicit CoordParser(QObject *parent = 0);
    ~CoordParser();

    Message parse( QByteArray coords, int coord_size);

    const int DATA_RECORD_SIZE = 20;

    QString getFormatTime(TimeStruct time);

private:
    QString mRecords;

};

#endif // COORDPARSER_H
