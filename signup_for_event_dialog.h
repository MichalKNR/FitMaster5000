#ifndef SIGNUP_FOR_EVENT_DIALOG_H
#define SIGNUP_FOR_EVENT_DIALOG_H

#define DEBUG //delete while playing with SQL magic !!!

#include <QDialog>
#include <typedefs.h>

namespace Ui {
class Signup_for_event_Dialog;
}

class Signup_for_event_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Signup_for_event_Dialog(QWidget *parent = nullptr);
    ~Signup_for_event_Dialog();

private slots:
    void on_End_PB_clicked();

    void on_pushButton_clicked();

    void on_Search_PB_clicked();

private:
    Ui::Signup_for_event_Dialog *ui;

    std::vector<FIT::Event> Events;
};

#endif // SIGNUP_FOR_EVENT_DIALOG_H
