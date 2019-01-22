#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect_database();
//    if(!database.open())
//    {
//        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą!1 \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
//        error_message->exec();
//        connect_database();
//    }
//    else
//    {
//        QMessageBox *error_message = new QMessageBox("Połączenie","Połączenie",QMessageBox::NoIcon,0,0,0);
//        error_message->exec();
//        connect_database();
//    }
    ui->setupUi(this);
    setWindowTitle("Okno główne");
    login_customer();
}

void MainWindow::connect_database(){
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("admin");
    //    database.setUserName("app_klient");
    //    database.setPassword("haslo");
    database.setDatabaseName("system_zapisow");
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
            QMessageBox *error_message = new QMessageBox("Błąd logowania","Użyto złego hasła! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
            error_message->exec();
        }
    }while(valid_password==false);
    ui->Login_Label->setText(QString::fromStdString(this->login));

    if(is_new_customer)
        add_new_customer();

    if(user == "admin") {
        ui->isAdmin_Laber->setVisible(true);
        ui->Add_new_Events_PB->setVisible(true);
        ui->ShowEvents_PB->setVisible(true);
        ui->Add_presence_PB->setVisible(true);
        ui->Apply_for_Event_PB->setVisible(true);

        ui->RAP_events_PB->setVisible(true);
        ui->RAP_coaches_PB->setVisible(true);
        ui->RAP_FITMASTER_PB->setVisible(true);
    }
    else{
        ui->RAP_events_PB->setVisible(false);
        ui->RAP_coaches_PB->setVisible(false);
        ui->RAP_FITMASTER_PB->setVisible(false);
        if(user == "trener"){
            ui->isAdmin_Laber->setVisible(false);
            ui->Add_new_Events_PB->setVisible(false);
            ui->ShowEvents_PB->setVisible(false);
            ui->Add_presence_PB->setVisible(true);
            ui->Apply_for_Event_PB->setVisible(false);
        }
        else {
            ui->isAdmin_Laber->setVisible(false);
            ui->Add_new_Events_PB->setVisible(false);
            ui->ShowEvents_PB->setVisible(true);
            ui->Add_presence_PB->setVisible(false);
            ui->Apply_for_Event_PB->setVisible(true);
        }
    }
}

void MainWindow::add_new_customer(){
    QString qlogin = QString::fromStdString(login.substr(1,login.size()));
    QString qpassword = QString::fromStdString(password);
    nr_k=qlogin;
    user = "klient";
    //TODO new customer
    bool is_signup_good = false;
    //insert new student
    QSqlQuery qry;
    //            QString nk= QString::fromStdString(nr_karty);
    QString nk=nr_k;
//    qry.prepare("SELECT nr_karty_klienta,id_zajec FROM system_zapisow.zapisany_na; ");
    qry.prepare("INSERT INTO `system_zapisow`.`klienci` (`nr_karty_klienta`, `imie`, `nazwisko`, `liczba_obecnosci`, `haslo`) VALUES('" + nk +"','A','B','0','"+ qpassword +"');");
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

bool MainWindow:: check_password_validity(std::string login, std::string password){
    QString qlogin = QString::fromStdString(login);
    QString qpassword = QString::fromStdString(password);

    if(!database.open())
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą!1 \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
        connect_database();
    }
    else
    {
        if(login == "admin" && password == "admin")
        {
            nr_k="admin";
            user="admin";
            return true;
        }
        else
        {
            QSqlQuery qry;
            QString qlogin = QString::fromStdString(login.substr(1,login.size()));
            nr_k=qlogin;
            if(login[0] == 'K')
            {
                qry.exec("SELECT * FROM klienci WHERE nr_karty_klienta = '" + qlogin + "' and haslo = '" +qpassword + "'");
                user = "klient";
            }
            else if(login[0] == 'T')
            {
                user = "trener";
                qry.exec("SELECT * FROM trenerzy WHERE nr_karty_trenera = '" + qlogin + "' and haslo = '" +qpassword + "'");
            }
            else
            {
                user = "brak";
                return false;
            }

            if(qry.size() > 0)
            {
                qry.next();
                return true;
            }
        }
        user = "brak";
        return false;
    }
    user = "brak";
    return false; //DEBUG
}


//bool MainWindow::is_admin(std::string login, std::string password){
//    //TODO evaluate ADMIN authentication
//    return true; //DEBUG
//}

//bool MainWindow::is_coach(std::string login, std::string password){
//    //TODO evaluate COACH authentication
//    return false; //DEBUG
//}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Log_out_PB_clicked()
{
    ui->Login_Label->setText("");
    login_customer();
}

void MainWindow::on_Apply_for_Event_PB_clicked()
{
    Signup_for_event_Dialog *SiFNEV_D = new Signup_for_event_Dialog(nullptr,nr_k);
    if(SiFNEV_D->exec() == QDialog::Accepted)
        return;
}


void MainWindow::on_Add_new_Events_PB_clicked()
{
    Add_Event_Dialog *AdEV_D = new Add_Event_Dialog;
    if(AdEV_D->exec()==QDialog::Accepted)
        return;
}

void MainWindow::on_ShowEvents_PB_clicked()
{
    Show_Events_Dialog *ShEv_D = new Show_Events_Dialog(nullptr,nr_k);
    if(ShEv_D->exec()==QDialog::Accepted)
        delete ShEv_D;
}

void MainWindow::on_Add_presence_PB_clicked()
{
    Add_presence_dialog *AdPr_D = new Add_presence_dialog;
    if(AdPr_D->exec()==QDialog::Accepted)
        delete AdPr_D;
}

void MainWindow::on_RAP_events_PB_clicked()
{
    STATS_Events_dialog *SEV_D = new STATS_Events_dialog;
    if(SEV_D->exec()==QDialog::Accepted)
        delete  SEV_D;
}

void MainWindow::on_RAP_coaches_PB_clicked()
{
    STATS_Coach *SCH = new STATS_Coach;
    if(SCH->exec()==QDialog::Accepted)
        delete SCH;
}

void MainWindow::on_RAP_FITMASTER_PB_clicked()
{
    STATS_FitMaster_dialog *SFM = new STATS_FitMaster_dialog;
    if(SFM->exec()==QDialog::Accepted)
        delete SFM;
}
