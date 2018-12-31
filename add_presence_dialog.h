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

private:
    Ui::Add_presence_dialog *ui;
};

#endif // ADD_PRESENCE_DIALOG_H
