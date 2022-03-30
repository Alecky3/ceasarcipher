#include "charactermodel.h"
#include<QFont>
CharacterModel::CharacterModel(QObject *parent):
    QAbstractTableModel(parent)
{

}

int CharacterModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return charactermap.size();
}

int CharacterModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 2;
}

QVariant CharacterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation==Qt::Horizontal){
       if(section==0){
           return QString("Key");
       }else{
           return QString("Value");
       }
    }else{
        return QString::number(section);
    }
    return QVariant();
}

QVariant CharacterModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role==Qt::DisplayRole){
        QMap<QChar,QChar>::const_iterator iter=charactermap.constBegin() + index.row();
        if(index.column()==0){
            return QString(iter.key());
        }else{

            return QString(iter.value());
        }
    }
    if(index.isValid() && role == Qt::UserRole+1){

        return QString(charactermap[QChar(index.row())]);
    }
    if(index.isValid() && role==Qt::FontRole){
        return QFont("Arial",24);
    }
    return QVariant();
}

QHash<int, QByteArray> CharacterModel::roleNames() const
{
    QHash<int,QByteArray>roles;
    roles[Qt::DisplayRole]="display";
    roles[Qt::UserRole+1]="filter";

    return roles;
}

void CharacterModel::updateCharacterMap(const QMap<QChar, QChar> &map)
{
    beginResetModel();
    charactermap=map;
    endResetModel();

}

QChar CharacterModel::value(const QChar &c)
{
    QMap<QChar,QChar>::const_iterator iter=charactermap.find(c);

    return iter.value();
}

QChar CharacterModel::key(const QChar &value)
{
    const QChar result=charactermap.key(value);

    return result;
}
