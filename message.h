#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <QDateTime>
#include <QChar>
#include "datarecord.h"
#include "timestruct.h"
#include "latlong.h"
#include "sensors.h"
#include "coords.h"
#include <iostream>

enum DEFCON_LEVEL {
     DEFCON_1 = 1,
     DEFCON_2 = 2,
     DEFCON_3 = 3,
     DEFCON_4 = 4,
     DEFCON_5 = 5
};

//Очень плохой класс, надо переписать
class Message {

public:
      Message();
      bool isSavedToDB() const;
      void addDataRecord(DataRecord );
      bool makeHeader(QString fl);
      QString mFileName;
      QString text();
      bool flValid;
      bool flSeen;
      bool flProceed;
      QString mAtNum;
      QDateTime mIncomeDate;
      QString mIdStrange;
      bool isAlarm();
      bool isIgnition();
      bool isJailbreaking();
      DEFCON_LEVEL getDEFCON();
      bool isValid();
      QList<DataRecord> mRecords;
      void showAllInfo() ;
      QString getShortInfo();
      int recordsCount() const;
      //struct geo;
      QString getInfo();
      QString td(QString );
      QString tr(QString val);
      bool flAlarm;
      bool flIgnition;
      bool flJailBreaking;
      void calculateDefCon();
      bool wasSeen() const;
      int countNewMessages();
      QString a(int num, QString name);
      QString b(int num);
      QString td_row(int number, int start);
      void setPointSize(int);
      int pointSize() const;
      bool flCourseExists;

      QDateTime date() const;
      void setSavedToDB();
      QString terminal() const ;

      QString id2() const ;
      QString fileName() const;
      bool is_extend() const;
      bool flExtend;
private:
        bool flSavedToDB;
        int mPointSize;
};
#endif // MESSAGE_H
