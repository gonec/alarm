#include "message.h"

Message::Message(){
    flSeen = false;
    flAlarm    = false;
    flIgnition = false;
    flJailBreaking = false;
    flProceed = false;
    flSavedToDB = false;
    flCourseExists = false;
}
bool Message::wasSeen() const {
    return flSeen;
}
bool Message::isValid() {
    return flValid;
}
QString Message::text() {
    // секунды
    //qDebug()<<"Seconds: "<<mTime.seconds;
    // минуты
    //qDebug()<<"Minutes: "<<mTime.minuts;
    // часы
    //qDebug()<<"Hours:   "<<mTime.hours;
    // дни
    //qDebug()<<"Days:     "<<mTime.day;
    // месяцы
    //qDebug()<<"Month:     "<<mTime.month ;
    // год
   //qDebug()<<"Year:       "<<mTime.year;
    //qDebug()<<"D1: "<<mSensors.D1<<"  D2: "<<mSensors.D2<<"  D3: "<<mSensors.D3<<"  AL: "<<
              //  mSensors.AL<<"  IG: "<<mSensors.IG;
      QString t;
      return t;
}

void Message::makeHeader(QString fl) {
    //TODO сделать проверку расширения и обработку ошибок
    /*
    QString extension = ".msg";
    int point = fl.indexOf(".msg");
    */
    QString str = fl.left( fl.size() - 4);
    QStringList strParts = str.split('_');
    QString dateStr = strParts[6];

    mIncomeDate = QDateTime::fromString(dateStr, "yyyyMMddhhmmss");

    mIdStrange = strParts[5];
    mAtNum = strParts[1];
}

bool Message::isAlarm(){
    return flAlarm;
}

bool Message::isIgnition(){
    return flIgnition;
}

bool Message::isJailbreaking(){
    return flJailBreaking;
}

void Message::calculateDefCon() {

     QList<DataRecord>::iterator i;
     for(i = mRecords.begin(); i != mRecords.end(); ++i) {
        if ( (*i).isCourse() )
            flCourseExists = true;
        if ( (*i).mSensors.AL == 1 )
            flAlarm        = true;
        if ( (*i).mSensors.IG == 0 )
            flIgnition     = true;
        if ( (*i).mSensors.D3 == 1 )
            flJailBreaking = true;
     }
}

DEFCON_LEVEL Message::getDEFCON() {
    if( flAlarm || flIgnition || flJailBreaking ){

        return DEFCON_1;
    }
    //Тревоги нет

    //if ( mSensors.AL == 0 && mSensors.D1 == 0 && mSensors.IG ==1) {
      //  return DEFCON_5;
    //}
    //if (mSensors.AL == 1 || mSensors.D1 == 1 || mSensors.IG == 0){
      //  return DEFCON_2;
    //}
    /*if( mSensors.AL == 0 && mSensors.D1 == 0 && mSensors.IG == 1){
        return DEFCON_4;
    }

    //Тревога есть
    if (mSensors.AL == 1 && mSensords.D1 == 0 && mSensors.IG == 0){
        return DEFCON_2;
    }
    if (mSensors.AL == 1 && mSensords.D1 == 0 && mSensors.IG == 1){

    }
    */
    return DEFCON_5;
}
void Message::showAllInfo(){
    //qDebug()<<"=== SUBMESSAGE ====";
    QList<DataRecord>::iterator i;

    for(i = mRecords.begin(); i != mRecords.end(); ++i) {
       // qDebug()<<"----------------------";
        (*i).mTimeStruct.show();

        //qDebug()<<(*i).mSensors.IG<<(*i).mSensors.AL<<(*i).mSensord.D1;
       // (*i).mCoords.show();
        //qDebug()<<"-----------------------";
    }
   // qDebug()<<"=========================";
}

void Message::addDataRecord(DataRecord dataRecord){
    mRecords.append(dataRecord);
}
QString Message::a(int num, QString sensorName){
    QString res;
    for(int i=0;i<num;i++) {
        res+=td( sensorName+QString::number(i) );
    }
    return res;
}
QString Message::b(int num){
     QString res="<td>b"+QString::number(num)+"</td>";
     return res;
}
QString Message::getShortInfo(){
    QList<DataRecord>::iterator i;
    QString info;

    for(i = mRecords.begin(); i != mRecords.end(); ++i) {
         info +="<TABLE border=\"1\" bordercolor=\"black\">";

         info += tr("<td >Дата</td>"
                    "<td align=\"center\" cellpadding=\"2\"> Время </td>"
                    "<td width=\"40px\" align=\"center\" cellpadding=\"2\"> Широта </td>"
                    "<td width=\"40px\" align=\"center\" cellpadding=\"2\"> Долгота </td>"
                    "<td align=\"center\" cellpadding=\"2\" > D1 </td>"
                    "<td align=\"center\" cellpadding=\"2\" > D2 </td>"
                    "<td align=\"center\" cellpadding=\"2\" > Вскрытие </td>"
                    "<td align=\"center\" cellpadding=\"2\" > Тревога </td>"
                    "<td align=\"center\" cellpadding=\"2\" > Питание </td>"
                    );

         QString row =
                td( (*i).mTimeStruct.getDate().toString() ) +
                td( (*i).mTimeStruct.getTime().toString() ) +
                td( (*i).mCoords.mLat.show() )+
                td( (*i).mCoords.mLon.show() ) +
                td( QString::number((*i).mSensors.D1) ) +
                td( QString::number((*i).mSensors.D2) ) +
                td( QString::number((*i).mSensors.D3) ) +
                td( QString::number((*i).mSensors.AL) ) +
                td( QString::number((*i).mSensors.IG) );

         info += tr(row);
         info += "</TABLE>";
         info +="<table></table>";
    }
    return info;
}

