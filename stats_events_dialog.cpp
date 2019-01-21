#include "stats_events_dialog.h"
#include "ui_stats_events_dialog.h"

STATS_Events_dialog::STATS_Events_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STATS_Events_dialog)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(3);
    QStringList ColumnsNames;
    ColumnsNames<<"id_zajec"<<"typ_zajec"<<"sr_il_osob";
    ui->tableWidget->setHorizontalHeaderLabels(ColumnsNames);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);

    struct info{
        int id_zajec;
        std::string typ_zajec;
        int sr_il_osob;
    };

    std::vector<info> event_info;

    //TODO: SQL Magic
    for(int i = 0;i<(int)event_info.size();i++){
        ui->tableWidget->insertRow((ui->tableWidget->rowCount()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 0,
                                 new QTableWidgetItem(QString::number(event_info.at(i).id_zajec)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 1,
                                 new QTableWidgetItem(QString::fromStdString(event_info.at(i).typ_zajec)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 2,
                                 new QTableWidgetItem(QString::number(event_info.at(i).sr_il_osob)));

    }
}

STATS_Events_dialog::~STATS_Events_dialog()
{
    delete ui;
}
