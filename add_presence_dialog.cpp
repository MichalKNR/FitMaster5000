#include "add_presence_dialog.h"
#include "ui_add_presence_dialog.h"
#include "QMessageBox"

Add_presence_dialog::Add_presence_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_presence_dialog)
{
    ui->setupUi(this);
    setWindowTitle("Dodawanie obecności");


    {
        ui->Automatic_RB->setChecked(true);
        ui->Manual_RB->setChecked(false);
        isAutomatic_Participant_adding_on = true;
        on_Automatic_RB_clicked();


        //Initializing Table

        ui->Participants_TV->setColumnCount(2);
        QStringList ColumnsNames;
        ColumnsNames<<"Imię"<<"Nazwisko";
        ui->Participants_TV->setHorizontalHeaderLabels(ColumnsNames);
        ui->Participants_TV->setColumnWidth(0,125);
        ui->Participants_TV->setColumnWidth(1,125);

        ui->Participants_TV->setEditTriggers(QAbstractItemView::NoEditTriggers); // set readonly

    }
    bool error=false;
    QSqlQuery qry,qry0;
    //TODO: do SQL magic to fill the Participants list
    qry.prepare("SELECT k.nr_karty_klienta,k.imie,k.nazwisko,bu.data FROM klienci as k INNER JOIN bierze_udzial as bu ON k.nr_karty_klienta=bu.nr_karty_klienta WHERE bu.id_zajec=1 GROUP BY nr_karty_klienta");
    if(qry.exec())
    {
//        QStringList klienci;
        while(qry.next())
        {
            QString imie = qry.value(1).toString();
            QString nazw = qry.value(2).toString();
//            klienci<<klient;


            ui->Participants_TV->insertRow((ui->Participants_TV->rowCount()));
            ui->Participants_TV->setItem(ui->Participants_TV->rowCount()-1,
                                     0,
                                     new QTableWidgetItem(imie));
            ui->Participants_TV->setItem(ui->Participants_TV->rowCount()-1,
                                     1,
                                     new QTableWidgetItem(nazw));
        }
    }
    else {
        error=true;
    }



    //TODO: do SQL magic to fill the events list
    QStringList events_names;


    qry.prepare("SELECT nr_sali FROM miejsce");
    if(qry.exec())
    {
        //        QStringList places;
        while(qry.next())
        {
            QString sala = qry.value(0).toString();
            events_names<<sala;
        }
        ui->Events_Selection_CB->addItems(events_names);
    }
    else {
        error=true;
    }

    //TODO: do SQL magic to fill the events list
    QStringList data_names;
    ui->Data_CB->clear();
    qry.prepare("SELECT data FROM bierze_udzial WHERE id_zajec="+selected_id);
    if(qry.exec())
    {
        //        QStringList places;
        while(qry.next())
        {
            QString sala = qry.value(0).toString();
            data_names<<sala;
        }
        ui->Data_CB->addItems(data_names);
    }
    else {
        error=true;
    }
    selected_id=1;
    selected_data=data_names.at(0);
    if(error)
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }

    //DEBUG filing with random data

    //    QStringList events_names;
    //    events_names<<"Aerobik"<<"Zumba";
    //    ui->Events_Selection_CB->addItems(events_names);
}

Add_presence_dialog::~Add_presence_dialog()
{
    delete ui;
}

void Add_presence_dialog::on_Automatic_RB_clicked()
{
    ui->Participants_TV->setEnabled(true);
    ui->Name_LE->setEnabled(false);
    ui->Surname_LE->setEnabled(false);
    ui->Automatic_RB->setChecked(true);
    ui->Manual_RB->setChecked(false);
    isAutomatic_Participant_adding_on = true;
}

void Add_presence_dialog::on_Manual_RB_clicked()
{
    isAutomatic_Participant_adding_on = false;
    ui->Participants_TV->setEnabled(false);
    ui->Name_LE->setEnabled(true);
    ui->Surname_LE->setEnabled(true);
    ui->Automatic_RB->setChecked(false);
    ui->Manual_RB->setChecked(true);
}

void Add_presence_dialog::on_End_PB_clicked()
{
    //TODO: Do SQL magic, close connection ETC.
    this->accept();
}

