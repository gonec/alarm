#include "dialogdb.h"
#include "ui_dialogdb.h"
#include <QDebug>
#include <QSqlDatabase>
DialogDB::DialogDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDB)
{
    ui->setupUi(this);
    QSettings settings;
    QString ini_file = settings.value(QString("ini_file")).toString();
    mIniSettings = new QSettings(ini_file, QSettings::IniFormat);
    mIniSettings->beginGroup("db");
    mHost     = mIniSettings->value("db_host").toString();
    mDbname   = mIniSettings->value("db_name").toString();
    mLogin    = mIniSettings->value("db_login").toString();
    mPassword = mIniSettings->value("db_password").toString();

    ui->lnHost->setText(mHost);
    ui->lnDatabase->setText(mDbname);
    ui->lnLogin->setText(mLogin);
    ui->lnPassword->setText(mPassword);
    mIniSettings->endGroup();

}

void DialogDB::accept(){
    mIniSettings->beginGroup("db");
    mHost = ui->lnHost->text();
    mIniSettings->setValue("db_host", mHost);

    mDbname = ui->lnDatabase->text();
    mIniSettings->setValue("db_name", mDbname);

    mLogin = ui->lnLogin->text();
    mIniSettings->setValue("db_login", mLogin);

    mPassword = ui->lnPassword->text();
    mIniSettings->setValue("db_password", mPassword);


}
QString DialogDB::db_host() {
   return mHost;
}

QString DialogDB::db_name() {
    return mDbname;
}

QString DialogDB::db_login() {
    return mLogin;
}

QString DialogDB::db_password() {
    return mPassword;
}

DialogDB::~DialogDB()
{
    delete ui;
}

void DialogDB::on_pushButton_clicked()
{
    QSqlDatabase db2;
    db2 =  QSqlDatabase::addDatabase("QMYSQL", "TEST");
    db2.setHostName(mHost);
    db2.setDatabaseName(mDbname);
    db2.setUserName(mLogin);
    db2.setPassword(mPassword);
    db2.open();
    if ( db2.isOpen() ) {
        db2.close();
        ui->lbDbTestResults->setText("Соединение установлено!");
    }
    else{
        ui->lbDbTestResults->setText("Не могу установить соединение");
    }
    //db2.setConnectOptions("MYSQL_OPT_RECONNECT=1");
}
