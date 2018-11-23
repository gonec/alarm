/*
Файл сохранения настроек для базы данных
*/
#ifndef DIALOGDB_H
#define DIALOGDB_H
#include <QDialog>
#include <QSettings>
namespace Ui {
class DialogDB;
}

class DialogDB : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDB(QString iniFile, QWidget *parent = 0);
    ~DialogDB();
    QSettings *mIniSettings;
    QString mIniFile;
public slots:
    void accept();
    QString db_host();
    QString db_name();
    QString db_login();
    QString db_password();
private slots:
    void on_pushButton_clicked();

private:
    QString mHost;
    QString mDbname;
    QString mLogin;
    QString mPassword;
private:
    Ui::DialogDB *ui;
};

#endif // DIALOGDB_H
