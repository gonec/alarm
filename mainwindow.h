#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QProcess>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "message.h"
#include "filesmonitor.h"
#include "coordparser.h"
#include "messagesgenerator.h"
#include "messagemodel.h"
#include "messageproxyfilter.h"
#include "settings.h"
#include "myserver.h"
#include "synchronizer.h"
#include "ping.h"
#include "dialogdb.h"
#include "settings.h"
#include "dialogstorage.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QString iniFile, QWidget *parent = 0);
    ~MainWindow();

    FilesMonitor *mFilesMonitor;
    FilesMonitor *mFilesMonitor2;
    MessagesGenerator  *mMsgGenerator;
    MessageModel *mMessageModel;
    MessageProxyFilter *mProxyModel;
    Settings* mSettings;
    //Диалог с настройками базы данных
    DialogDB *mDialogDbSettings;
    //Диалог с настройками хранилища данных
    DialogStorage *mDialogStorage;
    MyServer *mServer;
    Synchronizer *mSynchronizer;
    Ping *mPinger;
    QString mIniFile;
public slots:
    void errorOccurred(QProcess::ProcessError error);
    void progress(int, int);
    void show_progressDB(int total, int proceed);
    void slot_queue_progress_info(int listSize, int saved_counter);
    void showMessagesStatistics(int, int);
    void show_db_settings();

private slots:
    void on_action_STORAGE_triggered();

signals:
    //Сигнал на удаление файла, т.к. он уже обработан!

    void show_MessagesStatistics(int, int);
private:
    bool flFtpReceiving;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