QString Message::getInfo(){
    QList<DataRecord>::iterator i;
    QString info;

    int k = 1;


    for(i = mRecords.begin(); i != mRecords.end(); ++i) {
        info +="<TABLE border=\"1\" bordercolor=\"black\">";

        const int NUM = 32;
        info += tr("<td colspan=\"3\" >Позиция</td></td>" + td_row(NUM, 0));
        info += tr("<td colspan=\"3\"></td><td colspan=\"10\" align=\"center\">Датчик A</td><td colspan=\"10\" align=\"center\">Датчик B</td><td></td><td></td><td>Вскрытие</td><td>Тревога</td><td>Питание</td>");
        info += tr(td("№")+td("Дата") +td("Время") + a(10, "a") + a(10, "b") +
                   td("D1") + td("D2") + td("D3") + td("AL") + td("IG") +td("")+td("") + td("EC") );
        QString row =
                td( QString::number(k))  +
                td( (*i).mTimeStruct.getDate().toString() ) +
                td( (*i).mTimeStruct.getTime().toString() ) +
                td( QString::number((*i).mSensors.a0) ) +
                td( QString::number((*i).mSensors.a1) ) +
                td( QString::number((*i).mSensors.a2) ) +
                td( QString::number((*i).mSensors.a3) ) +
                td( QString::number((*i).mSensors.a4) ) +
                td( QString::number((*i).mSensors.a5) ) +
                td( QString::number((*i).mSensors.a6) ) +
                td( QString::number((*i).mSensors.a7) ) +
                td( QString::number((*i).mSensors.a8) ) +
                td( QString::number((*i).mSensors.a9) ) +
                td( QString::number((*i).mSensors.b0) ) +
                td( QString::number((*i).mSensors.b1) ) +
                td( QString::number((*i).mSensors.b2) ) +
                td( QString::number((*i).mSensors.b3) ) +
                td( QString::number((*i).mSensors.b4) ) +
                td( QString::number((*i).mSensors.b5) ) +
                td( QString::number((*i).mSensors.b6) ) +
                td( QString::number((*i).mSensors.b7) ) +
                td( QString::number((*i).mSensors.b8) ) +
                td( QString::number((*i).mSensors.b9) ) +
                td( QString::number((*i).mSensors.D1) ) +
                td( QString::number((*i).mSensors.D2) ) +
                td( QString::number((*i).mSensors.D3) ) +
                td( QString::number((*i).mSensors.AL) ) +
                td( QString::number((*i).mSensors.IG) ) +
                td( QString::number((*i).mSensors.r26)) +
                td( QString::number((*i).mSensors.r27)) +
                td( QString::number((*i).mSensors.EC) ) +
                td( QString::number((*i).mSensors.r29)) +
                td( QString::number((*i).mSensors.r30)) +
                td( QString::number((*i).mSensors.r31)) +
                td( QString::number((*i).mSensors.r32)) +
                "";
         info += tr(row);

        QString coords = "<tr>";

        QString lat = "<td rowspan=\"2\" colspan=\"5\">Широта</td><td rowspan=\"2\" colspan=\"12\">" + (*i).mCoords.mLat.show() + "</td>";
        QString lon = "<td rowspan=\"2\" colspan=\"5\">Долгота</td><td rowspan=\"2\" colspan=\"13\">" + (*i).mCoords.mLon.show() + "</td>";
        coords+=lat;
        coords+=lon;
        coords += "</tr>";
        info +=coords;
        info +="</TABLE>";
    }


    return info;
}

QString Message::td(QString val){
    return "<td  cellpadding=\"2\" align=\"center\">" + QString(" ") + val + QString(" ") + "</td>";
}

QString Message::td_row(int number, int start_value){
    QString res;
    for(int i=1;i<number;i++){
        res +=td(QString::number(start_value+i));
    }
    return res;
}

QString Message::tr(QString val){
    return "<tr>" + val + "</tr>";
}
int Message::recordsCount() const{
    return mRecords.size();
}
QDateTime Message::date() const {
    return mIncomeDate;
}

QString Message::terminal() const {
    return mAtNum;
}
QString Message::id2() const {
    return mIdStrange;
}

void  Message::setSavedToDB() {
    flSavedToDB = true;
}

bool Message::isSavedToDB() const{
    return flSavedToDB;
}

QString Message::fileName() const{
    return mFileName;
}
int Message::pointSize() const {
    return mPointSize;
}

void Message::setPointSize(int sz) {
    mPointSize = sz;
}
