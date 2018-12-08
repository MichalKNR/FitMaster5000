#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>

namespace Ui {
class Login_Dialog;
}

class Login_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Dialog(QWidget *parent = nullptr);
    ~Login_Dialog();

private slots:
    void on_OK_PB_clicked();

    void on_New_customer_CB_stateChanged(int arg1);

private:
    Ui::Login_Dialog *ui;
};

#endif // LOGIN_DIALOG_H
