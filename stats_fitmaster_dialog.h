#ifndef STATS_FITMASTER_DIALOG_H
#define STATS_FITMASTER_DIALOG_H

#include <QDialog>
#include <QString>
#include <QtSql>
#include <QTableWidgetItem>
#include "typedefs.h"
#include <string>
#include <sstream>
#include "QMessageBox"

namespace Ui {
class STATS_FitMaster_dialog;
}

class STATS_FitMaster_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit STATS_FitMaster_dialog(QWidget *parent = nullptr);
    ~STATS_FitMaster_dialog();
    int string_to_int(std::string s);

private:
    Ui::STATS_FitMaster_dialog *ui;
};

#endif // STATS_FITMASTER_DIALOG_H
