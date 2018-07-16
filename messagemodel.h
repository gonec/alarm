#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QColor>
#include <QFont>
#include "message.h"
enum HEADERS {
    COORDS_COUNT,
    DDATE = 1,
    AT_NUM,
    ID,
    ALARM,
    OPEN,
    POWER,
    ATTENTION
};
class MessageModel : public QAbstractTableModel
{
public:
    MessageModel();
    void setMessageStorage();
    void addMessage(Message msg_);
    QList<Message> mMessageList;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
     int columnCount(const QModelIndex &parent) const;
    int countNewMessages();
    int mNewMessages;
    int mAlarmMessages;
    const int NUM_ROWS = 8;
private:
    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;


};

#endif // MESSAGEMODEL_H
