
#include "synchronizer.h"
Synchronizer::Synchronizer( QString db_host,
                            QString db_name,
                            QString db_login,
                            QString db_password,
                            QObject *parent) :
    QThread(parent),
    mDbHost(db_host),
    mDbName(db_name),
    mDbLogin(db_login),
    mDbPassword(db_password)
{
    qDebug()<<"DB HOST:     "<<mDbHost;
    qDebug()<<"DB NAME:     "<<mDbName;
    qDebug()<<"DB LOGIN:    "<<mDbLogin;
    qDebug()<<"DB PASSWORD: "<<mDbPassword;

    moveToThread(this);


}
void Synchronizer::run() {
    qDebug()<<"SYNCHRONIZER RUN: "<<currentThreadId();

    db =  QSqlDatabase::addDatabase("QMYSQL", "thread_synchro");
    db.setHostName(mDbHost);
    db.setDatabaseName(mDbName);
    db.setUserName(mDbLogin);
    db.setPassword(mDbPassword);

    QSqlQuery encod(db);
    db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
    bool ok = db.open();
    if (!ok) {
        qDebug()<<"SYNCHRO: "<<db.lastError();
    }
    else{
        qDebug()<<"SYNCHRO "<<"DB IS OPEN!";
        if ( !encod.exec("SET NAMES \'utf8\';") ) {
            qDebug()<<"encoding err";
        }
        encod.exec("SET CHARSET SET \'utf8\';");
    }
    mMsgGenerator = new MessagesGenerator();
    QTimer timer;
    connect(&timer, SIGNAL( timeout() ), SLOT( slotProcessMessages() ) );
    timer.start(10000);
    exec();
}

void  Synchronizer::slotProcessMessages () {
    QList<Message>::iterator it;
    int listSize = mMsgGenerator->mMessagesList.size();
    int counter = 0;
    int saved_counter = 0;
    if (!listSize) {
        //установим 100 из 100
        emit queue_progress_info(0,0);
    }
    for(it = mMsgGenerator->mMessagesList.begin(); it != mMsgGenerator->mMessagesList.end(); ++it) {
        counter++;
        emit queue_progress_info(listSize, counter);
        //emit show_progressDB(listSize, counter);
        //если еще не сохранили в БД, то

        if ( !isSavedToDB( (*it).fileName() ) ) {
        //if ( !(*it).isSavedToDB() ) {
            //сохраняем
            if ( saveMessageToDb(*it) ) {
                   //если успешно обработали, можем удалять
                  // qDebug()<<"SAVED TO DB OK!";
                   //ставим метку, что сохранен
                   (*it).setSavedToDB();
                    emit remove_ftp_file( (*it).fileName() );
                    saved_counter++;
            }
            else{
                (*it).showAllInfo();
                qDebug()<<"COMPLETE: SAVING TO DB ERROR!!!";
            }
        }
        else {
              //удаляем если обработали ранее
              emit remove_ftp_file( (*it).fileName() );
              saved_counter++;

        }

    }




}
bool Synchronizer::isSavedToDB(QString filename) const {


    QSqlQuery query(db);
    QString query_string = QString("SELECT * FROM ftp_files "
                                            "WHERE name=\'%1\'").arg(filename);
    if( query.exec(query_string) ) {
        if( query.first() ) {
            int proc = query.value(2).toInt();
            //qDebug()<<" PROCESSED RESULT: "<< proc;
            if (proc == 0) {
                //qDebug()<<" SAVE WITH ERROR, BUT SAVED ";
                return false;
            }
            return true;
        }
        else {
            return false;
        }
    }
    else{
        qDebug()<<"MYSQL EROR SELECTIN ftp_files"<<query.lastError();
    }

    return false;
}

