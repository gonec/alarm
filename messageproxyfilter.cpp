#include "messageproxyfilter.h"

MessageProxyFilter::MessageProxyFilter(QObject *parent) : QSortFilterProxyModel(parent)
{
    flSet = false;
}

bool MessageProxyFilter::setFilter(bool res){
    flSet = res;
    return true;
}

bool MessageProxyFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    if(flSet){
        QModelIndex indG = sourceModel()->index(source_row, 6, source_parent);
        if(sourceModel()->data(indG,Qt::CheckStateRole).toBool() == false ){
            return false;
        }
        return true;
    }
    return true;

}
