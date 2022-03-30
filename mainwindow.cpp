#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"updatecharactermap.h"
#include<QTextEdit>
#include<QDebug>
#include<QSortFilterProxyModel>
#include<QRandomGenerator>
#include<QProgressBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updater=new UpdateCharacterMap;
    updater->moveToThread(&myThread);
    connect(&myThread,&QThread::finished,this,&QObject::deleteLater);
    connect(updater,&UpdateCharacterMap::fillingMapFinished,this,&MainWindow::updateModel);
    connect(updater,&UpdateCharacterMap::keyChanged,this,&MainWindow::newKey);
    setWindowTitle("Ceasar Cypher");
    myThread.start();
    proxy=new QSortFilterProxyModel;
    myModel=new CharacterModel;
    myModel->moveToThread(&proxyThread);
    proxy->setSourceModel(myModel);
    proxy->setFilterRole(Qt::UserRole+1);
    proxy->moveToThread(&proxyThread);
    connect(&proxyThread,&QThread::finished,proxy,&QObject::deleteLater);
    connect(&proxyThread,&QThread::finished,myModel,&QObject::deleteLater);
    proxyThread.start();
    qDebug()<<myModel->rowCount();
    ui->tableView->setModel(proxy);
    updater->fillmap(3);
    ui->plaintextEncode->setFontPointSize(14);
    ui->ciphertextEncode->setFontPointSize(14);

    ui->minSpinBox->setRange(3,65000);
    ui->minSpinBox->setValue(5);
    ui->maxSpinbox->setRange(3,65000);
    ui->maxSpinbox->setValue(10);
    ui->randomizepushButton->click();
    connect(ui->lineEdit,&QLineEdit::textChanged,this,&MainWindow::setFilterString);
    connect(ui->minSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),[=](int value){
        if(ui->maxSpinbox->value() <= ui->minSpinBox->value()){
            ui->maxSpinbox->setValue(ui->minSpinBox->value()+1);
        }
    });

    QProgressBar *progress=new QProgressBar;
    progress->setStyleSheet("height: 10px;border:none;background-color:#e0e0e0;outline:none;border-radius:2px;text-align:center;color: #fff;");
    progress->setValue(0);
    progress->setRange(0,65535);
    statusBar()->addWidget(progress);

    connect(updater,&UpdateCharacterMap::updateProgress,progress,&QProgressBar::setValue);
//    connect(ui->plaintextEncode,&QTextEdit::textChanged,ui->encodeBtn,&QPushButton::click);
}

MainWindow::~MainWindow()
{

    myThread.wait(1000);
    myThread.quit();
    proxyThread.wait(1000);
    proxyThread.quit();
    delete ui;
}

void MainWindow::updateModel(const QMap<QChar, QChar> &map)
{
//    qDebug()<<"updating caharacter map";
    myModel->updateCharacterMap(map);
}


void MainWindow::on_encodeBtn_clicked()
{
//    qDebug()<<ui->plaintextEncode->toHtml();
    QString plaintext=ui->plaintextEncode->toHtml();

    QChar *encoded=plaintext.data();
    for(int i=0;i<plaintext.size();i++){
        encoded[i]=myModel->value(plaintext[i]);
    }
    ui->ciphertextEncode->clear();
    ui->ciphertextEncode->setPlainText(QString(encoded));

}


void MainWindow::on_decodeBtn_clicked()
{
  QString encodedtext=ui->ciphertextEncode->toPlainText();
  QChar* decoded=encodedtext.data();

  for(int i=0;i<encodedtext.size();i++){
      decoded[i]=myModel->key(encodedtext[i]);
  }
  ui->plaintextEncode->clear();
  ui->plaintextEncode->setHtml(QString(decoded));
}

void MainWindow::setFilterString(const QString &filter)
{
   proxy->setFilterRegularExpression(filter);
  proxy->setFilterKeyColumn(1);
}


void MainWindow::on_randomizepushButton_clicked()
{
    int min=ui->minSpinBox->value();
    int max=ui->maxSpinbox->value();
    int key = QRandomGenerator::global()->bounded(min,max);
    updater->fillmap(key);
}

void MainWindow::newKey(int key)
{
    ui->keyLineedit->setText(QString::number(key));
}


void MainWindow::on_maxSpinbox_valueChanged(int arg1)
{
    if(arg1<=ui->minSpinBox->value()){
        ui->maxSpinbox->setValue(ui->minSpinBox->value()+1);
    }
}