bool Synchronizer::saveMessageToDb(Message &message){

   // qDebug()<<"============== START    ================";
   // qDebug()<<"SAVING MESSAGE TO DB....";
    QSqlQuery fq(db);
    QString qr= QString("INSERT INTO ftp_files (name, processed) VALUES (\'%1\', 0)").arg(message.mFileName);
    QString id;
    QString ftp_file_id;
    if( fq.exec(qr) ) {
        id = fq.lastInsertId().toString();
        ftp_file_id = id;
        //qDebug()<<"INSERT INTO FTP_FILES OK";
    }
    else{
        qDebug()<<"saveMessageToDb ERROR INSERTED INTO FILE";
        qDebug() << fq.lastError();
        qDebug()<<"============ END ======================";
        return false;
    }


    QSqlQuery query(db);
    query.prepare("INSERT INTO messages (received, terminal, id_2, file_id, course, coords_count, alarm_code) "
                      "VALUES (:received,"
                      " :terminal,"
                      " :id_2,"
                      " :file_id,"
                      " :course,"
                      " :coords_count,"
                      " :alarm_code);"
                  );

   QDateTime rcv_time = message.date();
   QString strTime = rcv_time.toString("yyyy-MM-dd hh:mm:ss");
   query.bindValue(":received", strTime);
   QString terminal = message.terminal();
   query.bindValue(":terminal", terminal);
   query.bindValue(":id_2", message.mIdStrange);
   query.bindValue(":file_id", id);
   int course = ( message.flCourseExists ) ? 1 : 0;
   query.bindValue(":course", course );
   query.bindValue(":coords_count", message.recordsCount() );
   if(message.getDEFCON()  == DEFCON_1){
        query.bindValue(":alarm_code", 1);
   }
   else
   {
        query.bindValue(":alarm_code", 0);
   }
   if ( !query.exec() ){
       qDebug()<<"ERROR INSERT INTO MESSAGES: ERROR error is: "<<query.lastError();
       qDebug()<<"MESSAGE DATE: "<<message.date().toString();
       qDebug()<<"============ END ======================";

       return false;
   }
   else {
       qDebug()<<"INSERTED INTO MESSAGES OK";
       QVariant id = query.lastInsertId();
       QString strId = id.toString();
       QList<DataRecord>::iterator it;
       for(it = message.mRecords.begin(); it != message.mRecords.end(); ++it) {
           saveCoord( strId, (*it) );
       }
   }
   //

   qr = QString("UPDATE ftp_files SET processed = 1  WHERE id=%1").arg(ftp_file_id);
   if( fq.exec(qr) ) {
      // qDebug()<<"UPDATING ftp_files OK";
      // qDebug()<<"============ END ======================";
       return true;
   }
   else{
        qDebug()<<"UPDATING FILES ERROR. error is "<<fq.lastError();
        qDebug()<<"============ END ======================";
   }
    return false;

}
bool Synchronizer::saveCoord(QString id, DataRecord rec ){
    QSqlQuery query(db);

    if( rec.isCourse()  ){
        //qDebug()<<"SAVING WITH COURSE";
        query.prepare("INSERT INTO coords (received,  D1, D2, D3, AL, IG, EC, speed, temperature, course, lat_s, lon_s, message_id) "
                      "VALUES (:received, :D1, :D2, :D3, :AL, :IG, :EC, :speed, :temperature, :course, :lat_s, :lon_s, :message_id);"
                      );
        QString coordDateTime = rec.datetime().toString("yyyy-MM-dd hh:mm:ss");
        //qDebug()<<"REC LAT: "<<rec.lat();
        query.bindValue( ":received", coordDateTime );
        query.bindValue( ":D1", rec.D1() );
        query.bindValue( ":D2", rec.D2() );
        query.bindValue( ":D3", rec.D3() );
        query.bindValue( ":AL", rec.AL() );
        query.bindValue( ":IG", rec.IG() );
        query.bindValue( ":EC", rec.EC() );
        query.bindValue( ":speed", rec.speed() );
        query.bindValue( ":temperature", rec.temperature());
        query.bindValue( ":course", rec.course() );
        query.bindValue(":lat_s", QString("'") +rec.lat() + QString("'") );
        query.bindValue(":lon_s", QString("'") + rec.lon()+  QString("'") );
        query.bindValue(":message_id", id);
   }
   else {
        query.prepare("INSERT INTO coords (received,  D1, D2, D3, AL, IG, EC, lat_s, lon_s, message_id) "
                      "VALUES (:received, :D1, :D2, :D3, :AL, :IG, :EC, :lat_s, :lon_s, :message_id);"
                      );
        QString coordDateTime = rec.datetime().toString("yyyy-MM-dd hh:mm:ss");
        //qDebug()<<"REC LAT: "<<rec.lat();
        query.bindValue(":received", coordDateTime );
        query.bindValue(":D1", rec.D1() );
        query.bindValue(":D2", rec.D2() );
        query.bindValue(":D3", rec.D3());
        query.bindValue(":AL", rec.AL());
        query.bindValue(":IG", rec.IG());
        query.bindValue(":EC", rec.EC());
        query.bindValue(":lat_s", QString("'") +rec.lat() + QString("'") );
        query.bindValue(":lon_s", QString("'") + rec.lon()+  QString("'") );
        query.bindValue(":message_id", id);
    }
   if( !query.exec() ){
        qDebug()<<"INSERTED INTO COORDS ERROR reason: "<<query.lastError();
        return false;
    }



    return true;
}

void  Synchronizer::income_message(QString s, QByteArray b, int point_size){
    mMsgGenerator->income_message(s, b, point_size);
}

void Synchronizer::remove(QString fl) {
    qDebug()<<"Synchronizer::remove...";
    QList<Message>::iterator it;
    int listSize = mMsgGenerator->mMessagesList.size();

    for(it = mMsgGenerator->mMessagesList.begin(); it != mMsgGenerator->mMessagesList.end(); ++it) {
      if ( (*it).fileName()  == fl ) {
          mMsgGenerator->mMessagesList.erase(it);
          return;
      }
    }
}
