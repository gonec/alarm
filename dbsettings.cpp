#include "dbsettings.h"
#include "ui_settings.h"
DbSettings::DbSettings()
{

}
DbSettings::DbSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DbSettings)
{
    ui->setupUi(this);
    QSettings settings;
    //settings.setValue("ini_file", "c:/ALARM/alarm.ini");
    QString ini_file = settings.value(QString("ini_file")).toString();
    //qDebug()<<""
    mIniSettings = new QSettings(ini_file, QSettings::IniFormat);
    mIniSettings->beginGroup("ftp");
    QString login = mIniSettings->value("ftp_login").toString();
    QString pass  = mIniSettings->value("ftp_password").toString();
    QString scriptPath = mIniSettings->value("script_path").toString();
    QString perlPath = mIniSettings->value("perl_path").toString();
    QString ftpDir = mIniSettings->value("ftp_dir").toString();


    mIniSettings->endGroup();
    mIniFile = ini_file;
    mLogin = login;
    mPassword = pass;
    mScriptPath = scriptPath;
    mPerlPath = perlPath;
    mFtpDir = ftpDir;
    updateUi();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::setSettings()
{
    mLogin    = ui->lnLogin->text();
    mPassword = ui->lnPass->text();
}

void Settings::loadSettings()
{
   // QSettings settings;
    //ui->lnLogin->setText(mLogin);
    //ui->lnPass->setText(mPassword);
    //ui->lnPerlPath->setText(perlPath);
    //ui->lnScriptPath->setText(scriptPath);
}



void Settings::on_pbSelect_clicked()
{
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
            tr("Ini Files (*.ini);"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            ui->lnIniFile->setText(fileName);
            QSettings settings;
            settings.setValue("ini_file", fileName);
            //QTextStream in(&file);
            //ui->lnIniFile->setText(in.readAll());
            file.close();
        }
}
void Settings::on_pbCancel_clicked()
{
   hide();
}

void Settings::on_pbSave_clicked()
{
    QString ini_file = ui->lnIniFile->text();
    QSettings settings;
    settings.setValue("ini_file", ini_file);
    mIniSettings = new QSettings(ini_file, QSettings::IniFormat);
    mIniSettings->beginGroup("ftp");
    mLogin = ui->lnLogin->text();
    mPassword = ui->lnPass->text();
    mPerlPath = ui->lnPerlPath->text();
    mScriptPath = ui->lnScriptPath->text();
    mFtpDir = ui->lnFtpDir->text();

    mIniSettings->setValue("ftp_login", mLogin) ;
    mIniSettings->setValue("ftp_password", mPassword ) ;
    mIniSettings->setValue("perl_path", mPerlPath);
    mIniSettings->setValue("script_path", mScriptPath);
    mIniSettings->setValue("ftp_dir", mFtpDir);
    mIniSettings->endGroup();
    updateUi();
}
void Settings::on_pbPerlSelect_clicked()
{
    QString perlPath = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Ini Files (*.exe);"));

    if (perlPath != "") {
        QFile file(perlPath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }



        setPerlPath(perlPath);
        file.close();
    }
}

void Settings::on_pbScriptSelect_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Ini Files (*.pl);"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        ui->lnScriptPath->setText(fileName);
        setScriptPath(fileName);
        file.close();
    }
}

void Settings::on_pbFtpDirSelect_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "c://",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    setFtpDir(dir);
}

QString Settings::getFtpDir(){
    return mFtpDir;
}

QString Settings::getPerlPath(){
    return mPerlPath;
}

QString Settings::getScriptPath(){
    return mScriptPath;
}

QString Settings::getLogin(){
    return mLogin;
}
QString Settings::getIniFile(){
    return mIniFile;
}
QString Settings::getPassword(){
    return mPassword;
}

void Settings::setFtpDir(QString ftpDir){
   mFtpDir = ftpDir;
   saveSettings();
}

void Settings::setLogin(QString login){
   mLogin = login;
   saveSettings();
}

void Settings::setPassword(QString password){
    mPassword = password;
    saveSettings();
}
void Settings::setPerlPath(QString perlPath){
    mPerlPath = perlPath;
    saveSettings();
}
void Settings::setScriptPath(QString scriptPath){
    mScriptPath = scriptPath;
    saveSettings();
}
void Settings::saveSettings(){
  // QSetings settings;
    //settings.setValue(QString("ini_file")).toString();
    mIniSettings->beginGroup("ftp");
    mIniSettings->setValue("ftp_login", mLogin) ;
    mIniSettings->setValue("ftp_password", mPassword ) ;
    mIniSettings->setValue("perl_path", mPerlPath);
    mIniSettings->setValue("script_path", mScriptPath);
    mIniSettings->setValue("ftp_dir", mFtpDir);
    mIniSettings->endGroup();
    updateUi();

}

void Settings::updateUi(){
    ui->lnLogin->setText(mLogin);
    ui->lnPass->setText(mPassword);
    ui->lnIniFile->setText(mIniFile);

    ui->lnPerlPath->setText(mPerlPath);

    QFile checkPerlPath(mPerlPath);
    if(!checkPerlPath.exists()){
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        ui->lnPerlPath->setPalette(*palette);
    }
    else{
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::black);
        ui->lnPerlPath->setPalette(*palette);
    }

    ui->lnScriptPath->setText(mScriptPath);
    QFile checkScriptPath(mScriptPath);
    if(!checkScriptPath.exists()){
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        ui->lnScriptPath->setPalette(*palette);
    }
    else{
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::black);
        ui->lnScriptPath->setPalette(*palette);
    }

    ui->lnScriptPath->setText(mScriptPath);

    ui->lnFtpDir->setText(mFtpDir);
    QFile checkFtpDir(mFtpDir);
    if(!checkFtpDir.exists()){
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        ui->lnFtpDir->setPalette(*palette);
    }
    else{
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::black);
        ui->lnFtpDir->setPalette(*palette);
    }

    //ui->lnIniFile->setText(mFtpDir);
    QFile checkIniFile(mIniFile);
    if(!checkIniFile.exists()){
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        ui->lnIniFile->setPalette(*palette);
    }
    else {
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::black);
        ui->lnIniFile->setPalette(*palette);
    }

}
