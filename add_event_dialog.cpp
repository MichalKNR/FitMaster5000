#include "add_event_dialog.h"
#include "ui_add_event_dialog.h"

Add_Event_Dialog::Add_Event_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Event_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Dodawanie nowego zajęcia");
    QStringList coaches;
    coaches<<"Adam Małysz"<<"Mariusz Pudzianowski"<<"Zbigniew Wodecki";
    ui->Coach_CB->addItems(coaches);
    QStringList places;
    places<<"Warszawa Centrum"<<"Warszawa Przedmieścia"<<"Kraków";
    ui->Place_CB->addItems(places);
    QStringList days;
    days<<"Poniedziałek"<<"Wtorek"<<"Środa"<<"Czwartek"<<"Piątek"<<"Sobota"<<"Niedziela";
    ui->Day_CB->addItems(days);
}

Add_Event_Dialog::~Add_Event_Dialog()
{
    delete ui;
}

void Add_Event_Dialog::on_Add_event_PB_clicked()
{
    event_new.Title=ui->Title_LE->text().toStdString();
    event_new.coach=ui->Coach_CB->currentText().toStdString();
    event_new.day=parse_day(ui->Day_CB->currentText());
    event_new.event_place=parse_place(ui->Day_CB->currentText());
}
void Add_Event_Dialog::on_End_PB_clicked()
{
//TODO Evaluate SQL querry clearing
}


int* Add_Event_Dialog::parse_time(QString time){

}

FIT::Place Add_Event_Dialog::parse_place(QString place){
    if(place=="Warszawa Centrum") return FIT::Warsaw_centre;
    if(place=="Warszawa Przedmieścia") return FIT::Warsaw_Suburbs;
    if(place=="Kraków") return FIT::Cracov;
    return FIT::Warsaw_centre; //domyślnie
}

FIT::Day Add_Event_Dialog::parse_day(QString day){
    if(day=="Poniedziałek") return FIT::Monday;
    if(day=="Wtorek") return FIT::Tuesday;
    if(day=="Środa") return FIT::Wednesday;
    if(day=="Czwartek") return FIT::Thursday;
    if(day=="Piatek") return FIT::Friday;
    if(day=="Sobota") return FIT::Saturday;
    if(day=="Niedziela") return FIT::Sundday;
    return FIT::Monday; //domyślnie
}
