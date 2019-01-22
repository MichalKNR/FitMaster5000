#ifndef ADD_PRESENCE_DIALOG_H
#define ADD_PRESENCE_DIALOG_H

#include <QDialog>
#include <QString>
#include <QtSql>
#include <QTableWidgetItem>
#include "typedefs.h"
#include <string>
#include <sstream>
#include "QMessageBox"
namespace Ui {
class Add_presence_dialog;
}

class Add_presence_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_presence_dialog(QWidget *parent = nullptr);
    ~Add_presence_dialog();

private slots:
    void on_Automatic_RB_clicked();

    void on_Manual_RB_clicked();

    void on_End_PB_clicked();

    void on_Add_Presence_PB_clicked();

    void on_Participants_TV_itemClicked(QTableWidgetItem *item);

    void on_Events_Selection_CB_currentIndexChanged(int index);

    void on_Data_CB_currentIndexChanged(const QString &arg1);

    void on_Events_Selection_CB_currentIndexChanged(const QString &arg1);

private:
    Ui::Add_presence_dialog *ui;

    bool isAutomatic_Participant_adding_on;

    bool is_selected_event;
    int selected_item_row;


    QString selected_id;
    QString selected_data;
};

#endif // ADD_PRESENCE_DIALOG_H
