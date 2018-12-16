#include "signup_for_event_dialog.h"
#include "ui_signup_for_event_dialog.h"

Signup_for_event_Dialog::Signup_for_event_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup_for_event_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Dodawanie nowego zajęcia");

    //Initializing combolist

    QStringList coaches;
    coaches<<"Adam Małysz"<<"Mariusz Pudzianowski"<<"Zbigniew Wodecki";
    ui->Coach_CB->addItems(coaches);
    QStringList places;
    places<<"Warszawa Centrum"<<"Warszawa Przedmieścia"<<"Kraków";
    ui->Place_CB->addItems(places);
    QStringList days;
    days<<"Poniedziałek"<<"Wtorek"<<"Środa"<<"Czwartek"<<"Piątek"<<"Sobota"<<"Niedziela";
    ui->Day_CB->addItems(days);

    //Initializing Table

    ui->EventsTable->setColumnCount(5);
    QStringList ColumnsNames;
    ColumnsNames<<"Nazwa"<<"Trener"<<"Miejsce"<<"Czas";
    ui->EventsTable->setHorizontalHeaderLabels(ColumnsNames);
    ui->EventsTable->setColumnWidth(Tytul,80);
    ui->EventsTable->setColumnWidth(Trener,125);
    ui->EventsTable->setColumnWidth(Miejsce,150);
    ui->EventsTable->setColumnWidth(Czas,150);
    ui->EventsTable->setColumnWidth(Ilosc_Miejsc,50);


}

Signup_for_event_Dialog::~Signup_for_event_Dialog()
{
    delete ui;
}

void Signup_for_event_Dialog::on_End_PB_clicked()
{

}

void Signup_for_event_Dialog::on_pushButton_clicked()
{

}

void Signup_for_event_Dialog::on_Search_PB_clicked()
{
    //TODO: evaluate SQL magic

#ifdef DEBUG //check if DEBUGGING is active
    {
        Events.push_back(FIT::Event("Aerobik",
                                        FIT::Friday,
                                        FIT::Warsaw_centre,
                                        std::vector<std::string>{"Janek","Bożena"},
                                        18,30,
                                        "Mariusz Pudzianowski", 15));
        Events.push_back(FIT::Event("Zumba",
                                        FIT::Monday,
                                        FIT::Warsaw_Suburbs,
                                        std::vector<std::string>{"Halina","Honorata"},
                                        18,30,
                                        "Adam Małysz",15));
    }
#endif


}

void Signup_for_event_Dialog::fill_Events_Table(){
    for(auto event: this->Events){
        ui->EventsTable->insertRow((ui->EventsTable->rowCount()));
        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Tytul,
                                 new QTableWidgetItem(QString::fromStdString(event.Title)));
        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Trener,
                                 new QTableWidgetItem(QString::fromStdString(event.coach)));
        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Miejsce,
                                 new QTableWidgetItem(QString::fromStdString(parse_place(event).toStdString())));
        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Czas,
                                 new QTableWidgetItem(QString::fromStdString(parse_time(event).toStdString())));

    }
}

QString Signup_for_event_Dialog::parse_time(FIT::Event event){
    QString Return_value;
    switch (event.day) {
    case FIT::Monday:
        Return_value="Poniedziałek ";
        break;
    case FIT::Tuesday:
        Return_value="Wtorek ";
        break;
    case FIT::Wednesday:
        Return_value="Środa ";
        break;
    case FIT::Thursday:
        Return_value="Czwartek ";
        break;
    case FIT::Friday:
        Return_value="Piątek ";
        break;
    case FIT::Saturday:
        Return_value="Sobota ";
        break;
    case FIT::Sundday:
        Return_value="Niedziela ";
        break;
    }

    Return_value+=QString::number(event.hour);
    Return_value+=":";
    Return_value+=QString::number(event.minutes);
    return Return_value;
}

QString Signup_for_event_Dialog::parse_place(FIT::Event event){
    switch (event.event_place) {
    case FIT::Warsaw_centre:
        return "Warszawa Centrum";
    case FIT::Warsaw_Suburbs:
        return "Warszawa Przedmieścia";
    case FIT::Cracov:
        return "Kraków";
    }
}
