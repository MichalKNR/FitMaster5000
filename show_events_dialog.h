#ifndef SHOW_EVENTS_DIALOG_H
#define SHOW_EVENTS_DIALOG_H

#include <QDialog>
#include "typedefs.h"
#include <QTableWidgetItem>

namespace Ui {
class Show_Events_Dialog;
}

class Show_Events_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Show_Events_Dialog(QWidget *parent = nullptr);
    ~Show_Events_Dialog();

private slots:
    void on_End_Dialog_PB_clicked();

    void on_exit_event_PB_clicked();

    void on_EventsTable_itemClicked(QTableWidgetItem *item);

private:
    Ui::Show_Events_Dialog *ui;
    enum Columns{
        Tytul,
        Trener,
        Miejsce,
        Czas
    };

    std::vector<FIT::Event> Events;

    QString parse_time(FIT::Event event);
    QString parse_place(FIT::Event event);

    void fill_Events_Table();

    bool is_selected_event;
    int selected_item_row;
};

#endif // SHOW_EVENTS_DIALOG_H
