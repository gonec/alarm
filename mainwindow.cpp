#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>
#define SQL_DEBUG

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mDialogDbSettings = new DialogDB();
    mDialogStorage = new DialogStorage();
    mSettings = new Settings(parent);
    ui->setupUi(this);
    QString ftpDir = mSettings->getFtpDir();

    //mServer = new MyServer
    mFilesMonitor = new FilesMonitor(ftpDir);

   // mMessageModel = new MessageModel();

    mSynchronizer = new Synchronizer(
                                     mDialogDbSettings->db_host(),
                                     mDialogDbSettings->db_name(),
                                     mDialogDbSettings->db_login(),
                                     mDialogDbSettings->db_password()
                                     );

    connect(mFilesMonitor,  SIGNAL( new_message    (QString, QByteArray, int) ),
            mSynchronizer, SLOT(    income_message (QString, QByteArray, int) ) );

    connect(mFilesMonitor,  SIGNAL( sig_progress(int, int) ), this, SLOT ( progress(int, int) ));

    //После удаления файла, удаляем его и из очереди синхронизатора
    connect(mFilesMonitor,  SIGNAL( remove(QString ) ), mSynchronizer, SLOT ( remove(QString) ));

    connect(mSynchronizer, SIGNAL(queue_progress_info(int,int)), this, SLOT(slot_queue_progress_info(int,int)));
    connect(mSynchronizer, SIGNAL(remove_ftp_file(QString)), mFilesMonitor, SLOT(remove_ftp_filemessage(QString)) );
    connect(mSynchronizer, SIGNAL(show_progressDB(int, int)), this, SLOT(show_progressDB(int, int)));

    connect(ui->action_DB,  SIGNAL( triggered() ), this, SLOT(show_db_settings()));

    connect(mSynchronizer, SIGNAL( show_MessagesStatistics(int, int) ), this, SLOT( showMessagesStatistics(int,int) ));






    mSynchronizer->start();
    mFilesMonitor->start();
    mPinger = new Ping(
                mDialogDbSettings->db_host(),
                mDialogDbSettings->db_name(),
                mDialogDbSettings->db_login(),
                mDialogDbSettings->db_password()
                );
    mPinger->start();

}




MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::progress(int total, int proceed){
    ui->lbFilesProceed->setText( "Обработано " + QString::number(proceed) + " из "+ QString::number(total) );
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(proceed);
}

void MainWindow::showMessagesStatistics(int total, int proceed){
    ui->lbMessagesProceed->setText( "Обработано " + QString::number(proceed) + " из "+ QString::number(total) );
    //ui->progressBarFTP->setMaximum(total);
    //ui->progressBarFTP->setValue(proceed);
}

void MainWindow::show_progressDB(int total, int proceed){
    ui->lbMessagesProceed->setText( "Сообщений в очереди " + QString::number(total) +
                                    " обработано "+ QString::number(proceed) );
    ui->progressBarDB->setMaximum(total);
    ui->progressBarDB->setValue(proceed);
}

void MainWindow::errorOccurred(QProcess::ProcessError error){
   qDebug()<<error;
}

void MainWindow::slot_queue_progress_info(int total, int counter ){

    ui->lbMessagesProceed->setText( "Сообщений в очереди " + QString::number(total) +
                                    " обработано "+ QString::number(counter) );
    ui->progressBarDB->setMaximum(total);
    ui->progressBarDB->setValue(counter);

    if (!total && !counter) {
        ui->progressBarDB->setEnabled(false);
    }
    else{
        ui->progressBarDB->setEnabled(true);
    }

}

void MainWindow::show_db_settings(){
    mDialogDbSettings->show();
}

void MainWindow::on_action_STORAGE_triggered()
{
    mDialogStorage->show();
}
