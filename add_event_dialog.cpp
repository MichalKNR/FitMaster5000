#include "add_event_dialog.h"
#include "ui_add_event_dialog.h"

Add_Event_Dialog::Add_Event_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Event_Dialog)
{
    ui->setupUi(this);
}

Add_Event_Dialog::~Add_Event_Dialog()
{
    delete ui;
}
