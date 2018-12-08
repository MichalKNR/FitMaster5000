#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<login_dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Login_Dialog *login_window;

private slots:
    //void create_new_customer(std::string login, std::string password);
    //void login_customer(std::string login, std::string password);
};

#endif // MAINWINDOW_H
