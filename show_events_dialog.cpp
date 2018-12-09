#include "show_events_dialog.h"
#include "ui_show_events_dialog.h"
#include "QMessageBox"

Show_Events_Dialog::Show_Events_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_Events_Dialog)
{
    ui->setupUi(this);

    //TODO evaluate SQL querry

    bool EventsExist = false; //DEBUG Teraz nie ma żadnych zajęć
    if(EventsExist){
        //TODO Show Events
    }
    else{
        QMessageBox *NoEventsMsgBox = new QMessageBox("Brak zajęć",
                                                     "Nie uczestniczysz w żadnych zajęciach \n\r Zapisz się, aby zobaczyć swoje obecności",
                                                     QMessageBox::NoIcon,0,0,0);
        NoEventsMsgBox->exec();
        this->accept();
    }
}

Show_Events_Dialog::~Show_Events_Dialog()
{
    delete ui;
}

void Show_Events_Dialog::on_End_Dialog_PB_clicked()
{
    //TODO clear SQL querry Data

    this->accept();
}
