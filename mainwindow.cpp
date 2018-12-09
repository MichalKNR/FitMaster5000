#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
}while(valid_password==false);

}
bool check_password_validity(std::string login, std::string password){
    //TODO evaluate password validity
    return true; //DEBUG
}

MainWindow::~MainWindow()
{
    delete ui;
}
