#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"login_dialog.h"
#include"show_events_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Log_out_PB_clicked();

    void on_Apply_for_Event_PB_clicked();

    void on_Add_new_Events_PB_clicked();

    void on_ShowEvents_PB_clicked();

private:
    Ui::MainWindow *ui;

    Login_Dialog *login_window;

    std::string login;
    std::string password;
    bool is_new_customer;

    void login_customer();


    bool check_password_validity(std::string login, std::string password);

    bool is_admin(std::string login, std::string password);
};

#endif // MAINWINDOW_H
