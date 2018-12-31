#include "add_presence_dialog.h"
#include "ui_add_presence_dialog.h"

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

    //TODO:: do SQL magic to fill the Participants list
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

}
