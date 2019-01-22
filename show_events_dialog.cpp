#include "show_events_dialog.h"
#include "ui_show_events_dialog.h"
#include "QMessageBox"
#include <exception>

Show_Events_Dialog::Show_Events_Dialog(QWidget *parent, QString s) :
    QDialog(parent),
    ui(new Ui::Show_Events_Dialog)
{
    nr_karty=s;
    ui->setupUi(this);
    setWindowTitle("Okno przeglądania zajęć");
    ui->EventsTable->setColumnCount(4);
    QStringList ColumnsNames;
    ColumnsNames<<"Nazwa"<<"Trener"<<"Miejsce"<<"Czas";
    ui->EventsTable->setHorizontalHeaderLabels(ColumnsNames);
    ui->EventsTable->setColumnWidth(Tytul,80);
    ui->EventsTable->setColumnWidth(Trener,125);
    ui->EventsTable->setColumnWidth(Miejsce,150);
    ui->EventsTable->setColumnWidth(Czas,150);

    is_selected_event = false;
    //TODO evaluate SQL querry
    QString nk=nr_karty;
    QSqlQuery qry;
    //    QMessageBox *error_message = new QMessageBox("Błąd połączenia","SELECT z.typ_zajec,m.nr_sali,z.dzien_tygodnia,z.godz_rozpoczecia,bierze_udzial.data,trenerzy.imie,trenerzy.nazwisko,m.limit_miejsc,z.id_zajec FROM (zajecia AS z LEFT JOIN miejsce AS m ON z.nr_sali=m.nr_sali LEFT JOIN bierze_udzial ON z.id_zajec=bierze_udzial.id_zajec LEFT JOIN prowadzi ON z.id_zajec=prowadzi.id_zajec LEFT JOIN trenerzy ON prowadzi.nr_karty_trenera=trenerzy.nr_karty_trenera) WHERE bierze_udzial.nr_karty_klienta = "+nk,QMessageBox::NoIcon,0,0,0);
    //    error_message->exec();
    qry.prepare("SELECT z.typ_zajec,m.nr_sali,z.dzien_tygodnia,z.godz_rozpoczecia,bierze_udzial.data,trenerzy.imie,trenerzy.nazwisko,m.limit_miejsc,z.id_zajec FROM (zajecia AS z LEFT JOIN miejsce AS m ON z.nr_sali=m.nr_sali LEFT JOIN bierze_udzial ON z.id_zajec=bierze_udzial.id_zajec LEFT JOIN prowadzi ON z.id_zajec=prowadzi.id_zajec LEFT JOIN trenerzy ON prowadzi.nr_karty_trenera=trenerzy.nr_karty_trenera) WHERE bierze_udzial.nr_karty_klienta = "+nk);
    if(qry.exec())
    {
        while(qry.next())
        {
            std::string typ = qry.value(0).toString().toStdString();
            std::string nr_sali = qry.value(1).toString().toStdString();
            std::string dz_tyg = qry.value(2).toString().toStdString();
            std::string czas = qry.value(3).toString().toStdString();
            std::string data = qry.value(4).toString().toStdString();
            std::string trener = qry.value(5).toString().toStdString() +" "+ qry.value(6).toString().toStdString();
            std::string limit = qry.value(7).toString().toStdString();
            std::string id = qry.value(8).toString().toStdString();
            std::string zapisani="0";//chyba nie ważne tu

            std::string godzina = czas.substr(0,2);
            std::string minut = czas.substr(3,2);
            //            std::vector<std::string> zapisani = {"Halina","Honorata"};
            //liczba zapisanych???
            //TODO Events.push_back
            FIT::Event event(typ,id,data,dz_tyg,nr_sali,zapisani,godzina,minut,trener,limit);
            Events.push_back(event);

        }
    }
    else
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia",nk+"Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }

    //DEBUG FILLING_EVENTS
    //    {
    //        Events.push_back(FIT::Event("Aerobik",
    //                                    FIT::Friday,
    //                                    FIT::Warsaw_centre,
    //                                    std::vector<std::string>{"Janek","Bożena"},
    //                                    18,30,
    //                                    "Mariusz Pudzianowski",15));
    //        Events.push_back(FIT::Event("Zumba",
    //                                    FIT::Monday,
    //                                    FIT::Warsaw_Suburbs,
    //                                    std::vector<std::string>{"Halina","Honorata"},
    //                                    18,30,
    //                                    "Adam Małysz",15));
    //    }

    fill_Events_Table();

    bool EventsExist;
    if(Events.empty()) EventsExist = false;
    else EventsExist = true;
    if(!EventsExist){
        QMessageBox *NoEventsMsgBox =
                new QMessageBox("Brak zajęć",
                                "Nie uczestniczysz w żadnych zajęciach \n\r Zapisz się, aby zobaczyć swoje obecności",
                                QMessageBox::NoIcon,0,0,0);
        NoEventsMsgBox->exec();
        this->accept();
    }

}
//QString Show_Events_Dialog::parse_time(FIT::Event event){
//    QString Return_value;
//    switch (event.day) {
//    case FIT::Monday:
//        Return_value="Poniedziałek ";
//        break;
//    case FIT::Tuesday:
//        Return_value="Wtorek ";
//        break;
//    case FIT::Wednesday:
//        Return_value="Środa ";
//        break;
//    case FIT::Thursday:
//        Return_value="Czwartek ";
//        break;
//    case FIT::Friday:
//        Return_value="Piątek ";
//        break;
//    case FIT::Saturday:
//        Return_value="Sobota ";
//        break;
//    case FIT::Sundday:
//        Return_value="Niedziela ";
//        break;
//    }

