#include "login_window.h"
#include "ui_login_window.h"

Login_Window::Login_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login_Window)
{

    ui->setupUi(this);
    ui->Password_secondary_LE->setEnabled(false); //kolejna komenda i tak spowoduje jego wyłączenie, lecz aby zahcować przejrzystość jest też tu.
    ui->New_customer_CB->setCheckState(Qt::Unchecked);
}

Login_Window::~Login_Window()
{
    delete ui;
}

void Login_Window::on_OK_PB_clicked()
{
    if(ui->New_customer_CB->checkState()==Qt::Checked)// Jeżeli został zaznaczony nowy uzytkownik
        if(ui->Password_primary_LE->text().compare(ui->Password_secondary_LE->text())==0){ //Jeżeli są zgodne

        }
}

void Login_Window::on_New_customer_CB_stateChanged(int arg1)
{
    if(ui->New_customer_CB->checkState()==Qt::Checked)// Jeżeli został zaznaczony nowy uzytkownik
        ui->Password_secondary_LE->setEnabled(true);
    else
        ui->Password_secondary_LE->setEnabled(false);
}
