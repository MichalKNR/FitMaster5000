#ifndef ADD_PRESENCE_DIALOG_H
#define ADD_PRESENCE_DIALOG_H

#include <QDialog>

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

private:
    Ui::Add_presence_dialog *ui;

    bool isAutomatic_Participant_adding_on;
};

#endif // ADD_PRESENCE_DIALOG_H
