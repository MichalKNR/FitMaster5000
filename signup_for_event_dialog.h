#ifndef SIGNUP_FOR_EVENT_DIALOG_H
#define SIGNUP_FOR_EVENT_DIALOG_H

#define DEBUG //delete while playing with SQL magic !!!

#include <QDialog>
#include <typedefs.h>
#include <QString>
#include <QtSql>
#include <QTableWidgetItem>
#include <string>
#include <sstream>
#include <QTableWidgetItem>

namespace Ui {
class Signup_for_event_Dialog;
}

class Signup_for_event_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Signup_for_event_Dialog(QWidget *parent = nullptr, QString s="");
    ~Signup_for_event_Dialog();
QString nr_karty;
private slots:
    void on_End_PB_clicked();

    void on_Search_PB_clicked();

    void on_EventsTable_itemClicked(QTableWidgetItem *item);

    void on_Signup_PB_clicked();

private:
    Ui::Signup_for_event_Dialog *ui;

    std::vector<FIT::Event> Events;

    QString parse_time(FIT::Event event);
    QString parse_place(FIT::Event event);

    void fill_Events_Table();
    int string_to_int(std::string s);

    enum Columns{
        Tytul,
        Trener,
        Miejsce,
        Czas,
        Ilosc_Miejsc
    };
        bool is_selected_event;
        int selected_item_row;
};

#endif // SIGNUP_FOR_EVENT_DIALOG_H
