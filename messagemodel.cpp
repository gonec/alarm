#include "messagemodel.h"

MessageModel::MessageModel()
{
    //mMessageList
}
QVariant MessageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();
    if ( orientation == Qt::Horizontal )
        {
            switch (section)
            {
            case COORDS_COUNT:
                return QVariant(QString::fromUtf8(""));
            case DDATE:
                return QVariant(QString::fromUtf8("Дата"));
            case AT_NUM:
                return QVariant(QString::fromUtf8("Номер АТ"));
            case ID:
                return QVariant(QString::fromUtf8("Идентификатор"));
            case ALARM:
               return QVariant(QString::fromUtf8("Тревога"));
            case OPEN:
                return QVariant(QString::fromUtf8("Вскрытие"));
            case POWER:
                return QVariant(QString::fromUtf8("Питание сеть"));
            case ATTENTION:
                return QVariant(QString::fromUtf8("ВНИМАНИЕ"));
            default:
                return QVariant();
            }
        }
        return QVariant();
    }

QVariant MessageModel::data(const QModelIndex &index, int role) const
{

    //qDebug()<<"MessageModel::data"<<index.row()<<"role "<<role;
    int num = index.row();
    Message msg = mMessageList[num];
    if( role == Qt::FontRole) {
        QFont boldFont;
        if(!msg.flSeen){
            boldFont.setBold(true);
        }
        return boldFont;

    }
    else if (role == Qt::BackgroundColorRole){

        if (msg.getDEFCON() != DEFCON_5 ){
            if( !msg.flSeen)
                return qVariantFromValue( QColor(Qt::red));

            else
                return qVariantFromValue( QColor(255, 153, 0));

        }
        else{
            //return qVariantFromValue( QColor(66, 170, 255));
        }
    }
    else if (role == Qt::DisplayRole) {

        if(index.column() == COORDS_COUNT){
             return QVariant(msg.recordsCount());
        }
        if(index.column() == DDATE){
            return QVariant(msg.mIncomeDate);
        }

        if(index.column() == AT_NUM ) {
            return QVariant(msg.mAtNum);
        }

        if(index.column() == ID) {
            return QVariant(msg.mIdStrange);
        }
    }

    else if ( role == Qt::CheckStateRole) {
        if(index.column() == ALARM) {
            return msg.isAlarm() ? Qt::Checked : Qt::Unchecked;
        }
        else if(index.column() == OPEN ) {
            return msg.isJailbreaking() ? Qt::Checked : Qt::Unchecked;
        }
        else if(index.column() == POWER ) {
            return msg.isIgnition() ? Qt::Checked : Qt::Unchecked;
        }

        if(index.column() == ATTENTION){
            return (msg.getDEFCON() == DEFCON_5) ? Qt::Unchecked : Qt::Checked;
        }
        return QVariant()  ;
    }

    else
        return QVariant();
      //QString fl = msg.mFileName;
     // return QVariant(fl);


}
    //
//}

Qt::ItemFlags MessageModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
       return 0;
      Qt::ItemFlags flags;
      //TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
      if ( index.column()>4 ) {
           flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable ;
           return flags;
      }


      //if (index.column() == 1) flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
      //if (index.column() == 2) flags |= Qt::ItemIsUserCheckable;
       // return flags;


    return QAbstractItemModel::flags(index);
}
int MessageModel::rowCount(const QModelIndex &parent) const {
    return mMessageList.size();
    //return 0;
}

int MessageModel::columnCount(const QModelIndex &parent) const {
    return NUM_ROWS;
}
void MessageModel::setMessageStorage(){
   // mMessageList
}
void MessageModel::addMessage(Message msg){
    int r = rowCount(QModelIndex());
    beginInsertRows(QModelIndex(), r, r);
    mMessageList.append(msg);
        // Добавляем одну строку в конец

        endInsertRows();

    emit dataChanged(QModelIndex(), QModelIndex());
}
int MessageModel::countNewMessages(){
    int num = 0;
    mNewMessages = 0;
    mAlarmMessages = 0;
    for(int i=0; i < mMessageList.size(); i++){
        if ( !(mMessageList[i]).wasSeen() ){
            mNewMessages++;
        }
        if ( DEFCON_1 == mMessageList[i].getDEFCON() ) {
            mAlarmMessages++;
        }
        num++;
    }
    qDebug()<<"size: "<<mMessageList.size()<<" COUNTING: "<<num<<" new: "<<mNewMessages<<" alarm: "<<mAlarmMessages;
    return 1;
}

