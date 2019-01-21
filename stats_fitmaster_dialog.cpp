#include "stats_fitmaster_dialog.h"
#include "ui_stats_fitmaster_dialog.h"

STATS_FitMaster_dialog::STATS_FitMaster_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STATS_FitMaster_dialog)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(5);
    QStringList ColumnsNames;
    ColumnsNames<<"miesiac"<<"rok"<<"suma_wplywow"<<"suma_wydatkow"<<"liczba_zajec";
    ui->tableWidget->setHorizontalHeaderLabels(ColumnsNames);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(1,125);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,150);

    struct info{
        int miesiac;
        int rok;
        int suma_wplywow;
        int suma_wydatkow;
        int liczba_zajec;
    };

    std::vector<info> event_info;

    //TODO: SQL Magic
    for(int i = 0;i<(int)event_info.size();i++){
        ui->tableWidget->insertRow((ui->tableWidget->rowCount()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 0,
                                 new QTableWidgetItem(QString::number(event_info.at(i).miesiac)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 1,
                                 new QTableWidgetItem(QString::number(event_info.at(i).rok)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 2,
                                 new QTableWidgetItem(QString::number(event_info.at(i).suma_wplywow)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 3,
                                 new QTableWidgetItem(QString::number(event_info.at(i).suma_wydatkow)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 4,
                                 new QTableWidgetItem(QString::number(event_info.at(i).liczba_zajec)));

    }
}

STATS_FitMaster_dialog::~STATS_FitMaster_dialog()
{
    delete ui;
}
