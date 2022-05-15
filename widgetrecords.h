#ifndef WIDGETRECORDS_H
#define WIDGETRECORDS_H

#include <QWidget>

namespace Ui {
class WidgetRecords;
}

class WidgetRecords : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRecords(QWidget *parent = nullptr);
    ~WidgetRecords();

private:
    Ui::WidgetRecords *ui;
};

#endif // WIDGETRECORDS_H
