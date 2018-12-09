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

    FIT::Event event_new;
    bool valid_event;

private slots:
    void on_Add_event_PB_clicked();

    void on_End_PB_clicked();

private:
    Ui::Add_Event_Dialog *ui;

    void parse_time(int *p_time);
    FIT::Place parse_place(QString place);
    FIT::Day parse_day(QString day);


};

#endif // ADD_EVENT_DIALOG_H
