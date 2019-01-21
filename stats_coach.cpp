#include "stats_coach.h"
#include "ui_stats_coach.h"

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

STATS_Coach::~STATS_Coach()
{
    delete ui;
}
