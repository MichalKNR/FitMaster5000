#include "signup_for_event_dialog.h"
#include "ui_signup_for_event_dialog.h"
#include "QMessageBox"

Signup_for_event_Dialog::Signup_for_event_Dialog(QWidget *parent,QString s) :
    QDialog(parent),
    ui(new Ui::Signup_for_event_Dialog)
{
    nr_karty=s;
    ui->setupUi(this);
    setWindowTitle("Zapisywanie się na zajęcia");

    is_selected_event = false;
    //Initializing combolist
    bool error=false;
    QSqlQuery qry;
    qry.prepare("SELECT t.imie,t.nazwisko FROM trenerzy as t");
    if(qry.exec())
    {
        QStringList coaches;
        while(qry.next())
        {
            QString trener = qry.value(0).toString() +" "+ qry.value(1).toString();
            coaches<<trener;
        }
        ui->Coach_CB->addItems(coaches);
    }
    else {
        error=true;
    }

    qry.prepare("SELECT nr_sali FROM miejsce");
    if(qry.exec())
    {
        QStringList places;
        while(qry.next())
        {
            QString sala = qry.value(0).toString();
            places<<sala;
        }
        ui->Place_CB->addItems(places);
    }
    else {
        error=true;
    }

    if(error)
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }
    //    QStringList coaches;
    //    coaches<<"Adam Małysz"<<"Mariusz Pudzianowski"<<"Zbigniew Wodecki";
    //    ui->Coach_CB->addItems(coaches);
    //    QStringList places;
    //    places<<"Warszawa Centrum"<<"Warszawa Przedmieścia"<<"Kraków";
    //    ui->Place_CB->addItems(places);
    QStringList days;
    //    days<<"Poniedziałek"<<"Wtorek"<<"Środa"<<"Czwartek"<<"Piątek"<<"Sobota"<<"Niedziela";
    days<<"poniedzialek"<<"wtorek"<<"sroda"<<"czwartek"<<"piatek"<<"sobota"<<"niedziela";
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
    QSqlQuery qry;
    qry.prepare("SELECT z.typ_zajec,m.nr_sali,z.dzien_tygodnia,z.godz_rozpoczecia,bierze_udzial.data,trenerzy.imie,trenerzy.nazwisko,m.limit_miejsc,COUNT(bierze_udzial.nr_karty_klienta),z.id_zajec FROM (zajecia AS z LEFT JOIN miejsce AS m ON z.nr_sali=m.nr_sali LEFT JOIN bierze_udzial ON z.id_zajec=bierze_udzial.id_zajec LEFT JOIN prowadzi ON z.id_zajec=prowadzi.id_zajec LEFT JOIN trenerzy ON prowadzi.nr_karty_trenera=trenerzy.nr_karty_trenera) GROUP BY bierze_udzial.data;");
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
            std::string liczba_zapisanych = qry.value(8).toString().toStdString();
            std::string id = qry.value(9).toString().toStdString();
            std::string godzina = czas.substr(0,2);
            std::string minut = czas.substr(3,2);
            FIT::Event event(typ,id,data,dz_tyg,nr_sali,liczba_zapisanych,godzina,minut,trener,limit);
            Events.push_back(event);
        }
    }
    else
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }

    //#ifdef DEBUG //check if DEBUGGING is active
    //    {
    //        Events.push_back(FIT::Event("Aerobik",
    //                                        FIT::Friday,
    //                                        FIT::Warsaw_centre,
    //                                        std::vector<std::string>{"Janek","Bożena"},
    //                                        18,30,
    //                                        "Mariusz Pudzianowski", 15));
    //        Events.push_back(FIT::Event("Zumba",
    //                                        FIT::Monday,
    //                                        FIT::Warsaw_Suburbs,
    //                                        std::vector<std::string>{"Halina","Honorata"},
    //                                        18,30,
    //                                        "Adam Małysz",15));
    //    }
    //#endif

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
                                 //                                 new QTableWidgetItem(QString::fromStdString(parse_place(event).toStdString())));
                                 new QTableWidgetItem(QString::fromStdString(event.event_place)));

        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Czas,
                                 new QTableWidgetItem(QString::fromStdString(parse_time(event).toStdString())));
        //        QString free_space_for_event_str = QString::number((int)event.participants.size());
        QString free_space_for_event_str = QString::fromStdString(event.participants);

        free_space_for_event_str+="/";
        //        free_space_for_event_str+=QString::number(event.max_participants);
        free_space_for_event_str+=QString::fromStdString(event.max_participants);

        ui->EventsTable->setItem(ui->EventsTable->rowCount()-1,
                                 Ilosc_Miejsc,
                                 new QTableWidgetItem(free_space_for_event_str));

    }
}

QString Signup_for_event_Dialog::parse_time(FIT::Event event){
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

    //    Return_value+=QString::number(event.hour);
    //    Return_value+=":";
    //    Return_value+=QString::number(event.minutes);
    Return_value=QString::fromStdString(event.date);
    Return_value+=" ";
    Return_value+=QString::fromStdString(event.day);
    Return_value+=" ";
    Return_value+=QString::fromStdString(event.hour);
    Return_value+=":";
    Return_value+=QString::fromStdString(event.minutes);

    return Return_value;
}

//QString Signup_for_event_Dialog::parse_place(FIT::Event event){
//    switch (event.event_place) {
//    case FIT::Warsaw_centre:
//        return "Warszawa Centrum";
//    case FIT::Warsaw_Suburbs:
//        return "Warszawa Przedmieścia";
//    case FIT::Cracov:
//        return "Kraków";
//    }
//}

void Signup_for_event_Dialog::on_EventsTable_itemClicked(QTableWidgetItem *item)
{
    ui->EventsTable->selectRow(item->row());

    is_selected_event = true;

    selected_item_row = item->row();
}
int Signup_for_event_Dialog::string_to_int(std::string s){
    int i;
    std::stringstream stream;
    stream.str(s);
    stream>>i;
    return i;
}
void Signup_for_event_Dialog::on_Signup_PB_clicked()
{
    if(is_selected_event){
        bool is_signup_good = true; //DEBUG fill
        //TODO: Do SQL magic
        FIT::Event selected_event=Events.at(selected_item_row);
        std::string limit = selected_event.max_participants;
        std::string liczba_zapisanych = selected_event.participants;
        if(string_to_int(liczba_zapisanych)<string_to_int(limit))
        {
            //insert do zapisany (automatycznie do bierze_udzial)
            QSqlQuery qry, qry0;
            QString id_zajec = QString::fromStdString(selected_event.id_zajec);
            //            QString nk= QString::fromStdString(nr_karty);
            QString nk=nr_karty;
//            qry.prepare("SELECT nr_karty_klienta,id_zajec FROM system_zapisow.zapisany_na; ");
            qry.prepare("INSERT INTO `system_zapisow`.`zapisany_na` (`nr_karty_klienta`, `id_zajec`) VALUES('" + nk +"','"+ id_zajec +"');");
            if(qry.exec())
            {
                is_signup_good = true;
            }
            else
            {
                is_signup_good = false;
            }
        }
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
