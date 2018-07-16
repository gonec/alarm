#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "settings.h"
#include <QSettings>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();


    void setSettings();
    void loadSettings();
    QSettings settings;
    QSettings *mIniSettings;

    QString getFtpDir();
    void setFtpDir(QString dir);

    QString getPerlPath();
    void setPerlPath(QString perlPath);

    QString getScriptPath();
    void setScriptPath(QString scriptPath);

    QString getLogin();
    void setLogin(QString login);
    QString getIniFile();
    QString getPassword();
    void setPassword(QString password);

    QString mFtpDir;
    QString mPerlPath;
    QString mScriptPath;
    QString mLogin;
    QString mPassword;
    QString mIniFile;
private slots:


    void on_pbSelect_clicked();

    void on_pbCancel_clicked();

    void on_pbSave_clicked();

    void on_pbPerlSelect_clicked();

    void on_pbScriptSelect_clicked();

    void on_pbFtpDirSelect_clicked();
    void saveSettings();
    void updateUi();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H







