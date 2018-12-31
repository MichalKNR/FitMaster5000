#include "signup_for_event_dialog.h"
#include "ui_signup_for_event_dialog.h"
#include "QMessageBox"

Signup_for_event_Dialog::Signup_for_event_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup_for_event_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Zapisywanie się na zajęcia");

    is_selected_event = false;
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
    ColumnsNames<<"Nazwa"<<"Trener"<<"Miejsce"<<"Czas"<<"Zajętosć";
    ui->EventsTable->setHorizontalHeaderLabels(ColumnsNames);
    ui->EventsTable->setColumnWidth(Tytul,80);
    ui->EventsTable->setColumnWidth(Trener,125);
    ui->EventsTable->setColumnWidth(Miejsce,150);
    ui->EventsTable->setColumnWidth(Czas,150);
    ui->EventsTable->setColumnWidth(Ilosc_Miejsc,60);

    ui->EventsTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // set readonly
}

Signup_for_event_Dialog::~Signup_for_event_Dialog()
{
    delete ui;
}

void Signup_for_event_Dialog::on_End_PB_clicked()
{
    this->accept();
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

    fill_Events_Table();

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
        QString free_space_for_event_str = QString::number((int)event.participants.size());

        free_space_for_event_str+="/";
        free_space_for_event_str+=QString::number(event.max_participants);
        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Ilosc_Miejsc,
                                 new QTableWidgetItem(free_space_for_event_str));

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

void Signup_for_event_Dialog::on_EventsTable_itemClicked(QTableWidgetItem *item)
{
    ui->EventsTable->selectRow(item->row());

    is_selected_event = true;

    selected_item_row = item->row();
}

void Signup_for_event_Dialog::on_Signup_PB_clicked()
{
    if(is_selected_event){
        bool is_signup_good = true; //DEBUG fill
        //TODO: Do SQL magic
        if(is_signup_good){
            QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,
                                              "Powodzenie zapisywanie",
                                              "Zapisywanie na zajęcia powiodło się!");
            msg->exec();
        }else
        {
            QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,
                                              "Niepowodzenie zapisywanie",
                                              "Zapisywanie na zajęcia nie powiodło się! \r\nSpróbuj ponownie za jakiś czas");
            msg->exec();
        }

    }
}
