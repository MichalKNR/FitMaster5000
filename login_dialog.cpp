#include "login_dialog.h"
#include "ui_login_dialog.h"

Login_Dialog::Login_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Logowanie");
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
int Login_Dialog::string_to_int(std::string s){
    int i;
    std::stringstream stream;
    stream.str(s);
    stream>>i;
    return i;
}


void Login_Dialog::on_New_customer_CB_stateChanged(int arg1)
{
    if(ui->New_customer_CB->checkState()==Qt::Checked){// Jeżeli został zaznaczony nowy uzytkownik
        ui->Password_secondary_LE->setEnabled(true);
        ui->Login_LE->setEnabled(false);
        //todo sql zdobyć max index
        QSqlQuery qry,qry0;
        std::string snk;
        qry.prepare("SELECT MAX(nr_karty_klienta) FROM klienci ");
        if(qry.exec())
        {
            qry.next();
//            while(qry.next())
            {
                std::string nr_karty_trenera = qry.value(0).toString().toStdString();
                int nk = string_to_int(nr_karty_trenera);
                nk++;

                std::stringstream stream;
                stream<<nk;
                snk= stream.str();

                ui->Login_LE->setText("K"+QString::fromStdString(snk));
            }
        }
        else
        {
            QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
            error_message->exec();
        }
    }
    else{
        ui->Password_secondary_LE->setEnabled(false);
        ui->Login_LE->setEnabled(true);
    }
}
