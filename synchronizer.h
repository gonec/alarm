#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>
#include <QByteArray>
#include "message.h"
#include "messagesgenerator.h"

class Synchronizer : public QThread
{
    Q_OBJECT
public:
     Synchronizer(QString db_host,
                  QString db_name,
                  QString db_login,
                  QString db_password,
                  QObject *parent = 0);

     bool saveCoord(QString id, DataRecord rec );
     bool saveMessageToDb(Message &message);
     MessagesGenerator *mMsgGenerator;
     bool isSavedToDB(QString fileName) const;
     QSqlDatabase db;
signals:
     void show_MessagesStatistics(int, int);
     void remove_ftp_file(QString);
     void queue_progress_info(int listSize, int saved_counter);
     void show_progressDB(int, int);
public slots:
     void slotProcessMessages();
     void income_message(QString s, QByteArray b, int point_size);
     void run();
     void remove(QString fl);
private:
     QString mDbHost;
     QString mDbName;
     QString mDbLogin;
     QString mDbPassword;
};

#endif // SYNCHRONIZER_H

