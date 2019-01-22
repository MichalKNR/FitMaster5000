#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QString>
#include <QtSql>
#include <QTableWidgetItem>
#include "typedefs.h"
#include <string>
#include <sstream>
#include "QMessageBox"

namespace Ui {
class Login_Dialog;
}

class Login_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Dialog(QWidget *parent = nullptr);
    ~Login_Dialog();
    int string_to_int(std::string s);

    std::string login;
    std::string password;
    bool is_new_customer;

private slots:
    void on_OK_PB_clicked();

    void on_New_customer_CB_stateChanged(int arg1);

private:
    Ui::Login_Dialog *ui;
};

#endif // LOGIN_DIALOG_H
