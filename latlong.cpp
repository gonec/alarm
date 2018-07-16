#include "latlong.h"

LatLong::LatLong()
{

}

QString LatLong::show(){
    //ШИРОТА
    if (!isLongtitude){
        QString strHem;
        if(hemisphere){
            strHem = "N";
        }
        else{
            strHem = "S";
        }
        return QString("%1 %2 %3 %4 %5").arg(deg).arg(QChar(176)).arg(minuts).arg(QChar(39)).arg(strHem);
    }
    else{
        return QString("%1 %2 %3 %4" ).arg(deg).arg(QChar(176)).arg(minuts).arg(QChar(39));
    }
}

QString LatLong::showMachine(){
    //ДОЛГОТА
    if (isLongtitude){

        QString strHem;
        if(hemisphere == 1){
            strHem = "W";
        }
        else{
            strHem = "E";
        }
        float degrees = calculateDegrees(deg, minuts, dm);
        return QString("%1 %2").arg(degrees).arg(strHem);
    }
    //ШИРОТА
    else{
        QString strHem;
        if(hemisphere){
             strHem = "S";

        }
        else{
            strHem = "N";
        }
        float degrees = calculateDegrees(deg, minuts, dm);
        return QString("%1 %2").arg(degrees).arg(strHem);




    }
}

float LatLong::calculateDegrees( int deg, int minuts, int dm) {

    QString strDm = QString::number(dm);
    QString strMin = QString::number(minuts);
    QString strMinutsFull = strMin +"."+strDm;
    float flMinutes = strMinutsFull.toFloat();
    float degFromMinutes =0;
    degFromMinutes = flMinutes/60;
    float fullDeg = deg + degFromMinutes;
    return fullDeg;
}
