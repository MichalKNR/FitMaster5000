#include "signup_for_event_dialog.h"
#include "ui_signup_for_event_dialog.h"

Signup_for_event_Dialog::Signup_for_event_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup_for_event_Dialog)
{
    ui->setupUi(this);
}

Signup_for_event_Dialog::~Signup_for_event_Dialog()
{
    delete ui;
}
