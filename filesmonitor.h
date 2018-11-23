#ifndef FILESCHECKER_H
#define FILESCHECKER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QThread>
#include <QMutex>
//#include <windows.h>
#include <iostream>
#include "message.h"
#include "ftpmessage.h"
//#include <direct.h>
#include <cstdlib>
//#include <tchar.h>
#include <stdio.h>
class FilesMonitor : public QThread
{
       Q_OBJECT
public:
    FilesMonitor(QString ftpFilesDir, QObject *parent = 0);
    QDir m_dir;

    //Получаем список файлов из директории
    QStringList getFtpFilesList();

    //Охрана очереди
    //QMutex mMsgMutex;


    void addToQueue(QString fileName);

    //Есть ли этот файл в контейнере
    bool isInQueue(QString fileName);
    //
    bool flStopped;
    //Дирректория откуда читать файлы
    QString getFtpDir() const;

    //Удаляем файл из рабочей папки
    bool deleteFtpFile(QString fl);

    //Контейнер для хранения объектов
    QList<FtpMessage> mFtpMessagesList;
    //ускоряем
    QStringList getFtpFilesListAPI();
signals:
    void new_message(QString fileName, QByteArray body, int coordSize);
    void sig_completed();
    void sig_progress(int, int);
    void remove(QString );
public slots:
    void slotProcessFiles();
    void run();
    void remove_ftp_filemessage(QString);
};

#endif // FILESCHECKER_H
