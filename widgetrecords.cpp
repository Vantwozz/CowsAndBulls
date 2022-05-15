#include "widgetrecords.h"
#include "ui_widgetrecords.h"
#include <QGridLayout>
#include <QFile>
#include <QTextStream>

WidgetRecords::WidgetRecords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetRecords)
{
    ui->setupUi(this);
    QGridLayout*gl1 = new QGridLayout(this);
    gl1->addWidget(ui->twRecords, 1, 0, 10, 1);
    gl1->addWidget(ui->lRecords, 0,0,1,1);
    ui->twRecords->setColumnWidth(1, 200);
    ui->twRecords->setColumnWidth(0, 140);
    ui->twRecords->setHorizontalHeaderItem(0,new QTableWidgetItem ("попытки"));
    ui->twRecords->setHorizontalHeaderItem(1,new QTableWidgetItem ("имя"));
    QFile record("record.txt");
    record.open(QIODevice::ReadOnly);
    QTextStream stream(&record);
    for(int i = 0; i<10;i++){
    QString key=stream.readLine();
    if(key.size()==0){
        break;
    }
    QString data=stream.readLine();
    ui->twRecords->setItem(i, 0, new QTableWidgetItem (key));
    ui->twRecords->setItem(i, 1, new QTableWidgetItem (data));
    }
    record.close();
}

WidgetRecords::~WidgetRecords()
{
    delete ui;
}
