#ifndef ADD_EVENT_DIALOG_H
#define ADD_EVENT_DIALOG_H

#include <QDialog>

namespace Ui {
class Add_Event_Dialog;
}

class Add_Event_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Event_Dialog(QWidget *parent = nullptr);
    ~Add_Event_Dialog();

private:
    Ui::Add_Event_Dialog *ui;
};

#endif // ADD_EVENT_DIALOG_H
