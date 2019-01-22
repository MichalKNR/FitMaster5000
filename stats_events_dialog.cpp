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

    QSqlQuery qry;
     QString m ="9",r="2018";
    qry.prepare("SELECT id_zajec, typ_zajec, ROUND(avg(ilosc_osob),1) as `srednia ilosc osob` FROM (   SELECT id_zajec, typ_zajec, COUNT(id_zajec) AS ilosc_osob, przyszedl.data    FROM zajecia INNER JOIN przyszedl USING (id_zajec)    WHERE MONTH(przyszedl.data) = "+m+" AND YEAR(przyszedl.data) = "+r+" GROUP BY zajecia.id_zajec, przyszedl.data ) AS sumy_osob GROUP BY id_zajec ORDER BY `srednia ilosc osob` DESC;");
    if(qry.exec())
    {
        while(qry.next())
        {
            std::string id_zajec = qry.value(0).toString().toStdString();
            std::string typ_zajec = qry.value(1).toString().toStdString();
            std::string sr_il_osob = qry.value(2).toString().toStdString();
            info in;
            in.id_zajec=string_to_int(id_zajec);
            in.typ_zajec=typ_zajec;
            in.sr_il_osob=string_to_int(sr_il_osob);
            event_info.push_back(in);
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
                                 new QTableWidgetItem(QString::number(event_info.at(i).id_zajec)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 1,
                                 new QTableWidgetItem(QString::fromStdString(event_info.at(i).typ_zajec)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,
                                 2,
                                 new QTableWidgetItem(QString::number(event_info.at(i).sr_il_osob)));

    }
}
int STATS_Events_dialog::string_to_int(std::string s){
    int i;
    std::stringstream stream;
    stream.str(s);
    stream>>i;
    return i;
}

STATS_Events_dialog::~STATS_Events_dialog()
{
    delete ui;
}
