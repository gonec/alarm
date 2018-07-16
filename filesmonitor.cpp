#include "filesmonitor.h"

FilesMonitor::FilesMonitor(QString ftpFilesDir, QObject *parent) : QThread(parent)
{
    moveToThread(this);
    m_dir = QDir(ftpFilesDir);

}

QStringList FilesMonitor::getFtpFilesList() {

    m_dir.setFilter(QDir::Files  | QDir::NoSymLinks);
    QStringList messages = m_dir.entryList( QStringList("*.msg") );
    return messages;
}

//ВЫЗЫВАЕМ ЭТОТ МЕТОД ПО ТАЙМЕРУ!
void FilesMonitor::slotProcessFiles(){

        //получаем список всех файлов
        //qDebug()<<"FilesMonitor GETTING FILES LIST";
        QStringList currentFtpFiles = getFtpFilesList();

        int filesNum = currentFtpFiles.size();
        //qDebug()<<"FilesMonitor COMPLETED FILES IN DIR: "<<filesNum;
        int counter = 0;
        //перебираем их
        foreach (QString ftpFile, currentFtpFiles) {
            counter++;
            if ( isInQueue(ftpFile)  )
                addToQueue(ftpFile);

            if ( ((counter % 10) == 0 && filesNum) || (filesNum == counter)){
                emit sig_progress( filesNum, mFtpMessagesList.size() );
            }
        }
        sleep(1);
}

void FilesMonitor::run(){
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), SLOT(slotProcessFiles()) );
    const int cTimeout = 5000;
    timer.start(cTimeout);
    exec();
}

bool FilesMonitor::deleteFtpFile(QString filename){
       QString entryAbsPath = m_dir.absolutePath() + "/" + filename;
       QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
       if ( QFile::remove(entryAbsPath) ) {
           return true;
       }
       else{
           qDebug()<<"can't REMOVE"<<entryAbsPath;
       }
       return false;
}
void FilesMonitor::addToQueue(QString fileName) {
    FtpMessage ftpMessage(fileName, getFtpDir());
    ftpMessage.getBodyContent();
    mFtpMessagesList.append(ftpMessage);
    emit new_message(fileName, ftpMessage.mBody, ftpMessage.coordSize() );
}

bool FilesMonitor::isInQueue(QString fileName) {
    foreach (FtpMessage fmsg, mFtpMessagesList) {
        if ( fmsg.fileName() == fileName ) {
            return false;
        }
    }
    return true;
}

QString FilesMonitor::getFtpDir() const {
    return m_dir.absolutePath()+ "//" ;
}

void FilesMonitor::remove_ftp_filemessage(QString fl){
    qDebug()<<"FilesMonitor: REMOVING "<<fl;
    //Удаляем файл и сообщение
    for (int i=0; i<mFtpMessagesList.size(); i++) {
      if ( mFtpMessagesList[i].fileName() == fl ) {
         if( deleteFtpFile(fl) ) {
              //qDebug()<<"SUCCESFULLY DELETED "<<fl;
          }
          else{
              qDebug()<<"CAN NOT REMOVE";
          }
          mFtpMessagesList.removeAt(i);
          //ОБРАТНАЯ СВЯЗЬ
          emit remove(fl);
          qDebug()<<"fl found removing! OK "<<fl;
          break;
      }
    }
}
