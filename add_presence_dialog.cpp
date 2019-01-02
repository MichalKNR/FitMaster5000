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

    //TODO: do SQL magic to fill the Participants list
    //TODO: do SQL magic to fill the events list
    //DEBUG filing with random data

    QStringList events_names;
    events_names<<"Aerobik"<<"Zumba";
    ui->Events_Selection_CB->addItems(events_names);
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

    //TODO: SQL magic to evaluate validation of participant and eventually adding presence
    //DEBUG: These messages will always occur until magic is done

    bool is_payment_done = false ; //debug to show message
    bool are_free_places = false ; //debug to show message//make true if client is already signed up

    QString title= "Błąd w dodawaniu obecności";
    QString text;
    if(is_payment_done&&!are_free_places) text = "Brak wolnych miejsc";
    if(!is_payment_done&&are_free_places) text = "Płatność nie została uregulowana";
    if(!is_payment_done&&!are_free_places) text = "Brak wolnych miejsc oraz nie została uregulowana płątność";
    QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,title,text);
    msg->exec();


}
