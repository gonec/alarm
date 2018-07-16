#include "dialogstorage.h"
#include "ui_dialogstorage.h"

DialogStorage::DialogStorage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStorage)
{
    ui->setupUi(this);

    QSettings settings;
    QString ini_file = settings.value( QString("ini_file") ).toString();

    mIniSettings = new QSettings(ini_file, QSettings::IniFormat);
    mIniSettings->beginGroup("storage");


    mArchive = mIniSettings->value("archive").toString();
    mWorking = mIniSettings->value("working").toString();
    mIniSettings->endGroup();
    ui->lnArchive->setText(mArchive);
    ui->lnWorking->setText(mWorking);
    /*
    mLogin    = mIniSettings->value("db_login").toString();
    mPassword = mIniSettings->value("db_password").toString();
    ui->lnHost->setText(mHost);
    ui->lnDatabase->setText(mDbname);
    ui->lnLogin->setText(mLogin);
    ui->lnPassword->setText(mPassword);

    */
}

DialogStorage::~DialogStorage()
{
    delete ui;
}
void DialogStorage::accept(){
    mIniSettings->beginGroup("storage");
    mWorking = ui->lnWorking->text();
    mIniSettings->setValue("working", mWorking);

    mArchive = ui->lnArchive->text();
    mIniSettings->setValue("archive", mArchive);

    mIniSettings->endGroup();


}
