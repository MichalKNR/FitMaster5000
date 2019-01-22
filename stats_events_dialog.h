#ifndef STATS_EVENTS_DIALOG_H
#define STATS_EVENTS_DIALOG_H

#include <QDialog>
#include <QString>
#include <QtSql>
#include <QTableWidgetItem>
#include "typedefs.h"
#include <string>
#include <sstream>
#include "QMessageBox"

namespace Ui {
class STATS_Events_dialog;
}

class STATS_Events_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit STATS_Events_dialog(QWidget *parent = nullptr);
    ~STATS_Events_dialog();
    int string_to_int(std::string s);

private:
    Ui::STATS_Events_dialog *ui;
};

#endif // STATS_EVENTS_DIALOG_H
