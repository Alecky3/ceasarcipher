#include "updatecharactermap.h"
#include<QDebug>
UpdateCharacterMap::UpdateCharacterMap(QObject *parent) : QObject(parent)
{

}

void UpdateCharacterMap::fillmap(const int key)
{
    cKey=key;
    emit keyChanged(key);
    QMap<QChar,QChar>map;
    for(int i=0;i<=65535;i++){
        map[QChar(i)]=QChar((i+key)%65536);
        emit updateProgress(i);
    }

    emit fillingMapFinished(map);

}
