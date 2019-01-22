#ifndef STATS_COACH_H
#define STATS_COACH_H

#include <QDialog>
#include <QString>
#include <QtSql>
#include <QTableWidgetItem>
#include "typedefs.h"
#include <string>
#include <sstream>
#include "QMessageBox"

namespace Ui {
class STATS_Coach;
}

class STATS_Coach : public QDialog
{
    Q_OBJECT

public:
    explicit STATS_Coach(QWidget *parent = nullptr);
    ~STATS_Coach();
    int string_to_int(std::string s);

private:
    Ui::STATS_Coach *ui;
};

#endif // STATS_COACH_H
