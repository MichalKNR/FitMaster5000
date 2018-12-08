#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class Login_Window;
}

class Login_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login_Window(QWidget *parent = nullptr);
    ~Login_Window();

private:
    Ui::Login_Window *ui;
};

#endif // LOGIN_WINDOW_H
