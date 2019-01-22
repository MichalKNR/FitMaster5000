#include "stats_coach.h"
#include "ui_stats_coach.h"
#include <iostream>

STATS_Coach::STATS_Coach(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STATS_Coach)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(5);
    QStringList ColumnsNames;
    ColumnsNames<<"nr_karty_trenera"<<"imie"<<"nazwisko"<<"ilosc_zajec"<<"wynagrodzenie";
    ui->tableWidget->setHorizontalHeaderLabels(ColumnsNames);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,150);

    struct info{
        int nr_karty_trenera;
        std::string imie;
        std::string nazwisko;
        int ilosc_zajec;
        int wynagrodzenie;
    };

    std::vector<info> event_info;

    //TODO: SQL Magic
    QSqlQuery qry;
    QString m ="9",r="2018";
    qry.prepare(" SELECT nr_karty_trenera, imie, nazwisko, count(data) AS `ilosc przeprowadzonych zajec`, sum(zaplata) AS wynagrodzenie FROM trenerzy INNER JOIN poprowadzil USING (nr_karty_trenera) WHERE MONTH(poprowadzil.data) = "+m+" AND YEAR(poprowadzil.data) = "+r+" GROUP BY nr_karty_trenera  ORDER BY nr_karty_trenera;");
    if(qry.exec())
    {
        while(qry.next())
        {
            std::string nr_karty_trenera = qry.value(0).toString().toStdString();
            std::string imie = qry.value(1).toString().toStdString();
            std::string nazwisko = qry.value(2).toString().toStdString();
            std::string ilosc_przeprowadzonych_zajec = qry.value(3).toString().toStdString();
            std::string wynagrodzenie = qry.value(4).toString().toStdString();
            info in;
            in.imie=imie;
            in.nazwisko=nazwisko;
            in.nr_karty_trenera=string_to_int(nr_karty_trenera);
            in.wynagrodzenie=string_to_int(wynagrodzenie);
            in.ilosc_zajec=string_to_int(ilosc_przeprowadzonych_zajec);
            event_info.push_back(in);;
//            std::cout<<imie;
//            std::cout<<in.imie;
//            std::cout<<event_info.at(0).imie;
        }
    }
    else
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }


    for(int i = 0;i<(int)event_info.size();i++){
        ui->tableWidget->insertRow((ui->tableWidget->rowCount()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 0,
                                 new QTableWidgetItem(QString::number(event_info.at(i).nr_karty_trenera)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 1,
                                 new QTableWidgetItem(QString::fromStdString(event_info.at(i).imie)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 2,
                                 new QTableWidgetItem(QString::fromStdString(event_info.at(i).nazwisko)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 3,
                                 new QTableWidgetItem(QString::number(event_info.at(i).nr_karty_trenera)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 4,
                                 new QTableWidgetItem(QString::number(event_info.at(i).wynagrodzenie)));
    }
}
int STATS_Coach::string_to_int(std::string s){
    int i;
    std::stringstream stream;
    stream.str(s);
    stream>>i;
    return i;
}

STATS_Coach::~STATS_Coach()
{
    delete ui;
}
