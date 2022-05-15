#ifndef WIDGETCOWS_H
#define WIDGETCOWS_H
#include <widgetrecords.h>

#include <QWidget>
#include <QMultiMap>

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetCows; }
QT_END_NAMESPACE

class WidgetCows : public QWidget
{
    Q_OBJECT

public:
    WidgetCows(QWidget *parent = nullptr);
    ~WidgetCows();

private slots:
    void on_pbNewgame_clicked();

    void on_pbCheck_clicked();

    void on_pbRecords_clicked();

private:
    Ui::WidgetCows *ui;
    int score;
    bool correctnum[10][4]{false};
    void startgame();
    bool isstarted=false;
    void victory();
    void newrecord();
    WidgetRecords *secondWindow;
    QMultiMap <int, QString> rec;
};
#endif // WIDGETCOWS_H
