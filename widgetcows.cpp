#include "widgetcows.h"
#include <QGridLayout>
#include "ui_widgetcows.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <array>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <string>
#include <QFile>
#include<iostream>
#include<QTextStream>
#include<QMultiMap>
#include<QInputDialog>
#include<iterator>
#include<QDir>

using namespace std;

WidgetCows::WidgetCows(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCows)
{
    ui->setupUi(this);
    secondWindow = new WidgetRecords();
    QGridLayout*gl = new QGridLayout(this);
    gl->addWidget(ui->leInput, 0,1,1,1);
    gl->addWidget(ui->pbCheck, 0,2,1,1);
    gl->addWidget(ui->pbNewgame, 0,0,1,1);
    gl->addWidget(ui->pbRecords, 0,3,1,1);
    gl->addWidget(ui->twFeedback, 1,0,4,12);
    ui->leInput->setInputMask("9999");
    ui->twFeedback->setColumnCount(1);
    ui->twFeedback->setColumnWidth(0, 800);
    ui->twFeedback->setItem(0,0,new QTableWidgetItem ("Игра не началась"));
    QFile record("record.txt");
    record.open(QIODevice::ReadOnly);
    QTextStream stream(&record);
    for(int i = 0; i<10;i++){
    QString str = stream.readLine();
    if(str.size()!=0){
    int key = str.toInt();
    QString data=stream.readLine();
    rec.insert(key, data);
    }else {
        break;
    }
    }
    record.close();
}

void WidgetCows::startgame(){
    std::array<int,10> a{0,1,2,3,4,5,6,7,8,9};
    srand(time(NULL));
    std::shuffle(a.begin(), a.end(), std::default_random_engine(rand()));

    for(int i = 0; i  <4; i++){
    correctnum[a[i]][i] = true;
    }
    score = 0;
    isstarted=true;
    ui->twFeedback->setRowCount(1);
    ui->twFeedback->setItem(0,0,new QTableWidgetItem ("Компьютер загадал новое число"/*+QString::number(a[0]) + QString::number(a[1]) + QString::number(a[2]) + QString::number(a[3])*/));
}

WidgetCows::~WidgetCows()
{
    delete ui;
}


void WidgetCows::on_pbNewgame_clicked()
{
    ui->twFeedback->clear();
    for (int i =0;i<10; i++){
        for(int j = 0; j<10;j++){
            correctnum[i][j]=false;
        }
    }
    ui->leInput->clear();
    startgame();
}

void WidgetCows::on_pbCheck_clicked()
{
    if(isstarted){
        QString var = ui->leInput->text();
        if (var.size()!=4){
            QMessageBox::question(this, "Ошибка!", "Количество введенных цифр должно равнятся 4", QMessageBox::Close);
        }else{
            int num;
            string num1;
            int numbers[4];
            num = var.toInt();
            num1 = to_string(num);
            if(num/1000>=1){
                for(int i=0;i<4;i++){
                    numbers[i] = num1[i] - (char)'0';
                }
            }else if(num/100>=1){
                num1.insert(0,"0");
                for(int i=0;i<4;i++){
                    numbers[i] = num1[i] - (char)'0';
                }
            }else{
                if(QMessageBox::question(this, "Ошибка!", "Цифры не должны повторяться!", QMessageBox::Close) ==QMessageBox::Close){
                    return;
                }
            }
            bool check[10]{false};
            for(int i=0;i<4;i++){
                if(!check[numbers[i]]){
                    check[numbers[i]] = true;
                }else{
                    if(QMessageBox::question(this, "Ошибка!", "Цифры не должны повторяться!", QMessageBox::Close) ==QMessageBox::Close){
                        return;
                    }
                }
            }
            score++;
            int cows = 0;
            int bulls = 0;
            for(int i = 0; i<4; i++){
                if(correctnum[numbers[i]][i]){
                    bulls++;
                }else{
                    for(int j=0; j<4; j++){
                        if(correctnum[numbers[i]][j]){
                            cows++;
                        }
                    }
                }
            }
            ui->twFeedback->insertRow(ui->twFeedback->rowCount());
            ui->twFeedback->setColumnWidth(ui->twFeedback->rowCount(), 800);
            ui->twFeedback->setItem(ui->twFeedback->rowCount()-1, 0, new QTableWidgetItem(QString::number(score)+")"+"Ваше число "+ var +".Коров "+QString::number(cows)+";Быков "+QString::number(bulls)));
            if(bulls == 4){
                victory();
            }
        }
    }else{
        QMessageBox::question(this, "Ошибка!", "Сначала начните игру!", QMessageBox::Close);
    }
}

void WidgetCows::victory(){
    isstarted = false;

    QFile record("record.txt");
    record.open(QIODevice::ReadOnly);
    QTextStream stream(&record);
    if(rec.size()<10){
        newrecord();
    }else {
        rec.clear();
        for(int i = 0; i<10;i++){
        int key=(stream.readLine()).toInt();
        QString data=stream.readLine();
        rec.insert(key, data);
        }
        QList<int> keys = rec.keys();
        sort(keys.begin(),keys.end());
        if(keys[9]>score){
            newrecord();
        }
    }
    record.close();
}

void WidgetCows::newrecord(){
    bool ok;
        QString name = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("User name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !name.isEmpty()){
        QMultiMap<int, QString>::iterator it = rec.end()-1;
        if(rec.size()>=10){
        it = rec.erase(it);
        }
        rec.insert(score, name);
        it = rec.begin();
        QFile record("record.txt");
        record.open(QIODevice::WriteOnly);
        QTextStream stream(&record);
        for(int i =0;i<10;i++){
            stream<< it.key()<<endl<<it.value()<<endl;
            it++;
            if (it == rec.end()){
                break;
            }
        }
        record.close();
    }
}

void WidgetCows::on_pbRecords_clicked()
{
    secondWindow = new WidgetRecords();
    secondWindow->show();
}
