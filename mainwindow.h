#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"charactermodel.h"
#include"updatecharactermap.h"
#include<QThread>
#include<QSortFilterProxyModel>
#include<QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void updateModel(const QMap<QChar,QChar>&map);

private slots:
    void on_encodeBtn_clicked();

    void on_decodeBtn_clicked();

    void setFilterString(const QString& filter);

    void on_randomizepushButton_clicked();

    void newKey(int key);

    void on_maxSpinbox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    CharacterModel* myModel;
    UpdateCharacterMap* updater;
    QThread myThread;
    QThread proxyThread;
    QSortFilterProxyModel* proxy;
};
#endif // MAINWINDOW_H
