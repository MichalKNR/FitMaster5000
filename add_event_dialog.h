#ifndef ADD_EVENT_DIALOG_H
#define ADD_EVENT_DIALOG_H

#include <QDialog>
#include "typedefs.h"

namespace Ui {
class Add_Event_Dialog;
}

class Add_Event_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Event_Dialog(QWidget *parent = nullptr);
    ~Add_Event_Dialog();

private slots:
    void on_Add_event_PB_clicked();

    void on_End_PB_clicked();

private:
    Ui::Add_Event_Dialog *ui;

    int* parse_time(QString time);
    int parse_place(QString place);
    int parse_day(QString day);


};

#endif // ADD_EVENT_DIALOG_H