void Add_presence_dialog::on_Add_Presence_PB_clicked()
{
 if(is_selected_event){
    //TODO: SQL magic to evaluate validation of participant and eventually adding presence
    bool is_signup_good = true;
    QString imie = ui->Participants_TV->item(selected_item_row,0)->text();
    QString nazwisko = ui->Participants_TV->item(selected_item_row,1)->text();


    //wez tu id_zajec z Events_Selection_CB
//    combobox->itemData(combobox->currentIndex())
    QString id_zajec = selected_id;

    QString nr_karty = "";
    QSqlQuery qry, qry0;
    qry.prepare("SELECT k.nr_karty_klienta FROM klienci as k WHERE k.imie = '"+ imie+",'k.nazwisko ='"+nazwisko+"'");
    if(qry.exec())
    {
        qry.next();
         nr_karty = qry.value(0).toString();
    }



    QString data=selected_data;
    QString oplata="15";
    QString z = "INSERT INTO `system_zapisow`.`przyszedl` (`nr_karty_klienta`, `id_zajec`,`data`,`oplata`) VALUES(" + nr_karty +","+ id_zajec +",'"+ data +"',"+ oplata +");";
//    QMessageBox *msg2 = new QMessageBox(QMessageBox::NoIcon,"title",z);
//    msg2->exec();
    qry.prepare(z);
    if(qry.exec())
    {
        is_signup_good = true;
    }
    else
    {
        is_signup_good = false;
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
    //DEBUG: These messages will always occur until magic is done

    bool is_payment_done = true ; //debug to show message
    bool are_free_places = true ; //debug to show message//make true if client is already signed up

    QString title= "Błąd w dodawaniu obecności";
    QString text;
    if(is_payment_done&&!are_free_places) text = "Brak wolnych miejsc";
    if(!is_payment_done&&are_free_places) text = "Płatność nie została uregulowana";
    if(!is_payment_done&&!are_free_places) text = "Brak wolnych miejsc oraz nie została uregulowana płątność";
//    QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,title,text);
//    msg->exec();


}

void Add_presence_dialog::on_Participants_TV_itemClicked(QTableWidgetItem *item)
{
    ui->Participants_TV->selectRow(item->row());

    is_selected_event = true;

    selected_item_row = item->row();
}

void Add_presence_dialog::on_Events_Selection_CB_currentIndexChanged(int index)
{

}

void Add_presence_dialog::on_Data_CB_currentIndexChanged(const QString &arg1)
{
    ui->Participants_TV->setRowCount(0);
    ui->Participants_TV->clearContents();
    selected_data=arg1;
    bool error=false;
    QSqlQuery qry,qry0;
    //TODO: do SQL magic to fill the Participants list
    qry.prepare("SELECT k.nr_karty_klienta,k.imie,k.nazwisko,bu.data FROM klienci as k INNER JOIN bierze_udzial as bu ON k.nr_karty_klienta=bu.nr_karty_klienta WHERE bu.id_zajec="+selected_id+" AND bu.data='"+selected_data+"';");
    if(qry.exec())
    {
//        QStringList klienci;

        while(qry.next())
        {
            QString imie = qry.value(1).toString();
            QString nazw = qry.value(2).toString();
//            klienci<<klient;


            ui->Participants_TV->insertRow((ui->Participants_TV->rowCount()));
            ui->Participants_TV->setItem(ui->Participants_TV->rowCount()-1,
                                     0,
                                     new QTableWidgetItem(imie));
            ui->Participants_TV->setItem(ui->Participants_TV->rowCount()-1,
                                     1,
                                     new QTableWidgetItem(nazw));
        }
    }
    else {
        error=true;
    }
}

void Add_presence_dialog::on_Events_Selection_CB_currentIndexChanged(const QString &arg1)
{
    selected_id = arg1;
    ui->Participants_TV->setRowCount(0);
    ui->Participants_TV->clearContents();

    bool error=false;
    QSqlQuery qry,qry0;
    //TODO: do SQL magic to fill the Participants list
    qry.prepare("SELECT k.nr_karty_klienta,k.imie,k.nazwisko,bu.data FROM klienci as k INNER JOIN bierze_udzial as bu ON k.nr_karty_klienta=bu.nr_karty_klienta WHERE bu.id_zajec="+selected_id+" AND bu.data='"+selected_data+"';");
    if(qry.exec())
    {
//        QStringList klienci;

        while(qry.next())
        {
            QString imie = qry.value(1).toString();
            QString nazw = qry.value(2).toString();
//            klienci<<klient;


            ui->Participants_TV->insertRow((ui->Participants_TV->rowCount()));
            ui->Participants_TV->setItem(ui->Participants_TV->rowCount()-1,
                                     0,
                                     new QTableWidgetItem(imie));
            ui->Participants_TV->setItem(ui->Participants_TV->rowCount()-1,
                                     1,
                                     new QTableWidgetItem(nazw));
        }
    }
    else {
        error=true;
    }
    //TODO: do SQL magic to fill the events list
    QStringList data_names;
    ui->Data_CB->clear();
    qry.prepare("SELECT data FROM bierze_udzial WHERE id_zajec="+selected_id);
    if(qry.exec())
    {
        //        QStringList places;
        while(qry.next())
        {
            QString sala = qry.value(0).toString();
            data_names<<sala;
        }
        ui->Data_CB->addItems(data_names);
    }
    else {
        error=true;
    }



   if(error)
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }

}
