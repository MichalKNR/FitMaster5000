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

void Add_Event_Dialog::on_Add_event_PB_clicked()
{

}

void Add_Event_Dialog::on_End_PB_clicked()
{

}


int* Add_Event_Dialog::parse_time(QString time){

}

int Add_Event_Dialog::parse_place(QString place){
    if(place=="Warszawa centrum") return FIT::Monday;
    if(place=="Warszawa przedmieścia") return FIT::Tuesday;
    if(place=="środa") return FIT::Wednesday;
}

int Add_Event_Dialog::parse_day(QString day){
    if(day=="poniedziałek") return FIT::Monday;
    if(day=="wtorek") return FIT::Tuesday;
    if(day=="środa") return FIT::Wednesday;
    if(day=="czwartek") return FIT::Thursday;
    if(day=="piatek") return FIT::Friday;
    if(day=="sobota") return FIT::Saturday;
    if(day=="niedziela") return FIT::Sundday;
    else
        return -1;
}
