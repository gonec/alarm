#ifndef MESSAGEPROXYFILTER_H
#define MESSAGEPROXYFILTER_H
#include <QSortFilterProxyModel>
#include <QDebug>
class MessageProxyFilter : public QSortFilterProxyModel
{
public:
    MessageProxyFilter(QObject* parent = 0);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool flSet;
    bool setFilter(bool fl);
};

#endif // MESSAGEPROXYFILTER_H
