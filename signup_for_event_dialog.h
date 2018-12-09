#ifndef SIGNUP_FOR_EVENT_DIALOG_H
#define SIGNUP_FOR_EVENT_DIALOG_H

#include <QDialog>

namespace Ui {
class Signup_for_event_Dialog;
}

class Signup_for_event_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Signup_for_event_Dialog(QWidget *parent = nullptr);
    ~Signup_for_event_Dialog();

private:
    Ui::Signup_for_event_Dialog *ui;
};

#endif // SIGNUP_FOR_EVENT_DIALOG_H
