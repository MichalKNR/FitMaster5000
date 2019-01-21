#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"login_dialog.h"
#include"show_events_dialog.h"
#include "add_event_dialog.h"
#include "signup_for_event_dialog.h"
#include "add_presence_dialog.h"
#include "stats_coach.h"
#include "stats_events_dialog.h"
#include "stats_fitmaster_dialog.h"

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
    void on_Log_out_PB_clicked();

    void on_Apply_for_Event_PB_clicked();

    void on_Add_new_Events_PB_clicked();

    void on_ShowEvents_PB_clicked();

    void on_Add_presence_PB_clicked();

    void on_RAP_events_PB_clicked();

    void on_RAP_coaches_PB_clicked();

    void on_RAP_FITMASTER_PB_clicked();

private:
    Ui::MainWindow *ui;

    Login_Dialog *login_window;

    std::string login;
    std::string password;
    bool is_new_customer;


    void login_customer();


    bool check_password_validity(std::string login, std::string password);

    bool is_admin(std::string login, std::string password);

    bool is_coach(std::string login, std::string password);
};

#endif // MAINWINDOW_H
