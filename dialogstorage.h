#ifndef DIALOGSTORAGE_H
#define DIALOGSTORAGE_H
#include <QDialog>
#include <QSettings>
namespace Ui {
class DialogStorage;
}

class DialogStorage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStorage(QString iniFile, QWidget *parent = 0);
    ~DialogStorage();
    QString mIniFile;
private:
    Ui::DialogStorage *ui;

    QSettings *mIniSettings;

    //Путь к архивной дирректории
    QString mArchive;

    //Путь к рабочей дирректории
    QString mWorking;
public slots:
    void accept();
};

#endif // DIALOGSTORAGE_H
