#ifndef SHOW_EVENTS_DIALOG_H
#define SHOW_EVENTS_DIALOG_H

#include <QDialog>

namespace Ui {
class Show_Events_Dialog;
}

class Show_Events_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Show_Events_Dialog(QWidget *parent = nullptr);
    ~Show_Events_Dialog();

private:
    Ui::Show_Events_Dialog *ui;
};

#endif // SHOW_EVENTS_DIALOG_H
