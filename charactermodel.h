#ifndef CHARACTERMODEL_H
#define CHARACTERMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include<QMap>

class CharacterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CharacterModel(QObject* parent=nullptr);
    int rowCount(const QModelIndex& parent=QModelIndex())const override;
    int columnCount(const QModelIndex& parent=QModelIndex())const override;
    QVariant headerData(int section,Qt::Orientation orientation,int role = Qt::DisplayRole)const override;
    QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const override;
    QHash<int,QByteArray>roleNames()const override;

    void updateCharacterMap(const QMap<QChar,QChar>&map);
    QChar value(const QChar& c);
    QChar key(const QChar& value);
private:
    QMap<QChar,QChar>charactermap;
};

#endif // CHARACTERMODEL_H
