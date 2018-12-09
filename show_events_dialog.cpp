#include "show_events_dialog.h"
#include "ui_show_events_dialog.h"
#include "QMessageBox"
#include <exception>

Show_Events_Dialog::Show_Events_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_Events_Dialog)
{
    ui->setupUi(this);
    ui->EventsTable->setColumnCount(4);
    QStringList ColumnsNames;
    ColumnsNames<<"Nazwa"<<"Trener"<<"Miejsce"<<"Czas";
    ui->EventsTable->setHorizontalHeaderLabels(ColumnsNames);

//DEBUG FILLING_EVENTS
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

    for(auto event: this->Events){
        ui->EventsTable->insertRow((ui->EventsTable->rowCount())-1);
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
QString Show_Events_Dialog::parse_time(FIT::Event event){
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

QString Show_Events_Dialog::parse_place(FIT::Event event){
    switch (event.event_place) {
    case FIT::Warsaw_centre:
        return "Warszawa Centrum";
    case FIT::Warsaw_Suburbs:
        return "Warszawa Przedmieścia";
    case FIT::Cracov:
        return "Kraków";
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
