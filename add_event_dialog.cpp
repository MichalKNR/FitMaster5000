#include "add_event_dialog.h"
#include "ui_add_event_dialog.h"
#include <QMessageBox>

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
    int parsed_time[2];
    parse_time(parsed_time);
    event_new.hour = parsed_time[0];
    event_new.minutes = parsed_time[1];

    //TODO do SQL magic to check if such event already exist
    bool already_exist=false;
    if(already_exist){
        valid_event=false;
        QMessageBox *already_exist_msg_box = new
                QMessageBox(QMessageBox::NoIcon,
                            "Duplikat!",
                            "Takie wydarzenie już istnieje.\n\r Zmień dane.");
        already_exist_msg_box->exec();
    }
    else
        valid_event=true;

    //TODO do SQL magic with adding new event

    bool added_properly=true;
    if(added_properly){
        valid_event=true;
        QMessageBox *adding_event_succes_msg_box = new
                QMessageBox(QMessageBox::NoIcon,
                            "Sukces dodawania!",
                            "Wszystko poszło znakomicie, nowe wydarzenie jest gotowe!");
        adding_event_succes_msg_box->exec();
    }
    else{
        QMessageBox *adding_event_error_msg_box = new
                QMessageBox(QMessageBox::NoIcon,
                            "Błąd dodawania!",
                            "Błąd bazy danych, sprawdź połączenie i strukturę");
        adding_event_error_msg_box->exec();
    }


}
void Add_Event_Dialog::on_End_PB_clicked()
{
    //TODO Evaluate SQL querry clearing
    this->accept();

}


void Add_Event_Dialog::parse_time(int* p_time){
    int  return_time[2];
    return_time[0] = ui->timeEdit->dateTime().time().hour();
    return_time[1]=ui->timeEdit->dateTime().time().minute();
    p_time = return_time;
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
