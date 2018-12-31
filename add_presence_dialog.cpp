#include "add_presence_dialog.h"
#include "ui_add_presence_dialog.h"

Add_presence_dialog::Add_presence_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_presence_dialog)
{
    ui->setupUi(this);
}

Add_presence_dialog::~Add_presence_dialog()
{
    delete ui;
}
