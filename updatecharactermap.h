#ifndef UPDATECHARACTERMAP_H
#define UPDATECHARACTERMAP_H

#include <QObject>
#include<QMap>
class UpdateCharacterMap : public QObject
{
    Q_OBJECT
public:
    explicit UpdateCharacterMap(QObject *parent = nullptr);
    int Key(){
        return cKey;
    }
signals:
    void fillingMapFinished(const QMap<QChar,QChar>& m);

public slots:
void fillmap(const int key=3);
signals:
void keyChanged(int key);
void updateProgress(int progress);
private:
  int cKey=3;
};

#endif // UPDATECHARACTERMAP_H
