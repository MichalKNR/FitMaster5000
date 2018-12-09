#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    login_customer();
}

void MainWindow::login_customer(){
    login_window = new Login_Dialog();
    bool valid_password=false;
    do{
    if(login_window->exec()==QDialog::Accepted){
        this->login=login_window->login;
        this->password=login_window->password;
        this->is_new_customer=login_window->is_new_customer;
    }
    if(is_new_customer) break; //Nowy użytkownik nie musi mieć spradzanego hasła

    valid_password=check_password_validity(login,password);
    if(valid_password==false){
        QMessageBox *error_message = new QMessageBox("Błąd logowania","Użyto złego hasła!, spróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }
}while(valid_password==false);

}
bool MainWindow:: check_password_validity(std::string login, std::string password){
    //TODO evaluate password validity
    return true; //DEBUG
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Log_out_PB_clicked()
{
    login_customer();
}

void MainWindow::on_Apply_for_Event_PB_clicked()
{

}
