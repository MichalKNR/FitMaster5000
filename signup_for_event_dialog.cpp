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

    ui->EventsTable->setColumnCount(4);
    QStringList ColumnsNames;
    ColumnsNames<<"Nazwa"<<"Trener"<<"Miejsce"<<"Czas";
    ui->EventsTable->setHorizontalHeaderLabels(ColumnsNames);
    ui->EventsTable->setColumnWidth(Tytul,80);
    ui->EventsTable->setColumnWidth(Trener,125);
    ui->EventsTable->setColumnWidth(Miejsce,150);
    ui->EventsTable->setColumnWidth(Czas,150);

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
                                        "Mariusz Pudzianowski"));
        Events.push_back(FIT::Event("Zumba",
                                        FIT::Monday,
                                        FIT::Warsaw_Suburbs,
                                        std::vector<std::string>{"Halina","Honorata"},
                                        18,30,
                                        "Adam Małysz"));
    }
#endif


}
