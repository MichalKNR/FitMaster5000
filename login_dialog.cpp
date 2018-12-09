#include "login_dialog.h"
#include "ui_login_dialog.h"

Login_Dialog::Login_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dialog)
{
    ui->setupUi(this);
    ui->Password_secondary_LE->setEnabled(false); //kolejna komenda i tak spowoduje jego wyłączenie, lecz aby zahcować przejrzystość jest też tu.
    ui->New_customer_CB->setCheckState(Qt::Unchecked);

}

Login_Dialog::~Login_Dialog()
{
    delete ui;
}

void Login_Dialog::on_OK_PB_clicked()
{
    if(ui->New_customer_CB->checkState()==Qt::Checked){// Jeżeli został zaznaczony nowy uzytkownik
        if(ui->Password_primary_LE->text().compare(ui->Password_secondary_LE->text())==0){ //Jeżeli są zgodne
            login=ui->Login_LE->text().toStdString();
            password=ui->Password_primary_LE->text().toStdString();
            is_new_customer=true;
            this->accept();
        }
    }
    else{
        login=ui->Login_LE->text().toStdString();
        password=ui->Password_primary_LE->text().toStdString();
        is_new_customer=false;
        this->accept();
    }

}

void Login_Dialog::on_New_customer_CB_stateChanged(int arg1)
{
    if(ui->New_customer_CB->checkState()==Qt::Checked)// Jeżeli został zaznaczony nowy uzytkownik
        ui->Password_secondary_LE->setEnabled(true);
    else
        ui->Password_secondary_LE->setEnabled(false);
}
