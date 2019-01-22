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
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,50);
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
 QString m ="9",r="2018";
    QString z1=" SELECT monthname(concat('2010-',"+m+",'-01')) AS miesiac,"+r+" AS Rok, sum(przyszedl.oplata) AS `suma wplywow` FROM przyszedl WHERE MONTH(przyszedl.data) = "+m+" AND YEAR(przyszedl.data) = "+r+" GROUP BY month(przyszedl.data);";
    QString z2="SELECT monthname(concat('2010-',"+m+",'-01')) AS miesiac,"+r+" AS Rok ,sum(poprowadzil.zaplata) AS `suma wydatkow` FROM poprowadzil WHERE MONTH(poprowadzil.data) = "+m+" AND YEAR(poprowadzil.data) = "+r+" GROUP BY month(poprowadzil.data);";
    QString z3=" SELECT monthname(concat('2010-',"+m+",'-01')) AS miesiac,"+r+" AS Rok ,count(*) AS `liczba przeprowadzonych zajec`     FROM poprowadzil     WHERE MONTH(poprowadzil.data) = "+m+" AND YEAR(poprowadzil.data) = "+r+"     GROUP BY month(poprowadzil.data);";
    QSqlQuery qry;
    qry.prepare(z1);
    if(qry.exec())
    {
        while(qry.next())
        {
            std::string miesiac = qry.value(0).toString().toStdString();
            std::string rok = qry.value(1).toString().toStdString();
            std::string suma_wplywow = qry.value(2).toString().toStdString();
            info in;
            in.miesiac=string_to_int(miesiac);
            in.rok=string_to_int(rok);
            in.suma_wplywow=string_to_int(suma_wplywow);
            event_info.push_back(in);
        }
    }
    else
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }
    qry.prepare(z2);
    if(qry.exec())
    {
        int iterator=0;
        while(qry.next())
        {
            std::string suma_wydatkow = qry.value(2).toString().toStdString();

            event_info.at(iterator).suma_wydatkow=string_to_int(suma_wydatkow);
            iterator++;
        }
    }
    else
    {
        QMessageBox *error_message = new QMessageBox("Błąd połączenia","Brak połączenia z bazą! \n\rSpróbuj ponownie",QMessageBox::NoIcon,0,0,0);
        error_message->exec();
    }
    qry.prepare(z3);
    if(qry.exec())
    {
        int iterator=0;
        while(qry.next())
        {
            std::string liczba_zajec = qry.value(2).toString().toStdString();

            event_info.at(iterator).liczba_zajec=string_to_int(liczba_zajec);
            iterator++;
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
int STATS_FitMaster_dialog::string_to_int(std::string s){
    int i;
    std::stringstream stream;
    stream.str(s);
    stream>>i;
    return i;
}

STATS_FitMaster_dialog::~STATS_FitMaster_dialog()
{
    delete ui;
}