//    Return_value+=QString::number(event.hour);
//    Return_value+=":";
//    Return_value+=QString::number(event.minutes);
//    return Return_value;
//}

//QString Show_Events_Dialog::parse_place(FIT::Event event){
//    switch (event.event_place) {
//    case FIT::Warsaw_centre:
//        return "Warszawa Centrum";
//    case FIT::Warsaw_Suburbs:
//        return "Warszawa Przedmieścia";
//    case FIT::Cracov:
//        return "Kraków";
//    }
//}
QString Show_Events_Dialog::parse_time(FIT::Event event){
    QString Return_value;
    //    switch (event.day) {
    //    case FIT::Monday:
    //        Return_value="Poniedziałek ";
    //        break;
    //    case FIT::Tuesday:
    //        Return_value="Wtorek ";
    //        break;
    //    case FIT::Wednesday:
    //        Return_value="Środa ";
    //        break;
    //    case FIT::Thursday:
    //        Return_value="Czwartek ";
    //        break;
    //    case FIT::Friday:
    //        Return_value="Piątek ";
    //        break;
    //    case FIT::Saturday:
    //        Return_value="Sobota ";
    //        break;
    //    case FIT::Sundday:
    //        Return_value="Niedziela ";
    //        break;
    //    }
    Return_value=QString::fromStdString(event.date);
    Return_value+=" ";
    Return_value+=QString::fromStdString(event.day);
    Return_value+=" ";
    //    Return_value+=QString::number(event.hour);
    Return_value+=QString::fromStdString(event.hour);
    Return_value+=":";
    //    Return_value+=QString::number(event.minutes);
    Return_value+=QString::fromStdString(event.minutes);
    return Return_value;
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

void Show_Events_Dialog::fill_Events_Table(){
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
                                 //                                 new QTableWidgetItem(QString::fromStdString(parse_place(event).toStdString())));
                                 new QTableWidgetItem(QString::fromStdString(event.event_place)));

        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Czas,
                                 //                                 new QTableWidgetItem(QString::fromStdString(parse_time(event).toStdString())));
                                 new QTableWidgetItem(parse_time(event)));

    }
}

void Show_Events_Dialog::on_exit_event_PB_clicked()
{
    if(is_selected_event){
        bool is_exit_good = true; //DEBUG fill
        //TODO: Do SQL magic
        //wypisanie sie

        FIT::Event selected_event=Events.at(selected_item_row);

        QSqlQuery qry;
        QString id_zajec = QString::fromStdString(selected_event.id_zajec);
        QString nk=nr_karty;
        qry.prepare("DELETE FROM bierze_udzial WHERE bierze_udzial.nr_karty_klienta = "+nk+" AND bierze_udzial.id_zajec");
        if(qry.exec())
        {
            is_exit_good = true;
        }
        else
        {
            is_exit_good = false;
        }


        if(is_exit_good){
            QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,
                                               "Powodzenie wypisywanie",
                                               "Wypisywanie na zajęcia powiodło się!");
            msg->exec();
        }else
        {
            QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,
                                               "Niepowodzenie wypisywanie",
                                               "Wypisywanie na zajęcia nie powiodło się! \r\nSpróbuj ponownie za jakiś czas");
            msg->exec();
        }
    }
}

void Show_Events_Dialog::on_EventsTable_itemClicked(QTableWidgetItem *item)
{
    ui->EventsTable->selectRow(item->row());

    is_selected_event = true;

    selected_item_row = item->row();
}
